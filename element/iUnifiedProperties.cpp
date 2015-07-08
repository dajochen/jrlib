#include "iUnifiedProperties.h"
#include "tUnifiedProperties.h"

iUnifiedProperties::iUnifiedProperties(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iUnifiedProperties::~iUnifiedProperties()
{
}
//-----------------------------------------------------------------------------

tString iUnifiedProperties::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
    return "elementList";
  } else if (index == nInheritedProperties()+ 1){
    return "unifiedProperty";
  } else if (index == nInheritedProperties()+ 2){
    return ((tUnifiedProperties*)element)->unifiedProperty();
    //return "unifiedValue";
  } else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iUnifiedProperties::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
    return "ElementList";
	} else if (index == nInheritedProperties()+1){
		return "String";
  } else if (index == nInheritedProperties()+2){
    return ((tUnifiedProperties*)element)->unifiedType();
  } else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iUnifiedProperties::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iUnifiedProperties::theType();
		return true;
  } else if (index == nInheritedProperties()+0 && propType == "ElementList"){
    *(tList<tElement*>*)value = ((tUnifiedProperties*)element)->elementList();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "String"){
    *(tString*)value = ((tUnifiedProperties*)element)->unifiedProperty();
		return true;
  } else if (index == nInheritedProperties()+2 && propType == ((tUnifiedProperties*)element)->unifiedType()){
    ((tUnifiedProperties*)element)->unifiedValue(value);
    return true;
  } else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iUnifiedProperties::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
  } else if(index == nInheritedProperties()+0 && type == "ElementList"){
    ((tUnifiedProperties*)element)->setElementList(*(tList<tElement*>*)value);
    ((tUnifiedProperties*)element)->updateLinkedPropertyData();
    //element->invalidate(element);
		return true;
  } else if(index == nInheritedProperties()+1 && type == "String"){
    ((tUnifiedProperties*)element)->setUnifiedProperty(*(QString*)value);
    ((tUnifiedProperties*)element)->updateLinkedPropertyData();
    //element->invalidate(element);
		return true;
  } else if (index == nInheritedProperties()+2 && type == ((tUnifiedProperties*)element)->unifiedType()){
    ((tUnifiedProperties*)element)->setUnifiedValue(value);
    //element->invalidate(element);
    return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iUnifiedProperties::isReadOnly(int index)
{
    if (index == nInheritedProperties()){
		return false;
  } else if (index == nInheritedProperties()+1){
    return false;
  } else if (index == nInheritedProperties()+2){
    if (getPropertyType(index) != "None"){
      return false;
    } else {
      return true;
    }
  } else {
    return iElement::isReadOnly(index);
  }
}
//-----------------------------------------------------------------------------

bool iUnifiedProperties::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iUnifiedProperties::inheritedTypes(void)
{
	QString type;
	iUnifiedProperties::getPropertyValue(0,"String",&type);
  return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

int iUnifiedProperties::nProperties()
{
  if (((tUnifiedProperties*)element)->unifiedType() != "None"){
    return iElement::nProperties() + 3;
  } else {
    return iElement::nProperties() + 2;
  }
}
//-----------------------------------------------------------------------------

bool iUnifiedProperties::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------


