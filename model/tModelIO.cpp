#include "tModelIO.h"
#include "model/tPatExport.h"
#include "model/tPclExport.h"
#include "element/surface/tPropSurface.h"
#include "classes/tVectorStringConverter.h"

#ifdef BUILD_WITH_DXFLIB
    #include "model/tDxfExport2.h"
#endif
//#include "element/tPropertyLinker.h"
#include <stdio.h>


#define jrInt "Int"
#define jrReal "Real"
#define jrVector "Vector"
#define jrBool "Bool"
#define jrString "String"
#define jrRGB "RGB"

#define propertySplitter ';'


tModelIO::tModelIO(tModel *m)
{
	model = m;
	currentFileName = "";
}
//-----------------------------------------------------------------------------

tModelIO::~tModelIO()
{
}
//-----------------------------------------------------------------------------
/*
tVector tModelIO::vectorize(QString str){
	QStringList Vector;
	tVector x;
	int i;
	bool ok;
	tReal value;

  Vector = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);
	for (i=0;i<3 && i<Vector.count();i++){
		value = Vector[i].toFloat(&ok);
		if (!ok){
			value = funcs.calc(Vector[i]);
		}
		*x[i] = value;
  }
  return x;
}*/
//-----------------------------------------------------------------------------

tRGB tModelIO::colorize(QString str){
	QStringList Vector;
	tRGB rgb;
  Vector = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);
  if (Vector.count() > 2){
    rgb.red = (unsigned char)Vector[0].toFloat();
    rgb.green = (unsigned char)Vector[1].toFloat();
    rgb.blue = (unsigned char)Vector[2].toFloat();
  }
  return rgb;
}
//-----------------------------------------------------------------------------

bool tModelIO::fromXmlFile(QString fileName,
													 QHash<QString,tElement*> *elName,
													 QHash<QString,QDomElement> *macro){

	QFile file;
	QString oldFileName;
  QDomDocument doc;

  QString jobName;

  QDir dir;
  QFileInfo fileInfo;
  QString currentPath;
  // in den Ordner wechseln, um bei rekursiven Aufrufen
  // relative Pfade bestimmen zu koennen.
  currentPath = QDir::currentPath();
  fileInfo.setFile(fileName);
  dir.setCurrent(fileInfo.path());


//  // Bei absoluter Pfadangabe
  file.setFileName(fileName);
//  // Ansonsten relativ zur zu letzt bearbeiteten Datei.
//  if (!file.exists()){
//  	QFileInfo fi(currentFileName);
//  	file.setFileName(fi.path()+"/"+fileName);
//  	if (file.exists()){
//  		fileName = fi.absolutePath()+"/"+fileName;
//  	}
////  	printf((file.fileName().toLatin1().data()));
//  }

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
  	fErrorMessages << "Can't read the given file: \"" + fileName +"\"";
    QDir::setCurrent(currentPath);
   	return false;
  } else {
    QDomElement root;
    //tReal ver;
  	oldFileName = currentFileName;
		currentFileName = fileName;

    doc.setContent(&file);
    root = doc.documentElement();
    bool ok = (fromXmlElement(root,elName, macro));

    currentFileName = oldFileName;
    QDir::setCurrent(currentPath);
    file.close();

    return (ok);
  }
}
//-----------------------------------------------------------------------------

bool tModelIO::fromXmlElement(const QDomElement& el, QHash<QString,tElement*> *elName, QHash<QString,QDomElement> *macro)
{
  bool ok = true;

  tVersion version(el.attribute("version","1.0"));
  //ver = root.attribute("version","1.0").toFloat();
  if (version.branch() >= 2){
    ok = executeXml_2xx(el, version);
  } else {
    ok = false;
  }
  return (ok);
}

//-----------------------------------------------------------------------------
//bool tModelIO::fromJRFile(QString fileName){
//
//	return true;
//}
//-----------------------------------------------------------------------------

bool tModelIO::toXmlFile(QString fileName){

  QDomDocument *XML;
  QDomElement root;
  QFile file;
  QString docType;

  docType = "JR_Geometry";

  file.setFileName(fileName);

  if (file.open(QIODevice::WriteOnly)){

	  XML = new QDomDocument(docType);
    root = XML->createElement(docType);
    root.setAttribute("version","2.01");
    XML->appendChild(root);
		if (!modelToXml(root)){
			return false;
		} else {
	// XML in eine Datei schreiben
	    QTextStream stream(&file);
	    stream << XML->toString();
	    file.close();
	    delete XML;
	    return true;
		}
  } else {
  	fErrorMessages << "Can't write the given file: \"" + fileName + "\"";
  	return false;
  }
}
//-----------------------------------------------------------------------------

bool tModelIO::modelToXml(QDomElement m){
    bool error = false;
    tVector x;
    QDomDocument doc;

    doc = m.ownerDocument();

    QHash<QString, tElement*> processedNames;
    QHash<tElement*, QString> processedElements;

    for (int i=0; i<model->nElements(); i++){
        elementToXml(model->element(i),doc, m, processedElements, processedNames);
    }

    return !error;
}
//-----------------------------------------------------------------------------

void tModelIO::elementToXml(tElement *el, QDomDocument &doc, QDomElement &parentElement, QHash<tElement *, QString> &processedElements, QHash<QString, tElement *> &processedNames)
{
  if (el){
    QString type, name, originalName, propType, propName;
    int i, nProperties;
    iElement *iface;
    QDomElement e, prop;

    iface = el->intrface();
    nProperties = iface->nProperties();
    originalName = iface->name();
    type = iface->type();

    name = originalName;
    i = 0;

    while (processedNames.contains(name) || name.length()==0){
      name = "__"+QString::number(++i)+":"+originalName;
    }

    processedElements.insert(el,name);
    processedNames.insert(name,el);

    e = doc.createElement(type);
    e.setAttribute("name",name);
    for (i=2; i<nProperties; i++){
      propName = iface->getPropertyName(i);
      if (!iface->isReadOnly(i) && !iface->isOptional(propName)){
        // the property is read- and writeable and is required to store the necessary data.
        prop = doc.createElement(propName);
        propType = iface->getPropertyType(i);

        if (propType == jrInt){
          int value;
          iface->getPropertyValue(i,propType,&value);
          prop.setAttribute(propType,QString::number(value));
        } else if (propType == jrReal){
          tReal value;
          iface->getPropertyValue(i,propType,&value);
          prop.setAttribute(propType,QString::number(value));
        } else if (propType == jrVector){
          tVector value;
          iface->getPropertyValue(i,propType,&value);
          prop.setAttribute(propType,tVectorStringConverter::toString(value, " "));
        } else if (propType == jrRGB){
          tRGB value;
          iface->getPropertyValue(i,propType,&value);
          prop.setAttribute(propType,tVectorStringConverter::toString(value.toVector(), " "));
        } else if (propType == jrString){
          QString value;
          iface->getPropertyValue(i,propType,&value);
          prop.setAttribute(propType,value);
        } else if (propType == jrBool){
          bool value;
          iface->getPropertyValue(i,propType,&value);
          if (value){
            prop.setAttribute(propType,"true");
          } else {
            prop.setAttribute(propType,"false");
          }
        } else {
          // otherwise it is a referenced element or a list.
          if (propType.endsWith("List")){
            // the property is a list
            int k,length;
            QString listPropType;
            QString propValue;
            listPropType = propType;
            listPropType.remove(propType.length()-4,4);

            if (listPropType == jrInt){
              tList<int> value;
              iface->getPropertyValue(i,propType,&value);
              for (k=0;k<value.count();k++){
                propValue.append(QString::number(value.at(k))+propertySplitter);
              }
              length = propValue.length()-1; // Remove the last semicolon
              propValue.remove(length,1);
              prop.setAttribute(propType,propValue);
            } else if (listPropType == jrReal){
              tList<tReal> value;
              iface->getPropertyValue(i,propType,&value);
              for (k=0;k<value.count();k++){
                propValue.append(QString::number(value.at(k))+propertySplitter);
              }
              length = propValue.length()-1; // Remove the last semicolon
              propValue.remove(length,1);
              prop.setAttribute(propType,propValue);
            } else if (listPropType == jrBool){
              tList<bool> value;
              iface->getPropertyValue(i,propType,&value);
              for (k=0;k<value.count();k++){
                if (value.at(k)){
                  propValue.append("true"+propertySplitter);
                } else {
                  propValue.append("false"+propertySplitter);
                }
              }
              length = propValue.length()-1; // Remove the last semicolon
              propValue.remove(length,1);
              prop.setAttribute(propType,propValue);
            } else if (listPropType == jrString){
              tList<QString> value;
              iface->getPropertyValue(i,propType,&value);
              for (k=0;k<value.count();k++){
                propValue.append(value.at(k)+propertySplitter);
              }
              length = propValue.length()-1; // Remove the last semicolon
              propValue.remove(length,1);
              prop.setAttribute(propType,propValue);
            } else {
              // the property contains a list of elements
              tList<tElement*> value;
              tElement *reference;
              iface->getPropertyValue(i,propType,&value);
              for (k=0;k<value.count();k++){
                // look at each element and check if it is already processed. If not, process it before proceeding further.
                reference = value.at(k);
                if (!reference){
                  // the entry is empty so add ""; instead
                  propValue.append(propertySplitter);
                } else {
                  if (reference && !processedElements.contains(reference)) {
                    elementToXml(reference, doc, parentElement, processedElements, processedNames);
                  }
                  propValue.append(processedElements.value(reference)+propertySplitter);
                }
              }
              length = propValue.length()-1; // Remove the last semicolon
              propValue.remove(length,1);
              prop.setAttribute(propType,propValue);
            }

          } else {
            // the property contains an element
            tElement *reference;
            iface->getPropertyValue(i,propType,&reference);
            if (reference && !processedElements.contains(reference)) {
              elementToXml(reference, doc, parentElement, processedElements, processedNames);
            }
            prop.setAttribute(propType,processedElements.value(reference));//processedElements->key(reference));
          }
        }
        e.appendChild(prop);
      }
    }
    parentElement.appendChild(e);
  }
}
//-----------------------------------------------------------------------------

bool tModelIO::executeXml_2xx(QDomElement job, tVersion version)
{
  QDomElement el, propEl;
  int propIndex;

  tLayer *defaultImportLayer;
  if (version.revision() < 1){
    defaultImportLayer = model->addLayer("Default Layer");
  } else {
    defaultImportLayer = model->addLayer("def.ImportLayer");
  }


  tElement *e;
  iElement *intrface;
  QString elType, elName,
          propType, propName;

  tList<tElement*> cleanUpNames;

  el = job.firstChildElement();

  while (el.isElement()){
    elType = el.tagName();
    elName = el.attribute("name","");
    e = defaultImportLayer->addElement(elType, elName);

    if (e){
      intrface = e->intrface();
      intrface->setName(elName);
      if (elName.startsWith("__")){
        cleanUpNames.append(e);
      }


      propEl = el.firstChildElement();
      while (!propEl.isNull()){
        bool ok = true;
        // Die Eigenschaften abarbeiten
        propName = propEl.tagName();


        propIndex = intrface->getPropertyIndex(propName);
        if (propIndex>=0){
          propType = intrface->getPropertyType(propIndex);
          if (propType == "Int"){
            int value = (int)propEl.attribute(propType,"0").toFloat(&ok);
            intrface->setPropertyValue(propIndex,propType,&value);
          } else if (propType == "Real") {
            tReal value = propEl.attribute(propType,"0").toDouble(&ok);
            intrface->setPropertyValue(propIndex,propType,&value);
          } else if (propType == "Bool") {
            QString attribute;
            attribute = propEl.attribute(propType,"false");
            if (attribute.contains("->")) {
              ok = false;
            } else {
              bool value= !(attribute=="false" || attribute=="0");
              intrface->setPropertyValue(propIndex,propType,&value);
            }
          } else if (propType == "String") {
            QString value = propEl.attribute(propType,"");
            if (value.contains("->")){
              ok = false;
            } else {
              intrface->setPropertyValue(propIndex,propType,&value);
            }
          } else if (propType == "Vector") {
            tVector value = tVectorStringConverter::toVector(propEl.attribute(propType,"0 0 0"),QRegExp(" "),&ok);
            intrface->setPropertyValue(propIndex,propType,&value);
          } else if (propType == "RGB") {
            tRGB value = colorize(propEl.attribute(propType,"30,180,10"));
            intrface->setPropertyValue(propIndex,propType,&value);
          } else if (propType.endsWith("List")){
            QString listPropType = propType;
            listPropType.remove(propType.length()-4,4);
            QStringList value;
            int i;
            if (listPropType == "Int"){
              tList<int> list;
              value = propEl.attribute(propType).split(propertySplitter,QString::KeepEmptyParts);
              for (i=0;i<value.count();i++){
                list.append((int)value.at(i).toFloat());
              }
              intrface->setPropertyValue(propIndex,propType,&list);
            } else if (listPropType == "Real"){
              tList<tReal> list;
              value = propEl.attribute(propType).split(propertySplitter,QString::KeepEmptyParts);
              for (i=0;i<value.count();i++){
                list.append(value.at(i).toDouble());
              }
              intrface->setPropertyValue(propIndex,propType,&list);
            } else if (listPropType == "Bool"){
              tList<bool> list;
              value = propEl.attribute(propType).split(propertySplitter,QString::KeepEmptyParts);
              for (i=0;i<value.count();i++){
                if (value.at(i)=="false" || value.at(i)=="0"){
                  list.append(false);
                } else {
                  list.append(true);
                }
              }
              intrface->setPropertyValue(propIndex,propType,&list);
            } else if (listPropType == "String"){
              tList<QString> list;
              value = propEl.attribute(propType).split(propertySplitter,QString::KeepEmptyParts);
              for (i=0;i<value.count();i++){
                list.append(value.at(i));
              }
              intrface->setPropertyValue(propIndex,propType,&list);
            } else {
              // the propType holds a list of elements
              tList<tElement*> list;

              value = propEl.attribute(propType,"").split(propertySplitter,QString::KeepEmptyParts);
              for (i=0;i<value.count();i++){
                tElement *el = model->currentLayer()->elementByName(value.at(i),listPropType);
                list.append(el);
              }
              intrface->setPropertyValue(propIndex,propType,&list);
            }
          } else {
            // alle anderen tElement-Typen
            QString refName;
            refName = propEl.attribute(propType,"");
            if (refName.contains("->")){
              ok = false;
            } else {
              intrface->setPropertyValue(propIndex,propType,model->elementByName(refName, propType));
            }
          }

          if (!ok){
            // Property-value could not be interpreted yet, now its tested if it can be linked to a property
            // of a differnt element.
            /*
            QStringList propValue = propEl.attribute(propType,"").split("->",QString::KeepEmptyParts);
            if (propValue.count()==2){
              tElement *sender;
              sender = model->elementByName(propValue.at(0));
              if (sender){
                new tPropertyLinker(e,propName,sender,propValue.at(1),&ok);
              }
            }*/
          }
        }
        propEl = propEl.nextSiblingElement();
      }
    }
    el = el.nextSiblingElement();
  }

  // autmatische Erweiterung doppelt vorhandener Namen aufheben.
  for (int i=0; i<cleanUpNames.count(); i++){
    tElement* el;
    el = cleanUpNames.at(i);

    QString elName = el->intrface()->name();
    elName.remove(QRegExp("^__[0-9]+:"));
    el->intrface()->setName(elName);
  }
  cleanUpNames.clear();

  // clear and remove defaultImportLayer, but install the topmost layers in the model first.
  if (version.revision() >= 1){
    tList<tElement*> layers = defaultImportLayer->elements(iLayer::theType());
    for (int i=0; i<layers.count(); i++){
      bool foundParentLayer = false;
      tLayer* importedLayer = dynamic_cast<tLayer*>(layers.at(i));
      tList<tElement*> dependents = importedLayer->dependents();
      for (int j=0; j<dependents.count(); j++){
        tLayer *l = dynamic_cast<tLayer*>(dependents.at(j));
        if (l && l!= defaultImportLayer){
          foundParentLayer = true;
        }
      }
      if (!foundParentLayer){
        model->append(importedLayer);
      }
    }
    model->removeElement(defaultImportLayer);
  }
  return true;
}
//-----------------------------------------------------------------------------
/*
bool tModelIO::executeXml(QDomElement mm,
													QHash<QString,tElement*> *elName,
													QHash<QString,QDomElement> *macro){

	int i;
	bool error,allRefs,newItems,tagIsHandled,isVisible;
	QDomElement m,tag,tag1;
	QDomNode node;
	QString name,type,job,func;
	QStringList refs;


	tElement *e,*ref1;
	tSurface *surf;
	tCurve *curve;
	tList<tElement*> refList;
	iElement *I;
	tVector x;
	tReal t;
	tRGB rgb;

	if (!elName){
		elName = new QHash<QString,tElement*>;
	}
	if (!macro){
		macro = new QHash<QString,QDomElement>;
	}

	error = false;
	name = mm.tagName();
	if (name == "JR_Geometry" || name == "loop" || name =="if" || name == "macro"){
		m = mm.cloneNode(true).toElement();
	}	else {
		error = true;
	}

	if (!error){
		tag = m.firstChildElement();
		do {
			newItems = false;
			do {
				tagIsHandled = false;
				if (tag.tagName() == "loop"){
					if (tag.hasAttribute("repeat")){
						func = tag.attribute("repeat","1");
						i = (int)funcs.calc(func);
						while(i>0){
							executeXml(tag,elName,macro);
							i--;
						}
					} else if (tag.hasAttribute("while")){
						func = tag.attribute("while","");
						while (funcs.calc(func)!=0){
							executeXml(tag,elName,macro);
						}
					}
					tagIsHandled = true;
				}	else if (tag.tagName() == "if"){
					func = tag.attribute("condition","");
					if (funcs.calc(func)!=0){
						executeXml(tag,elName,macro);
					}
					tagIsHandled = true;
				} else if (tag.tagName() == "math"){
					func = tag.attribute("func","");
					funcs.setFunc(func);
					tagIsHandled = true;
				} else if (tag.tagName() == "call"){
					if (tag.hasAttribute("file")){
						job = tag.attribute("file","");
						fromXmlFile(job, elName, macro);
					} else if (tag.hasAttribute("macro")){
						job = tag.attribute("macro","");
						if (macro->contains(job)){
							executeXml(macro->value(job),elName,macro);
						}
					}
					tagIsHandled = true;
				} else if (tag.tagName() == "macro"){
					job = tag.attribute("name","");
					if (!job.isEmpty()){
						if (macro->contains(job)){
							tag1 = macro->value(job);
							tag1.clear();
							macro->remove(job);
						}
						tag1 = tag.cloneNode(true).toElement();
						macro->insert(job,tag1);
					} else {
						fErrorMessages << "The macro doesn't have a name and can't be used.";
					}
					tagIsHandled = true;
				} else if (tag.tagName() == "print"){
					if (tag.hasAttribute("func")){
						job = tag.attribute("func","");
						t = funcs.calc(job);
						printf("%s: %f\n",job.toLatin1().data(),t);
					}
					tagIsHandled = true;
				} else {
					// Es werden alle Supports bestimmt und geprueft, ob diese bereits
					// geladen wurden. Wenn ja (allRefs = true) kann das Element
					// bearbeitet werden, ansonsten ist das naechste an der Reihe.
					refs.clear();
					tag1 = tag.firstChildElement();
					do {
						refs += tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
						tag1 = tag1.nextSiblingElement();
					} while (!tag1.isNull());
					allRefs = true;
					for (i=0;i<refs.count();i++){
						refs[i] = resolveName(refs.at(i));
						if (!elName->contains(refs.at(i))) {
						  tElement *el;
						  el = model->currentLayer()->elementByName(refs.at(i));
						  if(el){
						    elName->insert(refs.at(i),el);
						  } else {
                //printf((tag.tagName()+": No: "+refs[i]+"\n").toLatin1().data());
                allRefs = false;
                //i = refs.count();
						  }
						}
					}
					if (allRefs){

						type = tag.tagName();

	  				name = resolveName(tag.attribute("name"));

						tag1 = tag.firstChildElement("color");
						rgb = colorize(tag1.attribute("rgb","255 255 0"));


						if (!tag.firstChildElement("invisible").isNull()){
							isVisible = false;
						} else {
							tag1 = tag.firstChildElement("visibility");
							t = 1.;
							if (!tag1.isNull()){
								t = funcs.calc(tag1.attribute("status","1"));
							}
							if (t==0){
								isVisible = false;
							} else {
								isVisible = true;
							}
						}

						if (type == "Point"){
							tag1 = tag.firstChildElement("position");
							x = vectorize(tag1.attribute("vector","0 0 0"));

							e = model->currentLayer()->addPoint(x);
							tagIsHandled = true;

						} else if (type == "RelPoint"){
							tag1 = tag.firstChildElement("refPoint");
							ref1 = elName->value(resolveName(tag1.attribute("reference","")));

							tag1 = tag.firstChildElement("offset");
							x = vectorize(tag1.attribute("vector","0 0 0"));

							e = model->currentLayer()->addRelPoint((tDot*)ref1,x);
							tagIsHandled = true;

						} else if (type == "AbsBead"){
							tag1 = tag.firstChildElement("refCurve");
							ref1 = elName->value(resolveName(tag1.attribute("reference","")));

							tag1 = tag.firstChildElement("location");
							t = funcs.calc(tag1.attribute("real"));
							if (ref1){
								e = model->currentLayer()->addAbsBead((tCurve*)ref1,t);
								tagIsHandled = true;
							}

						} else if (type == "AbsMagnet"){
							tReal u,v;
							tag1 = tag.firstChildElement("refSurface");
							ref1 = elName->value(resolveName(tag1.attribute("reference","")));

							tag1 = tag.firstChildElement("u");
							u = funcs.calc(tag1.attribute("real"));
							tag1 = tag.firstChildElement("v");
							v = funcs.calc(tag1.attribute("real"));

							e = model->currentLayer()->addAbsMagnet(ref1,u,v);
							tagIsHandled = true;

						} else if (type == "OffsetPoint"){
							tag1 = tag.firstChildElement("refSurface");
							ref1 = elName->value(resolveName(tag1.attribute("reference","")));

							tag1 = tag.firstChildElement("offset");
							x = vectorize(tag1.attribute("vector","0 0 0"));

							e = model->currentLayer()->addOffsetPoint(ref1,x.x,x.y,x.z);
							tagIsHandled = true;

						} else if (type == "RotatedPoint"){
							tElement *p,*axis;
							tag1 = tag.firstChildElement("refPoint");
							p = elName->value(resolveName(tag1.attribute("reference","")));
							tag1 = tag.firstChildElement("axis");
							axis = elName->value(resolveName(tag1.attribute("reference","")));

							tag1 = tag.firstChildElement("angle");
							t = funcs.calc(tag1.attribute("Real"));

							e = model->currentLayer()->addRotatedPoint(p,axis,t);
							tagIsHandled = true;
						} else if (type == "RotatedCurve"){
							refList.clear();
							tag1 = tag.firstChildElement("refCurve");
							refList.append(elName->value(resolveName(tag1.attribute("reference",""))));
							tag1 = tag.firstChildElement("axis");
							refList.append(elName->value(resolveName(tag1.attribute("reference",""))));

							tag1 = tag.firstChildElement("angle");
							t = funcs.calc(tag1.attribute("real"));

							e = model->currentLayer()->addRotatedCurve(refList.at(0),refList.at(1),t);
							tagIsHandled = true;
						} else if (type == "Line"){
							if (refs.count() > 0){
								refList.clear();
								refList.append(elName->value(refs.at(0)));
								if (refs.count() > 1){
									refList.append(elName->value(refs.at(1)));
								} else {
									refList.append(refList.at(0));
								}

								e = model->currentLayer()->addLine((tDot*)refList.at(0),(tDot*)refList.at(1));
								tagIsHandled = true;
							} else {
								fErrorMessages << "The Line-Element called \""+name+ "\" does not have enough references.";
							}
            } else if (type == "CSpline"){
              if (refs.count() > 0){
                refList.clear();
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(refs.at(i)));
                }
                e = model->currentLayer()->addCSpline(&refList);
                if (!tag.firstChildElement("lengthBased").isNull()){
                  ((tCSpline*)e)->setCSplineType(jrCSLengthBased);
                } else {
                  ((tCSpline*)e)->setCSplineType(jrCSVortexBased);
                }
                tagIsHandled = true;
              } else {
                fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
              }
            } else if (type == "BSpline"){
              if (refs.count() > 0){
                refList.clear();
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(refs.at(i)));
                }
                e = model->currentLayer()->addCSpline(&refList);
                tagIsHandled = true;
              } else {
                fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
              }
            } else if (type == "HermiteSpline"){
              tReal c,t,b;
              if (refs.count() > 0){
                refList.clear();
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(resolveName(refs.at(i))));
                }
                tag1 = tag.firstChildElement("properties");
                if (!tag1.isNull()){
                  c = tag1.attribute("continuity","0.").toDouble();
                  b = tag1.attribute("bias","0.").toDouble();
                  t = tag1.attribute("tension","0.").toDouble();
                }
                e = model->currentLayer()->addHermiteSpline(&refList, b, c, t);
                tagIsHandled = true;
              } else {
                fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
              }
            } else if (type == "MidCurve"){
              if (refs.count() > 0){
                refList.clear();
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(resolveName(refs.at(i))));
                }
                e = model->currentLayer()->addMidCurve(&refList);
                tagIsHandled = true;
              } else {
                fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
              }
            } else if (type == "SumCurve"){
              if (refs.count() > 0){
                refList.clear();
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(resolveName(refs.at(i))));
                }
                e = model->currentLayer()->addSumCurve(&refList);
                tagIsHandled = true;
              } else {
                fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
              }
            } else if (type == "SubCurve"){
              if (refs.count() > 0){
                refList.clear();
                refList.append(elName->value(refs.at(0)));
                if (refs.count() > 1){
                  refList.append(elName->value(refs.at(1)));
                } else {
                  refList.append(refList.at(0));
                }

                e = model->currentLayer()->addSubCurve((tAbsBead*)refList.at(0),(tAbsBead*)refList.at(1));
                tagIsHandled = true;
              } else {
                fErrorMessages << "The SubCurve-Element called \""+name+ "\" does not have enough references.";
              }
            } else if (type == "PolyCurve"){
              refList.clear();
              if (refs.count()){
                for (i=0;i<refs.count();i++){
                  refList.append(elName->value(refs.at(i)));
                }
                e = model->currentLayer()->addPolyCurve(&refList);
                if (!tag.firstChildElement("curveBased").isNull()){
                  ((tPolyCurve*)e)->setPolyCurveType(jrPCCurveBased);
                }
                if (!tag.firstChildElement("lengthBased").isNull()){
                  ((tPolyCurve*)e)->setPolyCurveType(jrPCLengthBased);
                }
                tagIsHandled = true;
              } else {
                fErrorMessages << "The PolyCurve-Element called \""+name+ "\" does not have enough references.";
              }
						} else if (type == "LineSnake"){
							tElement *m1,*m2;
							m1 = NULL;
							m2 = NULL;
							tag1 = tag.firstChildElement("begin");
							if (!tag1.isNull()){
								m1 = elName->value(resolveName(tag1.attribute("reference","")));
							}
							tag1 = tag.firstChildElement("end");
							if (!tag1.isNull()){
								m2 = elName->value(resolveName(tag1.attribute("reference","")));
							}
							e = model->currentLayer()->addLineSnake(m1,m2);
							tagIsHandled = true;
						} else if (type == "RuledSurf"){
							if (refs.count() > 0){
								refList.clear();
								refList.append(elName->value(refs.at(0)));
								if (refs.count() > 1){
									refList.append(elName->value(refs.at(1)));
								} else {
									refList.append(refList.at(0));
								}

								e = model->currentLayer()->addRuled((tCurve*)refList.at(0),(tCurve*)refList.at(1));
								tagIsHandled = true;
							} else {
								fErrorMessages << "The Ruled-Surface-Element called \""+name+ "\" does not have enough references.";
							}
						} else if (type == "CLoft"){
							if (refs.count() > 0){
								refList.clear();
								for (i=0;i<refs.count();i++){
									refList.append(elName->value(refs.at(i)));
								}
								e = model->currentLayer()->addCLoft(&refList);
								tagIsHandled = true;
							} else {
								fErrorMessages << "The "+type+"-Element called \""+name+ "\" has no supports.";
							}
						} else if (type == "RotatedSurface"){
                            tSurface *surf =NULL;
                            tLine *axis =NULL;

							tag1 = tag.firstChildElement("refSurface");
							if (!tag1.isNull()){
								refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
								if (refs.count()>0){
									refs[0] = resolveName(refs.at(0));
								}
								if (elName->contains(refs.at(0))) {
									surf = (tSurface*)elName->value(refs.at(0));
								} else {
									surf = NULL;
								}
							}
							tag1 = tag.firstChildElement("axis");
							if (!tag1.isNull()){
								refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
								if (refs.count()>0){
									refs[0] = resolveName(refs.at(0));
								}
								if (elName->contains(refs.at(0))) {
									axis = (tLine*)elName->value(refs.at(0));
								} else {
									axis = NULL;
								}
							}
							tag1 = tag.firstChildElement("rotationAngle");
							if (!tag1.isNull()){
								func = tag1.attribute("value","");
								t = funcs.calc(func);
							}
							if (surf && axis){
								e = model->currentLayer()->addRotatedSurface(surf,axis,t);
								tagIsHandled = true;
							} else {
								fErrorMessages << "The "+type+"-Element called \""+name+ "\" had invalid supports.";
							}
						} else if (type == "FunctionSurface"){
							tFunctionSurface *s;
							QString macroName;
							QDomElement macroEl,tag2;
							tag1 = tag.firstChildElement("refSurface");
							if (!tag1.isNull()){
								refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
								if (refs.count()>0){
									ref1 = elName->value(resolveName(refs.at(0)));
								}
							}

              s = model->currentLayer()->addFunctionSurface();
              s->addReference(ref1,ref1->intrface()->getPropertyString("name"));
              executeFunctionSurfaceXml((tFunctionSurface*)s, tag, macro);

								e = s;
								tagIsHandled = true;
//						} else if (type == "RevolvedSurface"){
//              tCurve *curve;
//              tLine *axis;
//              tReal t,t2;
//
//              tag1 = tag.firstChildElement("refCurve");
//              if (!tag1.isNull()){
//                refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
//                if (refs.count()>0){
//                  refs[0] = resolveName(refs.at(0));
//                }
//                if (elName->contains(refs.at(0))) {
//                  curve = (tCurve*)elName->value(refs.at(0));
//                } else {
//                  curve = NULL;
//                }
//              }
//              tag1 = tag.firstChildElement("axis");
//              if (!tag1.isNull()){
//                refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts); // Elemente in der Liste reference werden mit "," getrennt
//                if (refs.count()>0){
//                  refs[0] = resolveName(refs.at(0));
//                }
//                if (elName->contains(refs.at(0))) {
//                  axis = (tLine*)elName->value(refs.at(0));
//                } else {
//                  axis = NULL;
//                }
//              }
//              tag1 = tag.firstChildElement("angleStart");
//              if (!tag1.isNull()){
//                func = tag1.attribute("value","");
//                t = funcs.calc(func);
//              }
//              tag1 = tag.firstChildElement("angleEnd");
//              if (!tag1.isNull()){
//                func = tag1.attribute("value","");
//                t2 = funcs.calc(func);
//              }
//              if (curve && axis){
//                e = model->currentLayer()->addRevolvedSurface(curve,axis,t,t2);
//                tagIsHandled = true;
//              } else {
//                fErrorMessages << "The "+type+"-Element called \""+name+ "\" had invalid supports.";
//              }
            } else if (type == "SubSurface"){
              if (refs.count() > 0){
                refList.clear();
                refList.append(elName->value(refs.at(0)));
                if (refs.count() > 1){
                  refList.append(elName->value(refs.at(1)));
                } else {
                  refList.append(refList.at(0));
                }
                e = model->currentLayer()->addSubSurface(refList.at(0),refList.at(1));
                tagIsHandled = true;
              }

            } else if (type == "PropSurf"){
              QString fileName;
              tPropSurface *propSurf;
              fileName = tag.attribute("file","");
              QFileInfo fi(fileName);
              if (!fi.isAbsolute()){
                fi.setFile(currentFileName);
                fileName = fi.absolutePath()+"/"+fileName;
              }
              propSurf = dynamic_cast<tPropSurface*>(model->currentLayer()->addPropSurface(fileName));
              e = propSurf;
              tagIsHandled = true;
            } else if (type == "Group"){
							tGroup *g = NULL;
							if (elName->contains(name)){
								// Wenn die Gruppe bereits existiert kann diese veraendert werden.
								e = g = dynamic_cast<tGroup*>(elName->value(name));
							} else {
							  e = g = dynamic_cast<tGroup*>(model->currentLayer()->elementByName(name,"Group"));
							}
              if (!g){
								// Es wird eine neue Gruppe erstellt.
								e = g = model->currentLayer()->addGroup();
								tagIsHandled = true;
							}
							// Die Befehle fuer die Gruppe werden abgearbeitet.
							tag1 = tag.firstChildElement();
							do {
								job = tag1.tagName();
								// es werden die aktuellen Referenzen bestimmt.
								refs = tag1.attribute("reference","").split(",", QString::SkipEmptyParts);
								for (i=0;i< refs.count();i++){
									refs[i] = resolveName(refs.at(i));
								}
								if (job == "append"){ // die Punkte werden hinzugefuegt.
									for (i=0;i<refs.count();i++){
										g->append(elName->value(refs.at(i)));
								  }
								}else if (job == "prepend"){ // die Punkte werden hinzugefuegt.
									for (i=0;i<refs.count();i++){
										g->prepend(elName->value(refs.at(i)));
								  }
								} else if (job == "remove"){ // die angegebenen Elemente werden der Gruppe entnommen
									for (i=0;i<refs.count();i++){
										g->removeAllElements(elName->value(refs.at(i)));
								  }
								} else if (job == "removeAll"){ // Die Gruppe wird geleert.
									g->clear();
								} else if (job == "removeAllButLast"){ // Die Gruppe wird geleert.
									g->removeAllButLast();
								} else if (job == "removeAllButFirst"){ // Die Gruppe wird geleert.
									g->removeAllButFirst();
								} else if (job == "reverse"){ // Die Reihenfolge der Elemente wird umgekehrt.
									g->reverse();
								}
								tag1 = tag1.nextSiblingElement();
							} while (!tag1.isNull());
            } else if (type == "Structured2DInterpolGrid"){
              tStructured2DInterpolGrid *grid;
              QString distribOnEdge, refName;
              int neighbourEdge;

              grid = model->currentLayer()->add2DStructuredInterpolGrid();
              e = grid;
              tag1 = tag.lastChildElement("ni");
              if (!tag1.isNull()){
                grid->setNi((int)tag1.attribute("int","-1").toFloat());
              }
              tag1 = tag.lastChildElement("nj");
              if (!tag1.isNull()){
                grid->setNj((int)tag1.attribute("int","-1").toFloat());
              }
              tag1 = tag.lastChildElement("meshIterations");
              if (!tag1.isNull()){
                grid->setMeshIterations((int)tag1.attribute("int","-1").toFloat());
              }
              tag1 = tag.lastChildElement("orientation");
              if (!tag1.isNull()){
                bool value;
                value = (tag1.attribute("Bool","true").toLower() == "true");
                grid->setOrientation(value);
              }
              refs = tag.lastChildElement("corner").attribute("reference","").split(","); // Elemente in der Liste reference werden mit "," getrennt
              for (i=0; i<refs.count() && i<4; i++){
                if (elName->contains(resolveName(refs.at(i)))){
                  grid->setCorner(i,elName->value(refs.at(i)));
                }
              }
              refs = tag.lastChildElement("edge").attribute("reference","").split(","); // Elemente in der Liste reference werden mit "," getrennt
              for (i=0; i<refs.count() && i<4; i++){
                if (elName->contains(resolveName(refs.at(i)))){
                  grid->setEdge(i,elName->value(refs.at(i)));
                }
              }
              refs = tag.lastChildElement("base").attribute("reference","").split(","); // Elemente in der Liste reference werden mit "," getrennt
              for (i=0; i<refs.count() && i<1; i++){
                if (elName->contains(resolveName(refs.at(i)))){
                  grid->setBase(elName->value(refs.at(i)));
                }
              }
              tag1 = tag.firstChildElement("distribOnEdge");
              while (!tag1.isNull()){
                i = (int)tag1.attribute("edge","-1").toFloat();
                distribOnEdge = tag1.attribute("func","1.");
                grid->setDistribOnEdge(i,distribOnEdge);
                tag1 = tag1.nextSiblingElement("distribOnEdge");
              }
              tag1 = tag.firstChildElement("neighbour");
              while (!tag1.isNull()){
                i = (int)tag1.attribute("myEdge","0").toFloat();
                neighbourEdge = (int)tag1.attribute("neighbourEdge","0").toFloat();
                refName = resolveName(tag1.attribute("reference",""));
                if (elName->contains(refName)){
                  ref1 = elName->value(refName);
                  grid->setNeighbour(i, ref1, neighbourEdge);
                }
                tag1 = tag1.nextSiblingElement("neighbour");
              }

              tagIsHandled = true;
//            } else if (type == "Structured2DSubGrid"){
//              tStructuredSub2DGrid *grid;
//              grid = model->currentLayer()->add2DStructuredSubGrid();
//              e = grid;
//              refs = tag.firstChildElement("parentGrid").attribute("reference","").split(","); // Elemente in der Liste reference werden mit "," getrennt
//              for (i=0; i<refs.count() && i<1; i++){
//                if (elName->contains(resolveName(refs.at(i)))){
//                  grid->setParentGrid(elName->value(refs.at(i)));
//                }
//              }
//              tag1 = tag.firstChildElement("ni");
//              if (!tag1.isNull()){
//                grid->setNi((int)tag1.attribute("int","-1").toFloat());
//              }
//              tag1 = tag.firstChildElement("nj");
//              if (!tag1.isNull()){
//                grid->setNj((int)tag1.attribute("int","-1").toFloat());
//              }
//              tag1 = tag.firstChildElement("iOffset");
//              if (!tag1.isNull()){
//                grid->setOffsetI((int)tag1.attribute("int","-1").toFloat());
//              }
//              tag1 = tag.firstChildElement("jOffset");
//              if (!tag1.isNull()){
//                grid->setOffsetJ((int)tag1.attribute("int","-1").toFloat());
//              }
//              tagIsHandled = true;
            } else if (type == "export"){
              tGroup *exportGroup;
              QString expType, expFile;
              QFile file;

              expType = tag.attribute("type","noType");
              expFile = tag.attribute("file","noFile");

              if (expType != "noType" && expFile!="noFile"){
                QFileInfo fi(expFile);
                if (!fi.isAbsolute()){
                  fi.setFile(currentFileName);
                  expFile = fi.absolutePath()+"/"+expFile;
                }

                if (expType == "MSurfPatches"){
                  tPatExport toPat;
                  exportGroup = new tGroup(this);
                  if (refs.count() > 0){
                    for (i=0;i<refs.count();i++){
                      exportGroup->append(elName->value(refs.at(i)));
                    }
                  } else {
                    exportGroup->append(model);
                  }
                  toPat.exportToFile(expFile,exportGroup);
                  exportGroup->clear();
                  exportGroup->releaseOwner(this);
                } else if (expType == "ISThydro"){
                  tPclExport toPcl;
                  toPcl.exportToFile(expFile,model);
#ifdef BUILD_WITH_DXFLIB
                 } else if (expType.toLower() == "dxf") {
                  tBasicPlane* plane = NULL;
                  plane = dynamic_cast<tBasicPlane*>(model->elementByName(tag.attribute("plane",iBasicPlane::theType())));
                  tDxfExport2 dxf(expFile, model, plane);
#endif
                }
              }
            } else {
              e = model->currentLayer()->addElement(type);
              if (e){
                QDomElement propEl;
                int propIndex;
                iElement *intrface;
                QString propName, propType;
                intrface = e->intrface();

                propEl = tag.firstChildElement();
                while (!propEl.isNull()){
                  // Die Eigenschaften abarbeiten
                  propName = propEl.tagName();
                  propIndex = intrface->getPropertyIndex(propName);
                  if (propIndex>=0){
                    propType = intrface->getPropertyType(propIndex);
                    if (propType == "Int"){
                      int value = (int)propEl.attribute(propType,"0").toFloat();
                      intrface->setPropertyValue(propIndex,propType,&value);
                    } else if (propType == "Real") {
                      tReal value = propEl.attribute(propType,"0").toDouble();
                      intrface->setPropertyValue(propIndex,propType,&value);
                    } else if (propType == "Bool") {
                      bool value = !(propEl.attribute(propType,"false")=="false" || propEl.attribute(propType,"0")=="0");
                      intrface->setPropertyValue(propIndex,propType,&value);
                    } else if (propType == "String") {
                      QString value = propEl.attribute(propType,"");
                      intrface->setPropertyValue(propIndex,propType,&value);
                    } else if (propType == "RGB") {
                      tRGB value = colorize(propEl.attribute(propType,"30,180,10"));
                      intrface->setPropertyValue(propIndex,propType,&value);
                    } else if (propType.endsWith("List")){
                      QStringList value;
                      int i;
                      if (propType.startsWith("Int")){
                        tList<int> list;
                        value = propEl.attribute(propType).split(',',QString::KeepEmptyParts);
                        for (i=0;i<value.count();i++){                        list.append((int)value.at(i).toFloat());
                        }
                        intrface->setPropertyValue(propIndex,propType,&list);
                      } else if (propType.startsWith("Real")){
                        //!!!!
                      } else if (propType.startsWith("Bool")){
                        //!!!!
                      } else if (propType.startsWith("String")){
                        //!!!!
                      } else {
                        value = propEl.attribute(propType,"").split(',',QString::KeepEmptyParts);
                        tList<tElement*> list;
                        for (i=0;i<value.count();i++){
                          if (elName->contains(value.at(i))){
                            // Verweis auf ein Element aus dieser Datei.
                            list.append(elName->value(value.at(i)));
                          } else if (value.at(i)==name){
                            // Verweis auf sich selbst????
                            list.append(e);
                          } else {
                            // Verweis auf ein Element im aktuellen Layer
                            tElement *el;
                            el = model->currentLayer()->elementByName(value.at(i));
                            if (el){
                              list.append(el);
                            } else {
                              list.append(NULL);
                            }
                          }
                        }
                        intrface->setPropertyValue(propIndex,propType,&list);
                      }
                    } else {
                      // alle anderen tElement-Typen
                      QString refName;
                      refName = propEl.attribute(propType,"");
                      if (elName->contains(refName)){
                        tElement *el;
                        el = elName->value(refName);
                        intrface->setPropertyValue(propIndex,propType,el);
                      } else if (refName==name){
                        intrface->setPropertyValue(propIndex,propType,e);
                      } else {
                        intrface->setPropertyValue(propIndex,propType,model->elementByName(refName, propType));
                      }
                    }
                  }
                  propEl = propEl.nextSiblingElement();
                }
                tagIsHandled = true;
              } else {
                fErrorMessages << "The Element type \"" + type + "\" is not implemented in the import routine.";
                error = true;
              }
						}
						if (tagIsHandled){
							elName->insert(name,e);
//							printf(("created: "+ type + ", " +name+"\n").toLatin1().data());
							I = e->intrface();
							I->setPropertyString("name",name.section(":",0,0));
							I->setPropertyValue("visibility",jrBool,&isVisible);
							I->setPropertyValue("color",jrRGB,&rgb);

							surf = dynamic_cast<tSurface*>(e);
							if (surf){
								tag1 = tag.firstChildElement("properties");
								if (!tag1.isNull()){
									surf->setUDiv((int)funcs.calc(tag1.attribute("uDiv","8")));
									surf->setVDiv((int)funcs.calc(tag1.attribute("vDiv","8")));
									surf->setURes((int)funcs.calc(tag1.attribute("uRes","4")));
									surf->setVRes((int)funcs.calc(tag1.attribute("vRes","4")));
								}
                tag1 = tag.firstChildElement("orientation");
                if (!tag1.isNull()){
                  if (tag1.attribute("bool","false") == "true"){
                    surf->setOrientation(true);
                  } else {
                    surf->setOrientation(false);
                  }
                }
							}
							curve = dynamic_cast<tCurve*>(e);
							if (curve){
								tag1 = tag.firstChildElement("properties");
								if (!tag1.isNull()){
//									tCurve *curve;
//									curve = (iCurve*)e;
									curve->setTResolution((int)funcs.calc(tag1.attribute("tRes","8")));
								}
							}
						}
						tagIsHandled = true;
					}
				}
				if (tagIsHandled){
					tag1 = tag.nextSiblingElement();
					newItems = true;
				  node = m.removeChild(tag);
				  node.clear();
				  tag = tag1;
				} else {
					tag = tag.nextSiblingElement();
				}
			} while (!tag.isNull());
		  tag = m.firstChildElement();
		} while ( !tag.isNull() && newItems );
		return !error;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

void tModelIO::executeFunctionSurfaceXml(tFunctionSurface *s, QDomElement el, QHash<QString,QDomElement> *macro){
  QString macroName;
  QDomElement tag, macroEl;

  tag = el.firstChildElement();
  while (!tag.isNull()){
    if (tag.tagName() == "function" || tag.tagName() == "math"){
      if (tag.hasAttribute("string")){
        s->addFunction(tag.attribute("string",""));
      } else if (tag.hasAttribute("func")){
        s->addFunction(tag.attribute("func",""));
      }
    } else if (tag.tagName() == "call"){
      macroName = resolveName(tag.attribute("macro",""));
      macroEl = macro->value(macroName);
      if (!macroEl.isNull()){
        executeFunctionSurfaceXml(s, macroEl, macro);
      }
    }
    tag = tag.nextSiblingElement();
  }
}
//-----------------------------------------------------------------------------

QString tModelIO::resolveName(QString str){
	QStringList L;
	QString result;
	int i;
	bool isValid;
	tReal res;

	L = str.split("|", QString::SkipEmptyParts);
	for (i=0;i<L.count();i++){
		if (funcs.isFunc(L.at(i))){
			res = funcs.calc(L.at(i),&isValid,0.);
			if (isValid){
				result += QString::number(res);
			} else {
				result += L.at(i);
			}
		} else {
			result += L.at(i);
		}
	}
	return result;
}*/
//-----------------------------------------------------------------------------
