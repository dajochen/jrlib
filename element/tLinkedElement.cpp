#include "tLinkedElement.h"

tLinkedElement::tLinkedElement(void* theOwner, tElement *ref, QString prop)
  : tElement(theOwner),
    fReference(NULL),
    fLinkedElement(NULL),
    fLinkedProperty("")
{
  setReference(ref);
  setProperty(prop);
}

tLinkedElement::~tLinkedElement()
{
  setReference(NULL);
  update();
}

iElement *tLinkedElement::intrface()
{
  update();
  if (iface == NULL){
    iface = new iLinkedElement(this);
  }
  return iface;
}

void tLinkedElement::refresh()
{
  fLinkedElement = NULL;
  if (fReference){
    fReference->update();
    if (!fLinkedProperty.isEmpty()){
      int index = fReference->intrface()->getPropertyIndex(fLinkedProperty);
      QString type = fReference->intrface()->getPropertyType(index);
      if (!fReference->intrface()->nonElementTypes().contains(type)){
        fReference->intrface()->getPropertyValue(index, type, &fLinkedElement);
      }
    } else {// if fLinkedProperty is empty, fReference is the linkedElement
      fLinkedElement = fReference;
    }
  }
}

QString tLinkedElement::property()
{
  return fLinkedProperty;
}

void tLinkedElement::setProperty(QString property)
{
  fLinkedProperty = property;
  invalidate(this);
}

tElement *tLinkedElement::reference()
{
  return fReference;
}

void tLinkedElement::setReference(tElement *el)
{
  if (el!=fReference){
    if (fReference)
      fReference->removeDependent(this);

    fReference = el;
    if (fReference && !fReference->addDependent(this))
      fReference = NULL;
    invalidate(this);
  }
}
