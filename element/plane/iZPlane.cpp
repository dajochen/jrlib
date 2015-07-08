#include "iZPlane.h"
#include "tZPlane.h"

iZPlane::iZPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

iZPlane::~iZPlane()
{
}
//-----------------------------------------------------------------------------

tString iZPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "z";
	} else {
		return iBasicPlane::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iZPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else {
		return iBasicPlane::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iZPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iZPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tZPlane*)element)->z();
		return true;
	} else {
		return iBasicPlane::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iZPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iBasicPlane::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tZPlane*)element)->setZ(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iZPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iBasicPlane::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iZPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iZPlane::inheritedTypes(void)
{
	QString type;
	iZPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iZPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

