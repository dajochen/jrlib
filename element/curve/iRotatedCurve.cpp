#include "iRotatedCurve.h"
#include "tRotatedCurve.h"

iRotatedCurve::iRotatedCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iRotatedCurve::~iRotatedCurve()
{
}
//-----------------------------------------------------------------------------

tString iRotatedCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "angle";
	} else if (index == nInheritedProperties()+ 1){
		return "referenceAxis";
	} else if (index == nInheritedProperties()+ 2){
		return "referenceCurve";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRotatedCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Line";
	} else if (index == nInheritedProperties()+2){
		return "Curve";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRotatedCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tRotatedCurve*)element)->angle();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedCurve*)element)->axis();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedCurve*)element)->reference();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tRotatedCurve*)element)->setAngle(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tRotatedCurve*)element)->setAxis((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tRotatedCurve*)element)->setReference((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRotatedCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRotatedCurve::inheritedTypes(void)
{
	QString type;
	iRotatedCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRotatedCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

