#include "tModifierTools.h"


tModifierTools::tModifierTools()
{
}


//-----------------------------------------------------------------------------

void tModifierTools::addSupportingPoints(tElement* el, tList<tPoint*>&pList, tList<tRelPoint*>&rpList)
{
  setElementLocked
  tPoint *p;
  tRelPoint *rp;

  p = dynamic_cast<tPoint*>(el);
  rp = dynamic_cast<tRelPoint*>(el);

  if (p && !pList.contains(p)){
    pList.append(p);
  } if (rp && !rpList.contains(rp)){
    rpList.append(rp);
  } else {
    iElement *in = el->intrface();
    int nProps = (int)in->nProperties();
    for (int j=0; j<nProps; j++){
      QString propType = in->getPropertyType(j);
      if (propType == iDot::theType() ){
        tElement *property=NULL;
        in->getPropertyValue(j,propType,&property);
        addSupportingPoints(property, pList, rpList);
      } else if (propType == iDot::theType()+"List") {
        tList<tElement*> property;
        in->getPropertyValue(j,propType,&property);
        for (int k=0; k<property.count(); k++){
          addSupportingPoints(property.at(k), pList, rpList);
        }
      }
    }
  }
}
//-----------------------------------------------------------------------------


/**
 * Moves all tPoints, found in attributes of the current selection with the increment dx.
 */

void tModifierTools::shiftElements(const tVector& dx, tList<tElement*> elements)
{
  tList<tPoint*> pList;
  tList<tRelPoint*> rpList;
  tPoint *p;
  tRelPoint *rp;

  for (int i=0; i<elements.count(); i++){
    tElement *el = elements.at(i);
    addSupportingPoints(el, pList, rpList);
  }


  for (int i=0; i<pList.count();i++){
    p = pList.at(i);
    p->setVector(p->vector()+dx);
  }
  for (int i=0; i<rpList.count();i++){
    rp = rpList.at(i);
    tPoint *reference = dynamic_cast<tPoint*>(rp->reference());
    if (!pList.contains(reference)) {
        rp->setOffset(rp->offset()+dx);
    }
  }
}
//-----------------------------------------------------------------------------

void tModifierTools::rotateElements(const tVector& origin, const tVector& domega, tList<tElement*> elements)
{
  tList<tPoint*> pList;
  tList<tRelPoint*> rpList;
  tPoint *p;
  tRelPoint *rp;

  for (int i=0; i<elements.count(); i++){
    tElement *el = elements.at(i);
    addSupportingPoints(el, pList, rpList);
  }

  QHash<tDot*, tVector> oldLocation;
  for (int i=0; i<rpList.count();i++){
      oldLocation [rpList.at(i)] = rpList.at(i)->vector();
  }

  for (int i=0; i<pList.count();i++){
    p = pList.at(i);
    p->setVector(p->vector().rotate(origin, domega, domega.length()));
  }

  for (int i=0; i<rpList.count();i++){
    rp = rpList.at(i);
    tVector start = oldLocation[rp];
    tVector end = start.rotate(origin, domega, domega.length());
    rp->setOffset(end-rp->reference()->vector());
  }
}

//-----------------------------------------------------------------------------
/**
 * Creates mirrored objects of the selected elements.
 */
void tModifierTools::flipElements(const tVector &origin, const tVector &flipAxis, tList<tElement *> elements)
{
  tList<tPoint*> pList;
  tList<tRelPoint*> rpList;
  tPoint *p;
  tRelPoint *rp;

  for (int i=0; i<elements.count(); i++){
    tElement *el = elements.at(i);
    addSupportingPoints(el, pList, rpList);
  }

  QHash<tDot*, tVector> oldLocation;
  for (int i=0; i<rpList.count();i++){
      oldLocation [rpList.at(i)] = rpList.at(i)->vector();
  }

  for (int i=0; i<pList.count();i++){
    p = pList.at(i);
    p->setVector(p->vector() - flipAxis*((p->vector()-origin)*flipAxis)*2. );
  }
  for (int i=0; i<rpList.count();i++){
    rp = rpList.at(i);
    tVector start = oldLocation[rp];
    tVector end = start - flipAxis*((start-origin)*flipAxis)*2.;
    rp->setOffset(end-rp->reference()->vector());
  }
}

void tModifierTools::removeDoublicateElements(tLayer *l)
{
    tList<tElement*> allElements = l->elements("", true);
    QStringList ignoreProps = QString("type;name;color;visibility").split(';');
    QStringList ignorePropTypes = QString("RGB").split(';');

    tList<tElement*> toBeRemoved;

    for (int i=0; i<allElements.count(); i++) {
        tElement* el = allElements.at(i);
        tList<tElement*> matchingElements;

        if (!toBeRemoved.contains(el) && dynamic_cast<tLayer*>(el) == NULL) {
            //Layers will not be processed, and elements detected before will be skipped.
            for (int j=i+1; j<allElements.count(); j++) {
                tElement* comp = allElements.at(j);
                if (el->intrface()->type() == comp->intrface()->type()) {
                    //compare interface values:
                    iElement *i = el->intrface(),
                            *iComp = comp->intrface();
                    bool matches = true;
                    for (int k=0; matches==true && k<i->nProperties(); k++) {
                        if (i->isReadOnly(k) == false) {
                            QString property = i->getPropertyName(k);
                            QString propType = i->getPropertyType(k);
                            if (!ignoreProps.contains(property) && !ignorePropTypes.contains(propType)) { // ignoring other properties
                                if (propType == "Int") {
                                    int value = 0, valueComp = -1;
                                    i->getPropertyValue(k, propType, &value);
                                    iComp->getPropertyValue(k,propType, &valueComp);
                                    if (value != valueComp) {
                                        matches = false;
                                    }
                                } else if (propType == "Real") {
                                    double value = 0, valueComp = -1;
                                    i->getPropertyValue(k, propType, &value);
                                    iComp->getPropertyValue(k,propType, &valueComp);
                                    if (value != valueComp) {
                                        matches = false;
                                    }
                                } else if (propType == "Bool") {
                                    bool value = true, valueComp = false;
                                    i->getPropertyValue(k, propType, &value);
                                    iComp->getPropertyValue(k,propType, &valueComp);
                                    if (value != valueComp) {
                                        matches = false;
                                    }
                                } else if (propType == "String") {
                                    QString value = "0", valueComp = "1";
                                    i->getPropertyValue(k, propType, &value);
                                    iComp->getPropertyValue(k,propType, &valueComp);
                                    if (value != valueComp) {
                                        matches = false;
                                    }
                                } else if (propType == "Vector") {
                                    tVector value(0,0,0), valueComp(1,1,1);
                                    i->getPropertyValue(k, propType, &value);
                                    iComp->getPropertyValue(k,propType, &valueComp);
                                    if (value != valueComp) {
                                        matches = false;
                                    }
                                    // ignoring colors
                                } else if (propType.endsWith("List")) {
                                    if (propType == "IntList") {
                                        tList<int> value, valueComp;
                                        bool foundProp;
                                        i->getPropertyValue(k, propType, &value);
                                        foundProp = iComp->getPropertyValue(k,propType, &valueComp);
                                        if (!foundProp || !value.isEqualTo(valueComp)) {
                                            matches = false;
                                        }
                                    } else if (propType == "RealList") {
                                        tList<double> value, valueComp;
                                        bool foundProp;
                                        i->getPropertyValue(k, propType, &value);
                                        foundProp = iComp->getPropertyValue(k,propType, &valueComp);
                                        if (!foundProp || !value.isEqualTo(valueComp)) {
                                            matches = false;
                                        }
                                    } else  {//if (propType == "ElementList") {
                                        tList<tElement*> value, valueComp;
                                        bool foundProp;
                                        i->getPropertyValue(k, propType, &value);
                                        foundProp = iComp->getPropertyValue(k,propType, &valueComp);
                                        if (!foundProp || !value.isEqualTo(valueComp)) {
                                            matches = false;
                                        }
                                    }
                                } else {
                                    //It should be of type tElement
                                    bool foundProp;
                                    tElement *value = el, *valueComp = NULL;
                                    i->getPropertyValue(k, propType, &value);
                                    foundProp = iComp->getPropertyValue(k,propType, &valueComp);
                                    if (!foundProp || value != valueComp) {
                                        matches = false;
                                    }
                                }
                            }
                        }
                    }
                    if (matches == true) {
                        matchingElements.append(comp);
                    }
                }
            }

            QStringList nonElementTypes = QString("Int;Real;Bool;String;RGB;Vector;IntList;RealList").split(';');
            for (int i=0; i<matchingElements.count(); i++) {
                tElement* toBeReplaced = matchingElements.at(i);
                tList<tElement*> dependents = toBeReplaced->dependents();
                for (int j=0; j<dependents.count(); j++) {
                    tElement *dep = dependents.at(j);
                    if (dynamic_cast<tLayer*>(dep) == NULL) { // The element to be replaced shall remain in its layer for the moment.
                        for (int k=0; k<dep->intrface()->nProperties(); k++) {
                            if (dep->intrface()->isReadOnly(k) == false) {
                                QString propName = dep->intrface()->getPropertyType(k);
                                QString propType = dep->intrface()->getPropertyType(k);
                                if (!nonElementTypes.contains(propType)) {
                                    //it is of type Element or ElementList
                                    if (propType.endsWith("List")){
                                        QStringList nonElementLists = QString("IntList;RealList;BoolList;StringList").split(';');
                                        if (!nonElementLists.contains(propType))  {
                                            tList<tElement*> referencedElements;
                                            dep->intrface()->getPropertyValue(k, propType, &referencedElements);

                                            for (int j=0;j<referencedElements.count(); j++) {
                                                if (referencedElements.at(j) == toBeReplaced) {
                                                    referencedElements.setAt(j,el);
                                                }
                                            }
                                            dep->intrface()->setPropertyValue(k, propType, &referencedElements);
                                        }
                                    } else {//it seams to be an Element
                                        tElement* referencedElement = NULL;
                                        dep->intrface()->getPropertyValue(k, "Element", &referencedElement);
                                        if (referencedElement == toBeReplaced) {
                                            referencedElement = el;
                                        }
                                        dep->intrface()->setPropertyValue(k, "Element", referencedElement);
                                    }
                                }
                            }

                        }
                    }
                }
                dependents = toBeReplaced->dependents();
                if (dependents.count()==1) {
                    toBeRemoved.append(toBeReplaced);
                }

            }
        }
    }
    for (int i=0; i<toBeRemoved.count(); i++) {
        tElement *el = toBeRemoved.at(i);
        tLayer *l = dynamic_cast<tLayer*>(el->dependents().at(0));
        l->removeElement(el);

    }
    //return toBeRemoved;
}
