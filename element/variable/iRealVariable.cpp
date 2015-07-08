#include "iRealVariable.h"
#include "tRealVariable.h"

iRealVariable::iRealVariable(tElement *el):iVariable(el)
{
}
//-----------------------------------------------------------------------------

iRealVariable::~iRealVariable()
{
}
//-----------------------------------------------------------------------------

tString iRealVariable::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "value";
	} else {
		return iVariable::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRealVariable::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else {
		return iVariable::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRealVariable::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRealVariable::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tRealVariable*)element)->value();
		return true;
	} else {
		return iVariable::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRealVariable::setPropertyValue(int index, tString type, void* value)
{
	if (iVariable::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tRealVariable*)element)->setValue(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRealVariable::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iVariable::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRealVariable::isOptional(QString propName)
{
  if (QString(",value,").contains("," + propName + ",")) {
    return true;
  } else {
    return iVariable::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRealVariable::inheritedTypes(void)
{
	QString type;
	iRealVariable::getPropertyValue(0,"String",&type);
	return (iVariable::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRealVariable::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iVariable::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

