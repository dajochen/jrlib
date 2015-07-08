#include "iTransformedDotListCurve.h"
#include "tTransformedDotListCurve.h"

iTransformedDotListCurve::iTransformedDotListCurve(tElement *el):iDotListCurve(el)
{
}
//-----------------------------------------------------------------------------

iTransformedDotListCurve::~iTransformedDotListCurve()
{
}
//-----------------------------------------------------------------------------

tString iTransformedDotListCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "referenceCurve";
	} else if (index == nInheritedProperties()+ 1){
		return "axis";
	} else if (index == nInheritedProperties()+ 2){
		return "angle";
	} else if (index == nInheritedProperties()+ 3){
		return "shift";
	} else {
		return iDotListCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iTransformedDotListCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Curve";
	} else if (index == nInheritedProperties()+1){
		return "Line";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Vector";
	} else {
		return iDotListCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iTransformedDotListCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iTransformedDotListCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tTransformedDotListCurve*)element)->referenceCurve();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tTransformedDotListCurve*)element)->axis();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tTransformedDotListCurve*)element)->angle();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Vector") {
		*(tVector*)value = ((tTransformedDotListCurve*)element)->shift();
		return true;
	} else {
		return iDotListCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iTransformedDotListCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iDotListCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tTransformedDotListCurve*)element)->setReferenceCurve((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tTransformedDotListCurve*)element)->setAxis((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tTransformedDotListCurve*)element)->setAngle(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Vector") {
		((tTransformedDotListCurve*)element)->setShift(*(tVector*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iTransformedDotListCurve::isReadOnly(int index)
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
		return iDotListCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iTransformedDotListCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDotListCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iTransformedDotListCurve::inheritedTypes(void)
{
	QString type;
	iTransformedDotListCurve::getPropertyValue(0,"String",&type);
	return (iDotListCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iTransformedDotListCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDotListCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

