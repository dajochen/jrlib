#include "iCurve.h"
#include "tCurve.h"

iCurve::iCurve(tElement *el):iPaintableElement(el)
{
}
//-----------------------------------------------------------------------------

iCurve::~iCurve()
{
}
//-----------------------------------------------------------------------------

tString iCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "length";
	} else if (index == nInheritedProperties()+ 1){
		return "t-Resolution";
	} else if (index == nInheritedProperties()+ 2){
		return "arrowheadPosition";
	} else if (index == nInheritedProperties()+ 3){
		return "lineWidth";
	} else {
		return iPaintableElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else {
		return iPaintableElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tCurve*)element)->length();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tCurve*)element)->tResolution();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tCurve*)element)->arrowheadPos();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tCurve*)element)->lineWidth();
		return true;
	} else {
		return iPaintableElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iPaintableElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tCurve*)element)->setTResolution(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tCurve*)element)->setArrowheadPos(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Real") {
		((tCurve*)element)->setLineWidth(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iCurve::isReadOnly(int index)
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
		return iPaintableElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iPaintableElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iCurve::inheritedTypes(void)
{
	QString type;
	iCurve::getPropertyValue(0,"String",&type);
	return (iPaintableElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPaintableElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

