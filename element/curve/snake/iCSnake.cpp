#include "iCSnake.h"
#include "tCSnake.h"

iCSnake::iCSnake(tElement *el):iSnake(el)
{
}
//-----------------------------------------------------------------------------

iCSnake::~iCSnake()
{
}
//-----------------------------------------------------------------------------

tString iCSnake::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "vertices";
	} else {
		return iSnake::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iCSnake::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "DotList";
	} else {
		return iSnake::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iCSnake::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iCSnake::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tCSnake*)element)->vertices();
		return true;
	} else {
		return iSnake::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iCSnake::setPropertyValue(int index, tString type, void* value)
{
	if (iSnake::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "DotList") {
		((tCSnake*)element)->setVertices(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iCSnake::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iSnake::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iCSnake::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSnake::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iCSnake::inheritedTypes(void)
{
	QString type;
	iCSnake::getPropertyValue(0,"String",&type);
	return (iSnake::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iCSnake::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSnake::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

