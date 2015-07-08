#include "iFunctionCurve.h"
#include "tFunctionCurve.h"

iFunctionCurve::iFunctionCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iFunctionCurve::~iFunctionCurve()
{
}
//-----------------------------------------------------------------------------

tString iFunctionCurve::getPropertyName(int index)
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
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iFunctionCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "String";
	} else if (index == nInheritedProperties()+1){
		return "CurveList";
	} else if (index == nInheritedProperties()+2){
		return "String";
	} else if (index == nInheritedProperties()+3){
		return "String";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iFunctionCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "String") {
		*(tString*)value = ((tFunctionCurve*)element)->variableStringList();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tFunctionCurve*)element)->referenceCurves();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "String") {
		*(tString*)value = ((tFunctionCurve*)element)->functions();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "String") {
		*(tString*)value = ((tFunctionCurve*)element)->lastAddedFunction();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "CurveList") {
		((tFunctionCurve*)element)->setReferenceCurves(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "String") {
		((tFunctionCurve*)element)->setFunctions(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "String") {
		((tFunctionCurve*)element)->addFunctionManually(*(tString*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iFunctionCurve::isReadOnly(int index)
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
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionCurve::isOptional(QString propName)
{
  if (QString(",addFunction,").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iFunctionCurve::inheritedTypes(void)
{
	QString type;
	iFunctionCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iFunctionCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

