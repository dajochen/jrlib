#include "iPolyCurve.h"
#include "tPolyCurve.h"

iPolyCurve::iPolyCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iPolyCurve::~iPolyCurve()
{
}
//-----------------------------------------------------------------------------

tString iPolyCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nSupportingCurves";
	} else if (index == nInheritedProperties()+ 1){
		return "supportingCurves";
	} else if (index == nInheritedProperties()+ 2){
		return "reverseCurve";
	} else if (index == nInheritedProperties()+ 3){
		return "interpolationMode";
	} else if (index == nInheritedProperties()+ 4){
		return "gapTolerance";
	} else if (index == nInheritedProperties()+ 5){
		return "autoClosePolyCurve";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPolyCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "CurveList";
	} else if (index == nInheritedProperties()+2){
		return "IntList";
	} else if (index == nInheritedProperties()+3){
		return "Int";
	} else if (index == nInheritedProperties()+4){
		return "Real";
	} else if (index == nInheritedProperties()+5){
		return "Bool";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPolyCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPolyCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tPolyCurve*)element)->nCurves();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tPolyCurve*)element)->curves();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "IntList") {
		*(tList<int>*)value = ((tPolyCurve*)element)->reversedCurves();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Int") {
		*(int*)value = ((tPolyCurve*)element)->polyCurveType();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Real") {
		*(tReal*)value = ((tPolyCurve*)element)->gapTolerance();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "Bool") {
		*(bool*)value = ((tPolyCurve*)element)->autoClosePolyCurve();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPolyCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "CurveList") {
		((tPolyCurve*)element)->setCurves(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "IntList") {
		((tPolyCurve*)element)->setReversedCurves(*(tList<int>*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Int") {
		((tPolyCurve*)element)->setPolyCurveType(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "Real") {
		((tPolyCurve*)element)->setGapTolerance(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "Bool") {
		((tPolyCurve*)element)->setAutoClosePolyCurve(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPolyCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else if (index == nInheritedProperties()+4){
		return false;
	} else if (index == nInheritedProperties()+5){
		return false;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPolyCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPolyCurve::inheritedTypes(void)
{
	QString type;
	iPolyCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPolyCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

