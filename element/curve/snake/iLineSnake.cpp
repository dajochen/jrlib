#include "iLineSnake.h"
#include "tLineSnake.h"

iLineSnake::iLineSnake(tElement *el):iSnake(el)
{
}
//-----------------------------------------------------------------------------

iLineSnake::~iLineSnake()
{
}
//-----------------------------------------------------------------------------

tString iLineSnake::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "start";
	} else if (index == nInheritedProperties()+ 1){
		return "end";
	} else {
		return iSnake::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iLineSnake::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "AbsMagnet";
	} else if (index == nInheritedProperties()+1){
		return "AbsMagnet";
	} else {
		return iSnake::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iLineSnake::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iLineSnake::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "AbsMagnet"|| propType=="Element")) {
		*(tElement**)value = ((tLineSnake*)element)->start();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "AbsMagnet"|| propType=="Element")) {
		*(tElement**)value = ((tLineSnake*)element)->end();
		return true;
	} else {
		return iSnake::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iLineSnake::setPropertyValue(int index, tString type, void* value)
{
	if (iSnake::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "AbsMagnet" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("AbsMagnet")))) {
		((tLineSnake*)element)->setStart((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "AbsMagnet" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("AbsMagnet")))) {
		((tLineSnake*)element)->setEnd((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iLineSnake::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iSnake::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iLineSnake::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSnake::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iLineSnake::inheritedTypes(void)
{
	QString type;
	iLineSnake::getPropertyValue(0,"String",&type);
	return (iSnake::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iLineSnake::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSnake::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

