#include "i3PointPlane.h"
#include "t3PointPlane.h"

i3PointPlane::i3PointPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

i3PointPlane::~i3PointPlane()
{
}
//-----------------------------------------------------------------------------

tString i3PointPlane::getPropertyName(int index)
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

tString i3PointPlane::getPropertyType(int index)
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

bool i3PointPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = i3PointPlane::theType();
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

bool i3PointPlane::setPropertyValue(int index, tString type, void* value)
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

bool i3PointPlane::isReadOnly(int index)
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

bool i3PointPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList i3PointPlane::inheritedTypes(void)
{
	QString type;
	i3PointPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool i3PointPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

