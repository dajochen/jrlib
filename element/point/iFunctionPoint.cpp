#include "iFunctionPoint.h"
#include "tFunctionPoint.h"

iFunctionPoint::iFunctionPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iFunctionPoint::~iFunctionPoint()
{
}
//-----------------------------------------------------------------------------

tString iFunctionPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "availableVariables";
	} else if (index == nInheritedProperties()+ 1){
		return "references";
	} else if (index == nInheritedProperties()+ 2){
		return "functions";
	} else if (index == nInheritedProperties()+ 3){
		return "addFunction";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iFunctionPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "String";
	} else if (index == nInheritedProperties()+1){
		return "DotList";
	} else if (index == nInheritedProperties()+2){
		return "String";
	} else if (index == nInheritedProperties()+3){
		return "String";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iFunctionPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "String") {
		*(tString*)value = ((tFunctionPoint*)element)->variableStringList();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tFunctionPoint*)element)->referenceDots();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "String") {
		*(tString*)value = ((tFunctionPoint*)element)->functions();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "String") {
		*(tString*)value = ((tFunctionPoint*)element)->lastAddedFunction();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "DotList") {
		((tFunctionPoint*)element)->setReferenceDots(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "String") {
		((tFunctionPoint*)element)->setFunctions(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "String") {
		((tFunctionPoint*)element)->addFunctionManually(*(tString*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iFunctionPoint::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionPoint::isOptional(QString propName)
{
  if (QString(",addFunction,").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iFunctionPoint::inheritedTypes(void)
{
	QString type;
	iFunctionPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iFunctionPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

