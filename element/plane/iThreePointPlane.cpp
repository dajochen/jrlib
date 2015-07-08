#include "iThreePointPlane.h"
#include "tThreePointPlane.h"

iThreePointPlane::iThreePointPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

iThreePointPlane::~iThreePointPlane()
{
}
//-----------------------------------------------------------------------------

tString iThreePointPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "centerPoint";
	} else if (index == nInheritedProperties()+ 1){
		return "p1";
	} else if (index == nInheritedProperties()+ 2){
		return "p2";
	} else {
		return iBasicPlane::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iThreePointPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Dot";
	} else if (index == nInheritedProperties()+1){
		return "Dot";
	} else if (index == nInheritedProperties()+2){
		return "Dot";
	} else {
		return iBasicPlane::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iThreePointPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iThreePointPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tThreePointPlane*)element)->centerPoint();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tThreePointPlane*)element)->p1();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tThreePointPlane*)element)->p2();
		return true;
	} else {
		return iBasicPlane::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iThreePointPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iBasicPlane::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tThreePointPlane*)element)->setCenter((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tThreePointPlane*)element)->setP1((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tThreePointPlane*)element)->setP2((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iThreePointPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iBasicPlane::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iThreePointPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iThreePointPlane::inheritedTypes(void)
{
	QString type;
	iThreePointPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iThreePointPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

