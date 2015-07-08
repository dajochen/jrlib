#include "iVectorVariable.h"
#include "tVectorVariable.h"

iVectorVariable::iVectorVariable(tElement *el):iVariable(el)
{
}
//-----------------------------------------------------------------------------

iVectorVariable::~iVectorVariable()
{
}
//-----------------------------------------------------------------------------

tString iVectorVariable::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "value";
	} else {
		return iVariable::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iVectorVariable::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else {
		return iVariable::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iVectorVariable::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iVectorVariable::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tVectorVariable*)element)->value();
		return true;
	} else {
		return iVariable::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iVectorVariable::setPropertyValue(int index, tString type, void* value)
{
	if (iVariable::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Vector") {
		((tVectorVariable*)element)->setValue(*(tVector*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iVectorVariable::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iVariable::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iVectorVariable::isOptional(QString propName)
{
  if (QString(",value,").contains("," + propName + ",")) {
    return true;
  } else {
    return iVariable::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iVectorVariable::inheritedTypes(void)
{
	QString type;
	iVectorVariable::getPropertyValue(0,"String",&type);
	return (iVariable::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iVectorVariable::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iVariable::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

