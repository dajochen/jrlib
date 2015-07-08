#include "iSnake.h"
#include "tSnake.h"

iSnake::iSnake(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iSnake::~iSnake()
{
}
//-----------------------------------------------------------------------------

tString iSnake::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "reference";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iSnake::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Surface";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iSnake::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iSnake::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tSnake*)element)->reference();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iSnake::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iSnake::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iSnake::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iSnake::inheritedTypes(void)
{
	QString type;
	iSnake::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iSnake::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

