#include "iYPlane.h"
#include "tYPlane.h"

iYPlane::iYPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

iYPlane::~iYPlane()
{
}
//-----------------------------------------------------------------------------

tString iYPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "y";
	} else {
		return iBasicPlane::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iYPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else {
		return iBasicPlane::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iYPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iYPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tYPlane*)element)->y();
		return true;
	} else {
		return iBasicPlane::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iYPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iBasicPlane::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tYPlane*)element)->setY(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iYPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iBasicPlane::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iYPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iYPlane::inheritedTypes(void)
{
	QString type;
	iYPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iYPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

