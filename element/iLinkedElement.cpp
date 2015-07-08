#include "iLinkedElement.h"
#include "tLinkedElement.h"

iLinkedElement::iLinkedElement(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iLinkedElement::~iLinkedElement()
{
}
//-----------------------------------------------------------------------------

tString iLinkedElement::getPropertyName(int index)
{
  if (linkedObjectIFace() && index >= nProperties()-nLinkedElementProperties()){
    return "link." + linkedObjectIFace()->getPropertyName(index - (nProperties()-nLinkedElementProperties()));
  } else if (index == nInheritedProperties()){
		return "reference";
  } else if (index == nInheritedProperties()+ 1){
    return "linkedProperty";
  } else if (index == nInheritedProperties()+ 2){
    return "linkedElement";
  } else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iLinkedElement::getPropertyType(int index)
{
  if (linkedObjectIFace() && index >= nProperties()-nLinkedElementProperties()){
    return linkedObjectIFace()->getPropertyType(index - (nProperties()-nLinkedElementProperties()));
  } else if (index == nInheritedProperties()){
		return "Element";
	} else if (index == nInheritedProperties()+1){
		return "String";
  } else if (index == nInheritedProperties()+ 2){
    tElement *linked = dynamic_cast<tLinkedElement*>(element)->linkedElement();
    if (linked) {
      return linked->intrface()->type();
    } else {
      return "None";
    }
  } else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iLinkedElement::getPropertyValue(int index, tString propType, void* value)
{
  if (linkedObjectIFace() && index >= nProperties()-nLinkedElementProperties()){
    return linkedObjectIFace()->getPropertyValue(index - (nProperties()-nLinkedElementProperties()), propType, value);
  } else if (index == 0 && propType == "String"){
		*(tString*)value = iLinkedElement::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Element"){
		*(tElement**)value = ((tLinkedElement*)element)->reference();
		return true;
  } else if (index == nInheritedProperties()+1 && propType == "String"){
    *(tString*)value = ((tLinkedElement*)element)->property();
    return true;
  } else if (index == nInheritedProperties()+2){
    tElement *linked = dynamic_cast<tLinkedElement*>(element)->linkedElement();
    if (linked && propType == linked->intrface()->type()) {
      *(tElement**)value = linked;
      return true;
    } else {
      return false;
    }
  } else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iLinkedElement::setPropertyValue(int index, tString type, void* value)
{
  if (iElement::setPropertyValue(index,type,value)){
    return true;
  } else if (linkedObjectIFace() && index >= nProperties()-nLinkedElementProperties()){
    return linkedObjectIFace()->setPropertyValue(index - (nProperties()-nLinkedElementProperties()), type, value);
  } else if (index == nInheritedProperties()+0 && type == "Element"){
		((tLinkedElement*)element)->setReference((tElement*)value);
		return true;
  } else if(index == nInheritedProperties()+1 && type == "String"){
    ((tLinkedElement*)element)->setProperty(*(tString*)value);
    return true;
  } else if(index == nInheritedProperties()+2){
    return false;
  } else {
    return false;
	}
}
//-----------------------------------------------------------------------------

bool iLinkedElement::isReadOnly(int index)
{
  if (linkedObjectIFace() && index >= nProperties()-nLinkedElementProperties()){
    return linkedObjectIFace()->isReadOnly(index - (nProperties()-nLinkedElementProperties()));
  } else if (index == nInheritedProperties()){
		return false;
  } else if (index == nInheritedProperties()+1){
    return false;
  } else if (index == nInheritedProperties()+2){
    return true;
  } else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iLinkedElement::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iLinkedElement::inheritedTypes(void)
{
	QString type;
	iLinkedElement::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iLinkedElement::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------
unsigned int iLinkedElement::nInheritedProperties(void)
{
  return iElement::nProperties();
}
//-----------------------------------------------------------------------------

unsigned int iLinkedElement::nLinkedElementProperties(void)
{
  int nProps=0;
  if(linkedObjectIFace()){
    nProps+=linkedObjectIFace()->nProperties();
  }
  return nProps;
}
//-----------------------------------------------------------------------------

int iLinkedElement::nProperties(void)
{
  return iElement::nProperties() + 3 + nLinkedElementProperties();
}
//-----------------------------------------------------------------------------

iElement *iLinkedElement::linkedObjectIFace()
{
  element->update();
  tLinkedElement *linkedEl = dynamic_cast<tLinkedElement*>(element);
  if (linkedEl->linkedElement()){
    return linkedEl->linkedElement()->intrface();
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------
