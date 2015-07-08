#include "iPlane.h"
#include "tPlane.h"

iPlane::iPlane(tElement *el):iBasicPlane(el)
{
}
//-----------------------------------------------------------------------------

iPlane::~iPlane()
{
}
//-----------------------------------------------------------------------------

tString iPlane::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "centerPoint";
	} else if (index == nInheritedProperties()+ 1){
		return "onNormal";
	} else if (index == nInheritedProperties()+ 2){
		return "onHorizontal";
	} else if (index == nInheritedProperties()+ 3){
		return "mode";
	} else {
		return iBasicPlane::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPlane::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Dot";
	} else if (index == nInheritedProperties()+1){
		return "Dot";
	} else if (index == nInheritedProperties()+2){
		return "Dot";
	} else if (index == nInheritedProperties()+3){
		return "Int";
	} else {
		return iBasicPlane::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPlane::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPlane::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tPlane*)element)->centerPoint();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tPlane*)element)->onNormal();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tPlane*)element)->onHorizontal();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Int") {
		*(int*)value = ((tPlane*)element)->mode();
		return true;
	} else {
		return iBasicPlane::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPlane::setPropertyValue(int index, tString type, void* value)
{
	if (iBasicPlane::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tPlane*)element)->setCenter((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tPlane*)element)->setOnNormal((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tPlane*)element)->setOnHorizontal((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Int") {
		((tPlane*)element)->setMode(*(int*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPlane::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iBasicPlane::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPlane::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iBasicPlane::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPlane::inheritedTypes(void)
{
	QString type;
	iPlane::getPropertyValue(0,"String",&type);
	return (iBasicPlane::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPlane::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iBasicPlane::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

