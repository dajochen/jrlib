#include <QStringList>
#include <QMessageBox>
#include <QFile>
#include "model/tModel.h"

#include "classes/utils.h"

/**
 * @brief tModel::tModel
 * A model is a container for tLayer-Elements. Under its structure elements structure tElements
 * can be created and passed to other objects which interact with tModel.
 * - It keeps a tGroup entity selection, which stores currently selected Elements. Such a selection
 *   can be used for several purposes, e.g. for a common modification etc.
 *
 * - It further keeps a reference to an other group, which is called selectable. If selectable is
 *   not NULL only elements can be added to selection, which are part of selectable. The group
 *   is set by calling setSelectables.
 *
 * - Using setCurrentLayer an active layer can be set.
 */
tModel::tModel(void *theOwner)
 : tLayer(theOwner, new tVariableNameSpace(this), iLayer::theType())
{
  variables = vars();//new tVariableNameSpace(this);
  variables->intrface()->setName("globalVariables");

  fCurrentLayer = this;

  //fSelection = new tGroup(this);
  //fSelection->addDependent(this);

  //fSelectable = NULL;
}
//-----------------------------------------------------------------------------

tModel::~tModel()
{
//	unsigned int i,j,nj;
  fCurrentLayer = NULL;
  clear();
//	fLayer->clear();
//	for (i=0;i<(unsigned int)fLayer.count();i++){
//  	fCurrentLayer = fLayer.element(i);
//  	nj = fCurrentLayer->nElements();
////  	for (j=0;j<nj;j++){
////      fCurrentLayer->element(j)->removeDependent(this);
////  		fCurrentLayer->element(j)->releaseOwner(this);
////  	}
// 	  fCurrentLayer->releaseOwner(this);
//	}
//	fLayer.clear();
//
//  setSelectables(NULL);

//  fSelection.clear();
  //fSelection->removeDependent(this);
  //fSelection->releaseOwner(this);

//  fSelectable->clear();
//  fSelectable->removeDependent(this);
//  fSelectable->releaseOwner(this);

  variables->releaseOwner(this);
}
//-----------------------------------------------------------------------------

iElement* tModel::intrface(void){
  setElementLocked
  if (iface == NULL){
    iface = new iModel(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tModel::refresh(void)
{
}
//-----------------------------------------------------------------------------

/*
void tModel::importMultiSurf (QString &filename)
{
	setElementLocked
  QFile *f;
  char *buffer;
  int i, j, lastcount;
  tVector v;
  tDot *d;
  QString Version, Header, line, Name;
  QStringList lines;
  tRGB color;

  f = new QFile(filename);
  if (f->open(QIODevice::ReadOnly)) {
    buffer = (char*)malloc(f->size());
    f->read(buffer,f->size());
    f->close();
    QString content = QString::fromLocal8Bit(buffer);
    free (buffer);
    i = content.indexOf("BeginModel");
    if (i < 0) {
      QMessageBox::critical(NULL,"Import MultiSurf","\"BeginModel\" nicht gefunden!");
      return;
    }
    Header = content.left(i);
    content.remove(0,i);
    lines = Header.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    for (i=0;i<lines.size();i++) {
      if (lines.at(i).startsWith("MultiSurf")) {
        int version = (int)(lines.at(i).section(' ',1,1).toDouble()*100.0);
        if (version > 134) {
          QMessageBox::warning (NULL,"Import MultiSurf","Dateiversionen ["+QString::number(version)+"] werden nur bis 1.34 unterstützt.");
        }
      }
    }
    Header.clear();
    content.replace(QRegExp("[\r\n]")," ");
    lines = content.split(";",QString::SkipEmptyParts);
    content.clear();
    i = 0;
    lastcount = lines.count()+1;
    while (lines.count()>0 && lastcount!=lines.count()) {
      lastcount = lines.count();
      i = 0;
      while (i<lines.count()){
        line = lines.at(i).trimmed();
        if (line.startsWith("AbsPoint")) {
          Name = line.section(' ',1,1,QString::SectionSkipEmpty);
          color = tRGB::MSColor(line.section(' ',2,2,QString::SectionSkipEmpty).toInt());
          j = line.indexOf('/');
          line.remove(0,j+1);
          v.x = line.section(' ',0,0,QString::SectionSkipEmpty).toDouble();
          v.y = line.section(' ',1,1,QString::SectionSkipEmpty).toDouble();
          v.z = line.section(' ',2,2,QString::SectionSkipEmpty).toDouble();
          tPoint* p= fCurrentLayer->addPoint(v);
          p->intrface()->setName(Name);
          p->intrface()->setColor(color);
          lines.removeAt(i);
        } else if (line.startsWith("RelPoint")) {
          Name = line.section(' ',1,1,QString::SectionSkipEmpty);
          color = tRGB::MSColor(line.section(' ',2,2,QString::SectionSkipEmpty).toInt());
          j = line.indexOf('/');
          line.remove(0,j+1);
          QString Ref = line.section(' ',0,0,QString::SectionSkipEmpty);
          v.x = line.section(' ',1,1,QString::SectionSkipEmpty).toDouble();
          v.y = line.section(' ',2,2,QString::SectionSkipEmpty).toDouble();
          v.z = line.section(' ',3,3,QString::SectionSkipEmpty).toDouble();
          d = dynamic_cast<tDot*>(elementByName(Ref));
          if (d) {
            tRelPoint *p = fCurrentLayer->addRelPoint(d,v);
            p->intrface()->setName(Name);
            p->intrface()->setColor(color);
            lines.removeAt(i);
          } else
            i++; // diesen RelPoint beim nächsten Durchlauf behandeln, weil Referenzpunkt bisher unbekannt ist.
        } else if (line.startsWith("XPlane")) {
          Name = line.section(' ',1,1,QString::SectionSkipEmpty);
          color = tRGB::MSColor(line.section(' ',2,2,QString::SectionSkipEmpty).toInt());
          j = line.indexOf('/');
          line.remove(0,j+1);
          tXPlane *p = fCurrentLayer->addXPlane(line.section(' ',0,0,QString::SectionSkipEmpty).toDouble());
          p->intrface()->setName(Name);
          p->intrface()->setColor(color);
          lines.removeAt(i);
        } else if (line.startsWith("YPlane")) {
          Name = line.section(' ',1,1,QString::SectionSkipEmpty);
          color = tRGB::MSColor(line.section(' ',2,2,QString::SectionSkipEmpty).toInt());
          j = line.indexOf('/');
          line.remove(0,j+1);
          tYPlane *p = fCurrentLayer->addYPlane(line.section(' ',0,0,QString::SectionSkipEmpty).toDouble());
          p->intrface()->setName(Name);
          p->intrface()->setColor(color);
          lines.removeAt(i);
        } else if (line.startsWith("ZPlane")) {
          Name = line.section(' ',1,1,QString::SectionSkipEmpty);
          color = tRGB::MSColor(line.section(' ',2,2,QString::SectionSkipEmpty).toInt());
          j = line.indexOf('/');
          line.remove(0,j+1);
          tZPlane *p = fCurrentLayer->addZPlane(line.section(' ',0,0,QString::SectionSkipEmpty).toDouble());
          p->intrface()->setName(Name);
          p->intrface()->setColor(color);
          lines.removeAt(i);
        } else {
          lines.removeAt(i); // unbekannten Typ löschen
        }
      }
    }
    invalidate(this);
  }
}*/
//-----------------------------------------------------------------------------

//void tModel::releaseElement(tElement* el)
//{
//	setElementLocked
//	int i;
//	for (i=0;i<fLayer.count();i++){
//		if (el->isSupportOf(fLayer.at(i))){
//			fLayer.at(i)->removeAllElements(el);
//			el->releaseOwner(this);
//			i=fLayer.count();
//		}
//	}
//  invalidate(this);
//}
////-----------------------------------------------------------------------------

//tElement* tModel::element(unsigned int index)
//{
//	setElementLocked
//  int g = 0;
//  unsigned int i = 0;
//  update();
//  while ((g < fLayer.count()) && (index > i+(fLayer.at(g)->nElements()))) {
//    i += fLayer.at(g)->nElements();
//    g++;
//  }
//  if (g < fLayer.count())
//    return fLayer.at(g)->element(index-i);
//  else
//    return NULL;
//}
////-----------------------------------------------------------------------------
//
//unsigned int tModel::nElements()
//{
//	setElementLocked
//  unsigned int n = 0;
//  update();
//  for (int g=0;g<fLayer.count();g++)
//    n += fLayer.at(g)->nElements();
//  return n;
//}
////-----------------------------------------------------------------------------
//
//bool tModel::contains(tElement *el)
//{
//	setElementLocked
//  update();
//  for (int g=0;g<fLayer.count();g++){
//    if (fLayer.at(g)->contains(el)){
//      return true;
//    }
//  }
//  return false;
//}
//
////-----------------------------------------------------------------------------
//
//tLayer* tModel::layer(int index)
//{
//	setElementLocked
//  update();
//  if (index < fLayer.count())
//	  return fLayer.at(index);
//  else
//    return NULL;
//}
////-----------------------------------------------------------------------------
//
//tLayer* tModel::addLayer(QString name)
//{
//	setElementLocked
//  tLayer *l;
//	l = dynamic_cast<tLayer*>(fLayer->addElement(iElement::theType()));
//	fCurrentLayer = l;
////  l = new(tLayer)(this, variables);
////  l->intrface()->setName(name);
////  l->addDependent(this);
////  fLayer.append(l);
////  fCurrentLayer = l;
////  invalidate(this);
//  return l;
//}
//-----------------------------------------------------------------------------

///**
// * Adds any layer to the model. This method is depreciated, as the variableNameSpace in not necessarily the same as the
// * common variableNameSpace of the model, also . Be careful using this method.
// */
//tLayer* tModel::addLayer (tElement *layer)
//{
//  setElementLocked
//  tLayer *l = NULL;//dynamic_cast<tLayer*>(layer);
//  if (l){
////    l->addDependent(this);
//    l = fLayer.append(layer);
//    fCurrentLayer = l;
//    invalidate(this);
//  }
//  return l;
//}

//-----------------------------------------------------------------------------
//tLayer* tModel::getLayer (QString name)
//{
//  setElementLocked
//  tLayer *l;
//  for (int i=0; i<fLayer.count(); i++){
//    if (fLayer.at(i)->intrface()->name() == name){
//      return fLayer.at(i);
//    }
//  }
//  return addLayer(name);
//}

//-----------------------------------------------------------------------------
// Wird durch allg. remove Element ersetzt.
//void tModel::removeLayer(tLayer *l)
//{
//  setElementLocked
//  int id = fLayer.firstIndexOf(l);
//  removeLayer(id);
//}
//-----------------------------------------------------------------------------

//void tModel::removeLayer(int index)
//{
//	setElementLocked
//	if (index >=0 && index < fLayer.count()){
//	  tLayer* toBeRemoved = fLayer.at(index);
//	  if (fCurrentLayer == toBeRemoved ){
//	    fCurrentLayer = NULL;
//	  }
//		toBeRemoved->removeDependent(this);
//		toBeRemoved->releaseOwner(this);
//		fLayer.removeAt(index);
//	}
//  invalidate(this);
//}
//-----------------------------------------------------------------------------
tLayer* tModel::currentLayer(void)
{
  setElementLocked
  update();
  return fCurrentLayer;
};
//-----------------------------------------------------------------------------

void tModel::setCurrentLayer(tLayer *layer)
{
	setElementLocked
  if (layer){
    fCurrentLayer = layer;
  }
  invalidate(this);
}
/*
void tModel::setSelectables(tGroup *group)
{
  setElementLocked
      if (group != fSelectable){
    if (fSelectable){
      fSelectable->removeDependent(this);
    }
    fSelectable = group;
    if (fSelectable){
      fSelectable->addDependent(this);
    }
    invalidate(this);
  }
}

void tModel::setSelection(tElement *el)
{
  setElementLocked
  tList<tElement*> newList;
  newList.append(el);
  setSelection(newList);
}

void tModel::setSelection(const tList<tElement *> eList)
{
  setElementLocked
  bool modified = false;
  // remove elements not in eList:
  tList<tElement *> fSelectionList = fSelection;
  for (int i=0; i<fSelectionList.count(); i++){
    tElement* el = fSelectionList.at(i);
    if (!eList.contains(el)){
      fSelection.removeAll(el);
      modified = true;
    }
  }

  //add missing elements:
  for (int i=0;i<eList.count(); i++){
    tElement *el = eList.at(i);
    if (!fSelection.contains(el)){
      fSelection.append(el);
      modified = true;
    }
  }
  if (modified){
    invalidate(this);
  }
}*/
//-----------------------------------------------------------------------------

tVector tModel::xMin(void)
{
	setElementLocked
	tVector xmin;
  xmin = tLayer::xMin();
	return xmin;
}
//-----------------------------------------------------------------------------

tVector tModel::xMax(void)
{
	setElementLocked
	tVector xmax;
  xmax = tLayer::xMax();
	return xmax;
}


//-----------------------------------------------------------------------------
void tModel::deleteElements(tList<tElement*> toBeDeleted)
{
  setElementLocked
  for (int i=0; i<toBeDeleted.count(); i++){
    tElement *el = toBeDeleted.at(i);
    removeElement(el, true);
  }
}
/*
//-----------------------------------------------------------------------------

void tModel::doublicateFirstSelectedElement(void)
{
  setElementLocked
  if (fSelection.count() && fCurrentLayer){
    tGroup *referenceBase = new tGroup(NULL);
    tElement *copy = fSelection.at(0);
    for (int i=1;i<fSelection.count(); i++){
      referenceBase->append(fSelection.at(i));
    }

    tElement* paste = fCurrentLayer->addElement(copy->intrface()->type());

    for (int i=0;i<(int)copy->intrface()->nProperties();i++){
      QString propType = copy->intrface()->getPropertyType(i) ,
              propName = copy->intrface()->getPropertyType(i);

      bool isList;
      if (propType.endsWith("List")){
        isList = true;
        propType.remove(propType.length()-1-4,4);
      } else {
        isList = false;
      }

      tList<tElement*> references = referenceBase->elements(propType);
      if (!references.isEmpty()){
        if (isList){
          paste->intrface()->setPropertyValue(i,propType,&references);
          for (int i=0;i<references.count();i++){
            paste->intrface()->setPropertyValue(i,propType,&references);
            referenceBase->removeAllElements(references.at(i));
          }
        } else {
          tElement *el =  references.at(0);
          paste->intrface()->setPropertyValue(i, propType, el);
          referenceBase->removeElement(0);
        }
      } else {


        int iVal;
        tReal rVal;
        bool bVal;
        tVector vVal;
        tRGB rgbVal;
        QString strVal;
        tElement* elVal;

        tList<int> iListVal;
        tList<tReal> rListVal;
        tList<bool> bListVal;
        tList<tVector> vListVal;
        tList<tRGB> rgbListVal;
        tList<QString> strListVal;
        tList<tElement*> elListVal;

        void *value;

        if (propType=="Int"){
          value = &iVal;
        } else if (propType=="Real"){
          value = &rVal;
        } else if (propType=="Bool"){
          value = &bVal;
        } else if (propType=="Vector"){
          value = &vVal;
        } else if (propType=="RGB"){
          value = &rgbVal;
        } else if (propType=="String"){
          value = &strVal;
        } else if (propType.endsWith("List")){
          if (propType=="IntList") {
            value = &iListVal;
          } else if (propType=="RealList") {
            value = &rListVal;
          } else if (propType=="BoolList") {
            value = &bListVal;
          } else if (propType=="VectorList") {
            value = &vListVal;
          } else if (propType=="RGBList") {
            value = &rgbListVal;
          } else if (propType=="StringList") {
            value = &strListVal;
          } else {
            value = &elListVal;
          }
        } else {
          value = &elVal;
        }

        copy->intrface()->getPropertyValue(i, propType, value);
        paste->intrface()->setPropertyValue(i, propType, value);
      }

    }
    referenceBase->clear();
    referenceBase->releaseOwner(NULL);
  }
}
*/
//-----------------------------------------------------------------------------

