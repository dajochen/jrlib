#include "iVariableNameSpace.h"
#include "tVariableNameSpace.h"

iVariableNameSpace::iVariableNameSpace(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iVariableNameSpace::~iVariableNameSpace()
{
}
//-----------------------------------------------------------------------------

tString iVariableNameSpace::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "count";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iVariableNameSpace::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iVariableNameSpace::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iVariableNameSpace::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tVariableNameSpace*)element)->count();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iVariableNameSpace::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iVariableNameSpace::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iVariableNameSpace::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iVariableNameSpace::inheritedTypes(void)
{
	QString type;
	iVariableNameSpace::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iVariableNameSpace::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

