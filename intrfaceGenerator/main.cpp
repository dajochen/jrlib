#include <QtCore>

#include <iostream>
#include <string>
using namespace std;

#define voidFunction "-void-"
#define funcSeparator "//-----------------------------------------------------------------------------\n\n"

bool debugMode; // mit -debug werden mehr Ausgaben nach cout gemacht.
bool forceMode; // Wird -force als Option angegeben, wird die Ausgabe in jedem Fall erzeugt, auch wenn sich das Interface nicht geaendert hat.


//-----------------------------------------------------------------------------

enum castMode {plainType, setPointer, readPointer};
QString castType(const QString& type, const castMode mode, bool forSip=false){

  QString castType;
  if (type == "Bool"){
    castType = "bool";
  } else if (type == "Int"){
    castType = "int";
  } else if (type == "Real"){
    castType = "tReal";
  } else if (type == "String"){
    castType = "tString";
  } else if (type == "Vector"){
    castType = "tVector";
  } else if (type == "RGB"){
    castType = "tRGB";
  } else if (type.endsWith("List")){
    //IntList, DotList, CLoftList, ...
    if (type.startsWith("Bool")){
      castType = "tList<bool>";
    } else if (type.startsWith("Int")){
      castType = "tList<int>";
    } else if (type.startsWith("Real")){
      castType = "tList<tReal>";
    } else if (type.startsWith("Vector")){
      castType = "tList<tVector>";
    } else if (type.startsWith("String")){
      castType = "tList<tString>";//Noch nicht getestet, ob das funktioniert!!!
    } else {
      castType = "tList<tElement*>";
    }
  } else {                              //Dot, CLoft, Line, ...
    castType = "tElement*";
  }

  if (mode == setPointer){
    if (castType == "tElement*"){
      castType = "(" + castType + ")";
    } else {
      castType = "*(" + castType + "*)";
    }
  } else if (mode == readPointer){
    if (castType == "tElement*"){
      castType = "(" + castType + "*)";
    } else {
      castType = "(" + castType + "*)";
    }
  }


  if (forSip && !type.endsWith("List")){
    // tElement werden in ihren eigentlichen Formaten aufgerufen (tDot, tPoint, ...)
    // Listen werden immer als tList<tElement*> übergeben.
    castType.replace("Element",type);
  }

  return castType;
}


QString getPropertyTypeMatcher(const QString& type, const QString& comparator){
    QStringList nonElementTypes = QString("Int,Real,Vector,String,Bool,RGB").split(",");
    if (nonElementTypes.contains(type) || type.endsWith("List")) {
        return comparator + " == \"" + type +"\"";
    } else {
        return "(" + comparator+ " == \"" + type + "\"|| " + comparator + "==\"Element\")";
    }
}

QString setPropertyTypeMatcher(QString type) {
    QStringList nonElementTypes = QString("Int,Real,Vector,String,Bool,RGB").split(",");
    QString matcher;
    if (nonElementTypes.contains(type) || type.endsWith("List")) {
        matcher = "type == \"" + type + "\"";
    } else {
        matcher = "( type == \"" + type + "\" || value==NULL || (type==\"Element\" && ((tElement*)value)->intrface()->isOfType(\"" + type+"\")))";
        //matcher = " (type == \"" + type + "\" || (type==\"Element\" && value &&  ((tElement*)value)->intrface()->isOfType(\"" + type +"\")))";
    }
    return matcher;
}


//-----------------------------------------------------------------------------
void writeHeader (QTextStream& stream, QFileInfo fInfo)
{
  stream << "//------------------------------------------------------------------------" << endl
         << "//Automatically generated interface class" << endl
         << "//generated from " << fInfo.fileName() << " (" << fInfo.lastModified().toString() <<")" << endl
         << "//------------------------------------------------------------------------" << endl
         << endl;
}
//-----------------------------------------------------------------------------

void processHeaderFile (char *fileName)
{
  bool error,
       isHeaderIncluded = false,
       isInterfaceUpToDate = false,
       isAbstract = false,
       publicMode = false; // true is line is within public: area

  int j,pos,lineCounter;

  QFile file,iHeaderFile,iCppFile,sipFile;
  QFileInfo iInfo,fInfo,sipInfo;
  QString iFileName, sipFileName,
          className, iClassName;
  QStringList parentClass, tparentClass,
              command, readable, writeable, type;
  QMap<QString,QStringList>  action;
  QString optionalProperties = ",";// Optional properties are not necessary to describe the element.
                                   // E.g.: such properties will not be written/stored to a file.
  QTextStream *iHeader, *iCpp;

  QStringList enums;
  QString constructor;
  QStringList publicFuncs;
  QHash<QString,QString> headerHash;

  fInfo.setFile(fileName);
  if (!fInfo.exists()){
    cout << "error: the given jr-header file (" << fInfo.filePath().toStdString() << ") doesn't exist.";
  } else {
    file.setFileName(fInfo.filePath());

    iInfo.setFile(file);
    iFileName = iInfo.completeBaseName();
    iFileName.replace(0,1,"i");
    iFileName = iInfo.path() + "/" + iFileName + ".cpp";
    iCppFile.setFileName(iFileName);

    iInfo.setFile(file);
    iFileName = iInfo.fileName();
    iFileName.replace(0,1,"i");
    iFileName.prepend(iInfo.path()+ "/");
    iHeaderFile.setFileName(iFileName);
    iInfo.setFile(iHeaderFile);

    sipInfo.setFile(file);
    QDir sipDir(sipInfo.absoluteDir());
    while (!sipDir.isRoot() && !sipDir.entryList(QDir::Dirs).contains("sip",Qt::CaseInsensitive)){
      sipDir.cdUp();
    }
    if (!sipDir.isRoot()){
      QString relPath = sipDir.relativeFilePath(sipInfo.absolutePath());
      sipFileName = sipDir.path() + "/sip/" + relPath +"/" + sipInfo.completeBaseName() +".sip";
      sipInfo.setFile(sipFileName);
      sipDir.mkpath(sipInfo.absolutePath());
      sipFile.setFileName(sipFileName);
    }


    file.open(QIODevice::ReadOnly);
    QTextStream header(&file);
    iHeader = NULL;
    iCpp = NULL;

    lineCounter = 0;
    isHeaderIncluded = false;
    isAbstract = false;

    error = false;

    iClassName = "";
    while (!header.atEnd() && iClassName==""){
      QString line = header.readLine();
      QRegExp commentTest("^\\s*//"); //Kommentare filtern.
      //bool ok = commentTest.isValid();
      line.indexOf(commentTest);
      QStringList found = commentTest.capturedTexts();
      if (found[0].isEmpty()) {


        lineCounter++;
        // Ueberpruefen, ob das interface im Header eingebunden wird.
        QRegExp includesIntrfaceHeader("\\s*#include\\s+\"([\\w/\\.]+)\".*");
        if (includesIntrfaceHeader.exactMatch(line)){
          if (includesIntrfaceHeader.capturedTexts().count()>0){
            QString headerPath = includesIntrfaceHeader.capturedTexts()[1];
            QFileInfo headerInfo(headerPath);
            if (headerInfo.fileName() == iInfo.fileName()){
              isHeaderIncluded = true;
            } else {
              headerHash[headerInfo.fileName()] = headerPath;
            }
          }
        }
        // Den Klassennamen bestimmen
        QRegExp classDefinition("\\s*class\\s+.*");
        if (classDefinition.exactMatch(line) && !line.endsWith(";")){
          error = false;
          if (!isHeaderIncluded){
            cout << file.fileName().toStdString() << ": warning: the header file does not reference to \"" << iFileName.toStdString() << "\"" << endl;
          }
          QStringList list = line.simplified().split(":",QString::SkipEmptyParts);
          if (list.count() > 0){
            className = list.first().split(QRegExp("\\s+"),QString::SkipEmptyParts).last();
            className = className.remove(0,1);
            if (list.count() > 1){
              pos = list[1].indexOf("{");
              if (pos >0){
                list[1].remove(pos,list[1].length()-pos);
              }
              parentClass = list[1].split(",",QString::SkipEmptyParts);
            } else {
              cout << file.fileName().toStdString() << ":" << lineCounter << ": Warning: the class <t" << className.toStdString() << "> must inherit one class (at least tElement)." << endl;
              error = true;
            }
            tparentClass = parentClass;
            for (j=0;j<parentClass.count();j++){
              parentClass[j] = parentClass[j].simplified();
              parentClass[j].replace(" t"," i");
              if (!parentClass[j].contains(" i")){
                parentClass.removeAt(j);
                j--;
              }
            }
            if (parentClass.count() > 1){
              cout << file.fileName().toStdString() << ":" << lineCounter << ": Warning: multiple inherited classes are not supported. (Only the first is used)." << endl;
            }

            cout << endl;
          }
        }
        //      // Prüfen, ob abstrakte Funktionen deklariert sind ==> bsp: void func(void)=0;
        //      {
        //        QString shortLine = line.simplified();
        //        shortLine.remove(' ');
        //        if (shortLine.endsWith("=0;") || shortLine.endsWith("=NULL;")){
        //          isAbstract = true;
        //        }
        //      }
        { //Auf enums prüfen
          QString shortLine = line.simplified();
          if (shortLine.startsWith("enum")){
            QString code = shortLine +"\n";
            while (!code.contains(";")){
              QString l = header.readLine();
              code.append(l+"\n");
            }
            enums.append(code);
          }
        }
        { // die Argumente des Konstruktors prüfen.
          if (!className.isEmpty()){
//          QString rxStr = "[^~]\\s*t"+className+"\\(.*\\)" ; //"\\s*^~"
            QString rxStr = "^\\s*[^~]t"+className+"\\(.*\\)" ; //"\\s*^~"
            QRegExp rx(rxStr);
            //bool ok = rx.isValid();
           // line = line.simplified();
            line.indexOf(rx);
            QStringList l = rx.capturedTexts();
            if (l.count() && !l[0].isEmpty()){
              constructor = l[0].simplified();
            }
          }
        }
        { // prüfen, ob public: protected: private:
          if (!className.isEmpty()){
            QString rxStr = "\\s*(private|public|protected|signals):";
            QRegExp rx(rxStr);
            line.indexOf(rx);
            QStringList l = rx.capturedTexts();
            if (l.count()>1 && !l[0].isEmpty()){
              if (l[1]=="public"){
                publicMode = true;
              } else {
                publicMode = false;
              }
            }

          }
        }
        { // alle public-Functionen für sip sammeln.
          // durch einen Kommentar, der das Schlüsselwort sipIgnore enhält, wird die Funktion ausgelassen
          // Bsp:
          // virtual void foo (int palim); //ok
          // virtual void foo (int palim); /* sipIngore */ // foo skipped
          if (publicMode){
            //               virtual[1]..    retType[2]  funcName[3]  ( type  argument [4]   ) =[5] NULL[6]
            QString rxStr = "(\\w+\\s+){0,1}(\\w+\\**)\\s+(\\w+)\\s*\\(([\\s\\w\\*\\,&]+)\\)(\\s*=\\s*){0,1}(0|NULL){0,1}";
            QRegExp rx(rxStr);
            line.indexOf(rx);
            QStringList l = rx.capturedTexts();

            QRegExp sipIgnore("/\\*.*sipIgnore.*|//.*sipIgnore");
            if (l[6].isEmpty() && line.indexOf(sipIgnore)==-1){
              if (l.count() && !l[0].isEmpty()){
                if (l[4] == "void"){
                  QStringList sections = l[0].split(QRegExp("\\(([\\s\\w\\*\\,&]+)\\)"));
                  publicFuncs.append(sections[0].simplified()+ "();");
                } else {
                  publicFuncs.append(l[0].simplified()+";");
                }
              }
            } else {
              isAbstract = true;
            }
          }
        }
        // Die Funktionen des Interface bestimmen
        if (line.startsWith("/*sip!") && !className.isEmpty() && !error){
          bool lastRun = false;
          do {
            lastRun = line.contains("*/");
            QStringList result;
            QRegExp tester("isAbstract\\s*={0,1}\\s*(true|false){0,1}");
            line.indexOf(tester);
            result = tester.capturedTexts();
            if (!result[0].isEmpty() && (result[1] == "true" || result[1].isEmpty())){
              isAbstract = true;
            }
            if (!lastRun) line = header.readLine();
          } while (!lastRun);
        }
        // Die Funktionen des Interface bestimmen
        if (line.startsWith("/*I!") && !className.isEmpty() && !error){
          iClassName = 'i'+className;
          cout << "generating interface: <" << iClassName.toStdString() << "> into file: \"" << iFileName.toStdString() << "\"" << endl;

          while (!line.contains("*/")){
            line = header.readLine();
            lineCounter++;
            if (!line.contains("*/")){
              error = false;
              bool isOptional = false,
                   isAction = false;

              QStringList list = line.simplified().split(QRegExp("\\s+"),QString::SkipEmptyParts);

              if (list.first() == "optional"){
                isOptional = true;
                optionalProperties.append(list.at(1) + ",");
                list.removeFirst();
              } else if (list.first() == "action") {
                  list.removeFirst();
                  QString act = list.first();
                  list.removeFirst();
                  action[act] = list;
                  isAction = true;
                  list.clear();
              }

              if (list.count() < 3){
                if (!isAction/*!isOptional*/){
                  cout << "  " << file.fileName().toStdString() << ":" << lineCounter << ": error: property does not contain enough information" << endl;
                  error = true;
                }
                //cout << "expecting something like: <property name> <jr-type> [write:<function> | read:<function>" << endl;
                //cout << "instead of              : " << line.toStdString() << endl << endl;
              } else {
                command << list[0];
                type << list[1];
                readable << voidFunction;
                writeable << voidFunction;
                for (j=2; j<4 && j<list.count();j++){
                  if (list[j].startsWith("read:")){
                    list[j].remove(0,5);
                    readable.last() = list[j];
                  } else if(list[j].startsWith("write:")){
                    list[j].remove(0,6);
                    writeable.last() = list[j];
                  } else {
                    cout << "  " << file.fileName().toStdString() << ":" << lineCounter << ": error: cannot process read- and write-functions" << endl;
                    command.removeLast();
                    type.removeLast();
                    readable.removeLast();
                    writeable.removeLast();
                    error = true;
                  }
                }
                if (readable.last() == voidFunction){
                  cout << file.fileName().toStdString() << ":" << lineCounter << ": error: the property <" << command.last().toStdString() << "> is not readable." << endl;
                  error = true;
                }
                if (!error && debugMode){
                  cout << "  added property: <"<< command.last().toStdString() << ">";
                  if (isOptional){
                    cout << " (is optional)";
                  }
                  cout << endl;
                }
              }
            }
          }
        }
      }
    }
    // Die Header Datei erzeugen...

    if (!iClassName.isEmpty()){
      // Zunaechst ueberpruefen, ob das Interface evtl. noch aktuell ist.
      if (iInfo.exists()){
        iHeaderFile.open(QIODevice::ReadOnly);
        iHeader = new QTextStream(&iHeaderFile);
        while (!iHeader->atEnd() && isInterfaceUpToDate == false){
          QString line = iHeader->readLine();
          if (   line.startsWith("//")
                 && line.contains(fInfo.fileName())){
            // Datum extrahieren
            int start, length;
            start = line.indexOf("(")+1;
            length = line.indexOf(")")-start;
            line = line.mid(start,length);
            if (line == fInfo.lastModified().toString()){
              isInterfaceUpToDate = true;
            }
          }
        }
        delete iHeader;
        iHeaderFile.close();
      }
      if (!isInterfaceUpToDate || forceMode){
        // Die Header-Datei anlegen
        iHeaderFile.open(QIODevice::WriteOnly);
        iHeader = new QTextStream(&iHeaderFile);
        // Die entsprechende Cpp-Datei anlegen
        if (command.count() > 0){
          iCppFile.open(QIODevice::WriteOnly);
          iCpp = new QTextStream(&iCppFile);
        } else {
          iCpp = NULL;
        }



        writeHeader(*iHeader, fInfo);
        *iHeader << "#ifndef " << iClassName.toUpper() <<"_H_" << endl;
        *iHeader << "#define " << iClassName.toUpper() <<"_H_" << endl << endl;
        // includes festlegen
        for (j=0;j<parentClass.count();j++){
          QString pc;
          pc = parentClass[j].split(QRegExp("\\s+"),QString::SkipEmptyParts).last();
          pc.replace(0,1,'t');
          QString pcHeader =  headerHash[pc+".h"];
          if (pcHeader.isEmpty()){
            //pcHeader = "jrIntrfaces.h";
            //pcHeader = pc.replace(0,1,'i')+".h";
            pcHeader = "Error: could not identify a matching #include to the inherited class: " + pc    ;
          }
          *iHeader << "#include \"" << pcHeader  << "\"" << endl;
        }
        *iHeader << endl;

        // Die Interface-Klasse definieren
        *iHeader << "class " << iClassName << " : ";
        for (j=0;j<parentClass.count();j++){
          *iHeader << parentClass[j];
          if (j!=parentClass.count()-1){
            *iHeader << ", ";
          }
        }
        *iHeader << endl << "{" << endl;

        // Ob public, private, etc. wird nun nicht mehr gebraucht.
        for (j=0;j<parentClass.count();j++){
          parentClass[j] = parentClass[j].split(" ",QString::SkipEmptyParts).last();
        }


        // Die Public-Funktionen
        *iHeader << "\t" << "public:" << endl;
        if (command.count() == 0 && action.count() == 0){
          // Der Standard-Konstruktor
          *iHeader << "\t\t" << iClassName << "(tElement *el):" << parentClass[0]<< "(el){}" << endl
                   << endl;
          // Es wird der aktuelle Klassenname gesetzt.
          *iHeader << "\t\tstatic tString theType(void) {return \""<<className<<"\";}" << endl;
          *iHeader << "\t\tvirtual tString type(void) const {return "<<iClassName<<"::theType();}" << endl
                   << endl;
          *iHeader << "\t\tvirtual bool getPropertyValue(int index, tString propType, void* value){" << endl
                   << "\t\t\tif (index == 0 && propType == \"String\"){" << endl
                   << "\t\t\t*(tString*)value =" << iClassName << "::theType();" << endl
                   << "\t\t\t\treturn true;" << endl
                   << "\t\t\t} else {" << endl
                   << "\t\t\t\treturn " << parentClass[0] <<"::getPropertyValue(index,propType,value);" << endl
                   << "\t\t\t}" << endl
                   << "\t\t}" << endl;
          *iHeader  << "\t\tvirtual QStringList inheritedTypes(void){" << endl
                    << "\t\t\treturn (" << parentClass[0] << "::inheritedTypes() << theType());" << endl
                    << "\t\t}" << endl;
          *iHeader << "\t\tvirtual bool isOfType(QString thetype){" << endl
                   << "\t\t\tif (theType() == thetype) {" << endl
                   << "\t\t\t\treturn true;" << endl
                   << "\t\t\t} else {"<< endl
                   << "\t\t\t\treturn " << parentClass[0] << "::isOfType(thetype);" << endl
                   << "\t\t\t}" << endl
                   << "\t\t}" << endl;
          *iHeader << "};" << endl;
          *iHeader << "#endif /*" << iClassName.toUpper() << "_H_*/" << endl ;
        } else {
          *iHeader << "\t\t" << iClassName << "(tElement *el);" << endl;
          *iHeader << "\t\tvirtual ~" << iClassName << "();" << endl
                   << endl;
          *iHeader << "\t\tstatic tString theType(void) {return \""<<className<<"\";}" << endl;
          *iHeader << "\t\tvirtual tString type(void) const {return "<<iClassName<<"::theType();}" << endl
                   << endl;
          *iHeader << "\t\tvirtual tString getPropertyName(int index);" << endl;
          *iHeader << "\t\tvirtual tString getPropertyType(int index);" << endl;
          *iHeader << "\t\tvirtual bool getPropertyValue(int index, tString type, void* value);" << endl;
          *iHeader << "\t\tvirtual bool isReadOnly(int);" << endl;
          *iHeader << "\t\tvirtual bool isOptional(QString propName);" << endl;
          *iHeader << "\t\tvirtual bool isOfType(QString type);" << endl;
          *iHeader << "\t\tvirtual QStringList inheritedTypes(void);" << endl;
          if (parentClass.count() > 0){
                QString pc;
                pc = parentClass[0].split(QRegExp("\\s+"),QString::SkipEmptyParts).last();
                *iHeader << "\t\tvirtual int nProperties(void) {return " << pc << "::nProperties()+"<< command.count() << ";}" << endl;
                *iHeader << "\t\tint nInheritedProperties(void) {return " << pc << "::nProperties();}" << endl;
                *iHeader << "\t\tvirtual bool setPropertyValue(int index, tString type, void* value);" << endl
                       << endl;
                if (action.count() > 0) {
                    *iHeader << "\t\t//Actions:" << endl;
                    *iHeader << "\t\tvirtual int nActions(void) {return " << pc << "::nActions()+" << action.count() << ";}" << endl;
                    *iHeader << "\t\tint nInheritedActions(void) {return " << pc << "::nActions();}" << endl;
                    *iHeader << "\t\tvirtual QString getActionName(int index);" << endl;
                    *iHeader << "\t\tvirtual void runAction(int index);" << endl
                           << endl;
                }

          }


          *iHeader << "};" << endl;
          *iHeader << "#endif /*" << iClassName.toUpper() << "_H_*/" << endl ;


          // Die CPP-Datei erzeugen...
          *iCpp << "#include \"" << iInfo.fileName() << "\"" << endl;
          *iCpp << "#include \"" << fInfo.fileName() << "\"" << endl << endl;


          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          // Konstruktor
          *iCpp << iClassName << "::" << iClassName <<"(tElement *el):";
          for (j=0;j<parentClass.count();j++){
            *iCpp << parentClass[j]<< "(el)";
            if (j!=parentClass.count()-1){
              *iCpp << ", ";
            } else {
              *iCpp << endl << "{" << endl << "}" <<  endl << funcSeparator;
            }
          }

          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          // Destruktor
          *iCpp << iClassName << "::~" << iClassName <<"()\n{\n}\n" << funcSeparator;


          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //Die Namen der Eigenschaften
          *iCpp << "tString " << iClassName << "::getPropertyName(int index)" << endl
                << "{" << endl;
          for (j=0;j<command.count();j++){
            if (j==0){
              *iCpp << "\tif (index == nInheritedProperties()){" << endl;
            } else {
              *iCpp << "\t} else if (index == nInheritedProperties()+ " << j << "){" << endl;
            }
            *iCpp << "\t\treturn \"" << command[j] << "\";" << endl;
          }
          *iCpp << "\t} else {" << endl
                << "\t\treturn "<< parentClass[0] << "::getPropertyName(index);" << endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;

          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //Der Typ der Eigenschaft:
          *iCpp << "tString "<<  iClassName << "::getPropertyType(int index)" << endl
                << "{" << endl;
          for (j=0;j<type.count();j++){
            if (j==0){
              *iCpp << "\tif (index == nInheritedProperties()){" << endl;
            } else {
              *iCpp << "\t} else if (index == nInheritedProperties()+" << j<< "){" << endl;
            }
            *iCpp << "\t\treturn \"" << type[j] << "\";" << endl;
          }
          *iCpp << "\t} else {" << endl
                << "\t\treturn "<< parentClass[0] << "::getPropertyType(index);" << endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;

          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          // Den Wert einer Eigenschaft zurueckgeben
          *iCpp << "bool " << iClassName << "::getPropertyValue(int index, tString propType, void* value)" << endl
                << "{" << endl
                << "\tif (index == 0 && propType == \"String\"){" << endl
                << "\t\t*(tString*)value = "<< iClassName << "::theType();" << endl
                << "\t\treturn true;" << endl;
          for (j=0;j<command.count();j++){
            *iCpp << "\t} else if (index == nInheritedProperties()+" << j << " && " << getPropertyTypeMatcher(type[j], "propType") << ") {" << endl;
            if (readable[j] != voidFunction){
              QString castedType = castType(type[j], readPointer);
              *iCpp << "\t\t*" << castedType << "value = ((t" << className << "*)element)->" << readable[j] << "();" << endl
                    << "\t\treturn true;" << endl;
            } else {
              *iCpp << "\t\t The parameter is not readable. The interface description of <" <<command[j]<< "> is invalid."<< endl
                    << "\t\treturn false;" << endl;
            }
          }
          *iCpp << "\t} else {" << endl
                << "\t\treturn " << parentClass[0] << "::getPropertyValue(index,propType,value);" << endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;

          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          // Die Schreibfunktion fuer die Eigenschaften
          *iCpp << "bool " << iClassName << "::setPropertyValue(int index, tString type, void* value)" << endl
                << "{" << endl;
          if (writeable.count() == 0){
            *iCpp << "return " << parentClass[0] << "setPropertyValue(index,type,value);" << endl;
          } else {
            // call set-Function of parentClass first.
            // This will delete linked properties (if there is one).
            *iCpp << "\tif (" << parentClass[0] << "::setPropertyValue(index,type,value)){" << endl
                  << "\t\treturn true;" << endl;

            for (j=0;j<writeable.count();j++){
              *iCpp << "\t} else if";
              if (writeable[j] != voidFunction){
                QString castedType = castType(type[j], setPointer);
//                //--
//                *iCpp << "(index == nInheritedProperties()+" << j << " && type == \"" << type[j] << "\"){" << endl
//                --//
                *iCpp << "(index == nInheritedProperties()+" << j << " && " << setPropertyTypeMatcher(type[j]) << ") {" << endl


                      << "\t\t((t" << className <<"*)element)->" << writeable[j] << "(" << castedType << "value);" << endl
                      << "\t\treturn true;" << endl;
              } else {
                *iCpp << "(index == nInheritedProperties()+" << j << "){" << endl
                      << "\t\treturn false;" << endl;
              }
            }
            *iCpp << "\t} else {" << endl
                  << "\t\treturn false;" << endl
                  << "\t}" << endl;
          }
          *iCpp << "}" << endl
                << funcSeparator;

          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //Gibt zurueck, ob Eigenschaft nur lesbar ist.
          *iCpp << "bool " << iClassName << "::isReadOnly(int index)" << endl
                << "{" << endl;
          for (j=0; j<writeable.count(); j++){
            if (j==0){
              *iCpp << "\tif (index == nInheritedProperties()){" << endl;
            } else {
              *iCpp << "\t} else if (index == nInheritedProperties()+" << j << "){" << endl;
            }
            if (writeable[j] != voidFunction){
              *iCpp << "\t\treturn false;" << endl;
            } else {
              *iCpp << "\t\treturn true;" << endl;
            }
          }
          if (writeable.count() == 0){
            *iCpp << "\treturn " << parentClass[0] << "::isReadOnly(index);" << endl;
          } else {
            *iCpp << "\t} else {" << endl
                  << "\t\treturn " << parentClass[0] << "::isReadOnly(index);" << endl
                  << "\t}" << endl;
          }
          *iCpp << "}" << endl
                << funcSeparator;


          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //Gibt zurueck ob Eigenschaft nur optional ist. (Eine optionale Eigenschaft wird bspw beim Speichern nicht benoetigt.)
          *iCpp << "bool " << iClassName << "::isOptional(QString propName)" << endl
                << "{" << endl
                << "  if (QString(\"" << optionalProperties << "\").contains(\",\" + propName + \",\")) {"<< endl
                << "    return true;" << endl
                << "  } else {" << endl
                << "    return " + parentClass[0] + "::isOptional(propName);" << endl
                << "  }" << endl
                << "}" << endl
                << funcSeparator;
          //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          //Gibt eine Liste mit den Namen der Klassen von der diese Klasse abgeleitet ist.
          *iCpp << "QStringList " << iClassName << "::inheritedTypes(void)" << endl
                << "{" << endl
                << "\tQString type;" << endl
                << "\t" << iClassName << "::getPropertyValue(0,\"String\",&type);" << endl
                << "\treturn (" << parentClass[0] << "::inheritedTypes() << theType());" << endl
                << "}" << endl
                << funcSeparator;

          *iCpp << "bool " << iClassName << "::isOfType(QString thetype)" << endl
                << "{" << endl
                << "\tif (theType() == thetype){" << endl
                << "\t\treturn true;" << endl
                << "\t} else {" << endl
                << "\t\treturn " << parentClass[0] << "::isOfType(thetype); " <<  endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;


          //-----------------------------------------------------------------------------
          if (action.count() > 0) {
            *iCpp << endl;
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //Die Namen der Eigenschaften
            *iCpp << "QString " << iClassName << "::getActionName(int index)" << endl
                << "{" << endl;
            for (j=0;j<action.count();j++){
                QString act = action.keys()[j];
                if (j==0){
                  *iCpp << "\tif (index == nInheritedActions()){" << endl;
                } else {
                  *iCpp << "\t} else if (index == nInheritedActions()+ " << j << "){" << endl;
                }
                *iCpp << "\t\treturn \"" << act << "\";" << endl;
            }
            *iCpp << "\t} else {" << endl
                << "\t\treturn "<< parentClass[0] << "::getActionName(index);" << endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            //Die Action starten
            *iCpp << "void " << iClassName << "::runAction(int index)" << endl
                << "{" << endl;
            for (j=0;j<action.count();j++){
                QString act = action.keys()[j];
                if (j==0){
                  *iCpp << "\tif (index == nInheritedActions()){" << endl;
                } else {
                  *iCpp << "\t} else if (index == nInheritedActions()+ " << j << "){" << endl;
                }
                *iCpp << "\t\t((t" << className << "*)element)->" << act << "();" << endl;
            }
            *iCpp << "\t} else {" << endl
                << "\t\t"<< parentClass[0] << "::runAction(index);" << endl
                << "\t}" << endl
                << "}" << endl
                << funcSeparator;
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
          }


          delete iHeader;
          if (iCpp) delete iCpp;
          iHeaderFile.close();
          iCppFile.close();

        }
      } else {
        cout << "interface is up to date!" << endl;
      }


      // Create SIP-File
      bool isSipUpToDate = false;

      // Die Header Datei erzeugen...
      // Zunaechst ueberpruefen, ob das Interface evtl. noch aktuell ist.
      if (sipInfo.exists()){
        sipFile.open(QIODevice::ReadOnly);
        QTextStream sip(&sipFile);
        while (!sip.atEnd() && isSipUpToDate == false){
          QString line = sip.readLine();
          if (   line.startsWith("//")
                 && line.contains(fInfo.fileName())){
            // Datum extrahieren
            int start, length;
            start = line.indexOf("(")+1;
            length = line.indexOf(")")-start;
            line = line.mid(start,length);
            if (line == fInfo.lastModified().toString()){
              isSipUpToDate = true;
            }
          }
        }
        sipFile.close();
      }
      if ((!isSipUpToDate || forceMode) && sipFile.open(QIODevice::WriteOnly)){
        // Die SIP-Datei anlegen

        QTextStream sip(&sipFile);

        writeHeader(sip, fInfo);

        // enums schreiben:
        if (enums.count()){
          for (int j=0;j<enums.count();j++){
            sip << enums[j] << endl;
          }
          sip << endl;
        }

        sip << "class t" << className << " : ";
        for (j=0;j<tparentClass.count();j++){
          sip << tparentClass[j];
          if (j!=tparentClass.count()-1){
            sip << ", ";
          }
        }

        if (isAbstract){
          sip << " /Abstract/";
        }
        sip << " {" << endl
            << endl
            << "%TypeHeaderCode" << endl
            << "#include \"t" << className << ".h\"" << endl
            << "%End" << endl
            << endl;

        sip << "public:" << endl
            << "\t" <<  constructor << ";" << endl
            << "\t" << "virtual ~t" << className << "();" << endl
            << endl;
        for (int i=0; i<publicFuncs.count(); i++){
          sip << "\t" << publicFuncs[i] << endl;
        }
        sip << "};" << endl;
        sipFile.close();
      }


      file.close();
    } else {
        cout << "warning: class \""  << className.toStdString() << "\" has no interface." << endl;
    }
  }
}
//------------------------------------------------------------------------------------------------------------------

int main (int argc, char *argv[]){
  int i;
  QFileInfo fInfo;

  debugMode = false;
  forceMode = false;
  if (argc < 2){
    fInfo.setFile(argv[0]);
    cout << "error: invalid program call! Try: \"" << fInfo.fileName().toStdString() << " myElement.h\"" << endl;
  } else {
    for (i=1;i<argc;i++){
      if (QString("-debug")==argv[i]){
        debugMode = true;
      } else if (QString("-force")==argv[i]){
        forceMode = true;
      } else {
        processHeaderFile(argv[i]);
      }
    }
  }
}
