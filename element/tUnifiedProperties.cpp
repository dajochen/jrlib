#include "tUnifiedProperties.h"
#include "tGroup.h"

tUnifiedProperties::tUnifiedProperties(void *theOwner)
  : tElement(theOwner)
{

  fUnifiedProperty ="";
  fUnifiedType = "None";
  isUpdating = false;

}

tUnifiedProperties::~tUnifiedProperties()
{
}

iElement *tUnifiedProperties::intrface()
{
  update();
  if (iface == NULL){
    iface = new iUnifiedProperties(this);
  }
  return iface;
}

void tUnifiedProperties::refresh()
{
}

tList<tElement*> tUnifiedProperties::elementList(void)
{
  return fElementList;
}

void tUnifiedProperties::setElementList(tList<tElement*> list) {
  setElementLocked

  for(int i=0; i<fElementList.count();i++){
    fElementList.at(i)->removeDependent(this);
  }
  fElementList.clear();
  for (int i=0; i<list.count();i++){
    addElement(list.at(i));
  }
}

void tUnifiedProperties::addElement(tElement *el)
{
  if (el->addDependent(this)){
    fElementList.append(el);
    invalidate(this);
  }
}

void tUnifiedProperties::invalidate(tElement *sender)
{
  if (fElementList.contains(sender)){
    checkForModifiedProperties();
  }
  tElement::invalidate(sender);
}

void tUnifiedProperties::repaintElement(tElement *sender)
{
  if (fElementList.contains(sender)){
      checkForModifiedProperties();
  }
  tElement::repaintElement(sender);
}


/**
  checkForModifiedProperties checks if a property of an element was modified. If the modified element has now a different
  property value for the unfifiedProperty its pointer from the elementList is removed.  .

*/
void tUnifiedProperties::checkForModifiedProperties()
{
  setElementLocked

  for (int i=0; i<fElementList.count() && isUpdating==false; i++){
    tElement* el = fElementList.at(i);
    el->lockElement();

    bool isEqual = true;
    if (fUnifiedType == "None"){
      isEqual = true;
    } else if(fUnifiedType == "Int") {
      int iVal, value2;
      unifiedValue(&iVal);
      el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
      isEqual = (iVal == value2);
    } else if (fUnifiedType == "Real") {
      tReal val, value2;
      unifiedValue(&val);
      el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
      isEqual = (val == value2);
    } else if (fUnifiedType == "Bool") {
        bool val, value2;
        unifiedValue(&val);
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (val == value2);
    } else if (fUnifiedType == "Vector") {
        tVector val, value2;
        unifiedValue(&val);
        el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
        isEqual = (val == value2);
    } else if (fUnifiedType == "RGB") {
        tRGB val, value2;
        unifiedValue(&val);
        el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
        isEqual = (val == value2);
    } else if (fUnifiedType == "String") {
        QString val, value2;
        unifiedValue(&val);
        el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
        isEqual = (val == value2);
    } else  {
      if (fUnifiedType.endsWith("List")) {
        QString listType = fUnifiedType.left(fUnifiedType.length()-4);
        if(listType == "Int") {
            tList<int> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else if (listType == "Real") {
            tList<tReal> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else if (listType == "Bool") {
            tList<bool> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else if (listType == "Vector") {
            tList<tVector> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else if (listType == "RGB") {
            tList<tRGB> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else if (listType == "String") {
            tList<QString> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        } else {
            tList<tElement*> val, value2;
            unifiedValue(&val);
            el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
            isEqual = (val == value2);
        }
      } else {
          tElement *val, *value2;
          unifiedValue(&val);
          el->intrface()->getPropertyValue(fUnifiedProperty, fUnifiedType, &value2);
          isEqual = (val == value2);
      }
    }

    if (!isEqual){
        el->removeDependent(this);
        fElementList.removeAt(i);    
        i--;
    }

    el->unlockElement();
  }
}


void tUnifiedProperties::applyUnifiedValue(tElement* el, void* newValue){
  el->lockElement();

  tGroup *g = dynamic_cast<tGroup*>(el);
  // the newValue will also be applied to the elements within a group.
  if (g){
    tList<tElement*> elements = g->elements();
    for (int i=0; i<elements.count(); i++){
      applyUnifiedValue(elements.at(i), newValue);
    }
  }


  // check if property has changed. Overwrite only if value will change.
  // Otherwise endless loops will occure as this depends on the changed objects.
  bool isEqual = false;

  if(fUnifiedType == "Int") {
    iVal = *(int*)(newValue);
    int value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (iVal == value2);
  } else if (fUnifiedType == "Real") {
    rVal = *(tReal*)(newValue);
    tReal value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (rVal == value2);
  } else if (fUnifiedType == "Bool") {
    bVal = *(bool*)(newValue);
    bool value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (bVal == value2);
  } else if (fUnifiedType == "Vector") {
    vVal = *(tVector*)(newValue);
    tVector value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (vVal == value2);
  } else if (fUnifiedType == "RGB") {
    rgbVal = *(tRGB*)(newValue);
    tRGB value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (rgbVal == value2);
  } else if (fUnifiedType == "String") {
    strVal = *(QString*)(newValue);
    QString value2;
    el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
    isEqual = (strVal == value2);
  } else  {
    if (fUnifiedType.endsWith("List")) {
      QString listType = fUnifiedType.left(fUnifiedType.length()-4);
      if(listType == "Int") {
        intList = *(tList<int>*)(newValue);
        tList<int> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (intList == value2);
      } else if (listType == "Real") {
        realList = *(tList<tReal>*)(newValue);
        tList<tReal> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (realList == value2);
      } else if (listType == "Bool") {
        boolList = *(tList<bool>*)(newValue);
        tList<bool> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (boolList == value2);
      } else if (listType == "Vector") {
        vectorList = *(tList<tVector>*)(newValue);
        tList<tVector> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (vectorList == value2);
      } else if (listType == "RGB") {
        rgbList = *(tList<tRGB>*)(newValue);
        tList<tRGB> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (rgbList == value2);
      } else if (listType == "String") {
        stringList = *(tList<QString>*)(newValue);
        tList<QString> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (stringList == value2);
      } else {
        elList = *(tList<tElement*>*)newValue;
        tList<tElement*> value2;
        el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, &value2);
        isEqual = (elList == value2);
      }
    } else {
      elVal  = (tElement*)newValue;
      tElement* value2=NULL;
      el->intrface()->getPropertyValue(fUnifiedProperty,fUnifiedType, value2);
      isEqual = (elVal == value2);
    }
  }
  // and finally set the new value:
  if (!isEqual){
    el->intrface()->setPropertyValue(fUnifiedProperty,fUnifiedType, newValue);
  }

  el->unlockElement();

}

void tUnifiedProperties::setUnifiedValue(void* newValue) {
  lockElement();
  isUpdating = true;

  for (int i=0; i<fElementList.count(); i++){

    tElement *el2 = fElementList.at(i);
    applyUnifiedValue(el2, newValue);
  }
  isUpdating = false;
  invalidate(this);
  unlockElement();

}
//-----------------------------------------------------------------------------
/**
 * @brief iUnifiedProperties::unifiedValue
 * @param writeTo
 * @return
 *
 * writes the unified value into the pointer "writeTo" and returns a pointer to the private value.
 */
void* tUnifiedProperties::unifiedValue(void *writeTo){
  setElementLocked
  void* value=NULL;
  if (fUnifiedType == "None"){
    value = NULL;
  } else if(fUnifiedType == "Int") {
    value = &iVal;
    if (writeTo) {*(int*)writeTo = iVal;}
  } else if (fUnifiedType == "Real") {
    value = &rVal;
    if (writeTo) {*(tReal*)writeTo = rVal;}
  } else if (fUnifiedType == "Bool") {
    value = &bVal;
    if (writeTo) {*(bool*)writeTo = bVal;}
  } else if (fUnifiedType == "Vector") {
    value = &vVal;
    if (writeTo) {*(tVector*)writeTo = vVal;}
  } else if (fUnifiedType == "RGB") {
    value = &rgbVal;
    if (writeTo) {*(tRGB*)writeTo = rgbVal;}
  } else if (fUnifiedType == "String") {
    value = &strVal;
    if (writeTo) {*(QString*)writeTo = strVal;}
  } else  {
    if (fUnifiedType.endsWith("List")) {
      QString listType = fUnifiedType.left(fUnifiedType.length()-4);
      if(listType == "Int") {
        value = &intList;
        if (writeTo) {*(tList<int>*)writeTo = intList;}
      } else if (listType == "Real") {
        value = &realList;
        if (writeTo) {*(tList<tReal>*)writeTo = realList;}
      } else if (listType == "Bool") {
        value = &boolList;
        if (writeTo) {*(tList<bool>*)writeTo = boolList;}
      } else if (listType == "Vector") {
        value = &vectorList;
        if (writeTo) {*(tList<tVector>*)writeTo = vectorList;}
      } else if (listType == "RGB") {
        value = &rgbList;
        if (writeTo) {*(tList<tRGB>*)writeTo = rgbList;}
      } else if (listType == "String") {
        value = &stringList;
        if (writeTo) {*(tList<QString>*)writeTo = stringList;}
      } else {
        value = &elList;
        if (writeTo) {*(tList<tElement*>*)writeTo = elList;}
      }
    } else {
      value = &elVal;
      if (writeTo) {writeTo = elVal;}
    }
  }
  return value;
}
//-----------------------------------------------------------------------------

void tUnifiedProperties::updateLinkedPropertyData(void)
{
  setElementLocked
  //tList<tElement*> fElementList = ((tUnifiedProperties*)element)->elementList();

  fUnifiedType  = "None";
  for (int i=0; i<fElementList.count(); i++){
    tElement *el = fElementList.at(i);
    el->lockElement();
    int propId = el->intrface()->getPropertyIndex(fUnifiedProperty);
    if (propId>=0){
      fUnifiedType = el->intrface()->getPropertyType(propId);
      //
      void* propValue = unifiedValue(NULL);
      el->intrface()->getPropertyValue(propId, fUnifiedType, propValue);
      setUnifiedValue(propValue);

      i=fElementList.count();
    }
    el->unlockElement();
  }
}
//-----------------------------------------------------------------------------

