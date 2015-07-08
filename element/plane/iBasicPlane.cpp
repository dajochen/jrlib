#include "iBasicPlane.h"
#include "tBasicPlane.h"

iBasicPlane::iBasicPlane(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iBasicPlane::~iBasicPlane()
{
}
//-----------------------------------------------------------------------------

tString iBasicPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "center";
	} else if (index == nInheritedProperties()+ 1){
		return "normal";
	} else if (index == nInheritedProperties()+ 2){
		return "horizontalDir";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iBasicPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Vector";
	} else if (index == nInheritedProperties()+2){
		return "Vector";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iBasicPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iBasicPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tBasicPlane*)element)->center();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Vector") {
		*(tVector*)value = ((tBasicPlane*)element)->normal();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Vector") {
		*(tVector*)value = ((tBasicPlane*)element)->horizontalDir();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iBasicPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iBasicPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return true;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iBasicPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iBasicPlane::inheritedTypes(void)
{
	QString type;
	iBasicPlane::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iBasicPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

