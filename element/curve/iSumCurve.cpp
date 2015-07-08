#include "iSumCurve.h"
#include "tSumCurve.h"

iSumCurve::iSumCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iSumCurve::~iSumCurve()
{
}
//-----------------------------------------------------------------------------

tString iSumCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nSupportCurves";
	} else if (index == nInheritedProperties()+ 1){
		return "supportCurves";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iSumCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "CurveList";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iSumCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iSumCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tSumCurve*)element)->nCurves();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tSumCurve*)element)->supportList();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iSumCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "CurveList") {
		((tSumCurve*)element)->setSupportList(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iSumCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iSumCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iSumCurve::inheritedTypes(void)
{
	QString type;
	iSumCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iSumCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

