#include "iXPlane.h"
#include "tXPlane.h"

iXPlane::iXPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

iXPlane::~iXPlane()
{
}
//-----------------------------------------------------------------------------

tString iXPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "x";
	} else {
		return iBasicPlane::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iXPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else {
		return iBasicPlane::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iXPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iXPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tXPlane*)element)->x();
		return true;
	} else {
		return iBasicPlane::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iXPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iBasicPlane::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tXPlane*)element)->setX(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iXPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iBasicPlane::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iXPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iXPlane::inheritedTypes(void)
{
	QString type;
	iXPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iXPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

