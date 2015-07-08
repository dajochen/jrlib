#include "iDot.h"
#include "tDot.h"

iDot::iDot(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iDot::~iDot()
{
}
//-----------------------------------------------------------------------------

tString iDot::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "location";
	} else if (index == nInheritedProperties()+ 1){
		return "dependents";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iDot::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "ElementList";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iDot::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iDot::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tDot*)element)->vector();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "ElementList") {
		*(tList<tElement*>*)value = ((tDot*)element)->dependents();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iDot::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iDot::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iDot::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iDot::inheritedTypes(void)
{
	QString type;
	iDot::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iDot::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

