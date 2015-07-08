#include "iMidCurve.h"
#include "tMidCurve.h"

iMidCurve::iMidCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iMidCurve::~iMidCurve()
{
}
//-----------------------------------------------------------------------------

tString iMidCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nSupportingCurves";
	} else if (index == nInheritedProperties()+ 1){
		return "supportingCurves";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iMidCurve::getPropertyType(int index)
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

bool iMidCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iMidCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tMidCurve*)element)->nCurves();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tMidCurve*)element)->curves();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iMidCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "CurveList") {
		((tMidCurve*)element)->setCurves(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iMidCurve::isReadOnly(int index)
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

bool iMidCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iMidCurve::inheritedTypes(void)
{
	QString type;
	iMidCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iMidCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

