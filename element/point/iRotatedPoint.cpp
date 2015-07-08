#include "iRotatedPoint.h"
#include "tRotatedPoint.h"

iRotatedPoint::iRotatedPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iRotatedPoint::~iRotatedPoint()
{
}
//-----------------------------------------------------------------------------

tString iRotatedPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "angle";
	} else if (index == nInheritedProperties()+ 1){
		return "axis";
	} else if (index == nInheritedProperties()+ 2){
		return "referencePoint";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRotatedPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Line";
	} else if (index == nInheritedProperties()+2){
		return "Dot";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRotatedPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tRotatedPoint*)element)->angle();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedPoint*)element)->axis();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedPoint*)element)->reference();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tRotatedPoint*)element)->setAngle(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tRotatedPoint*)element)->setAxis((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tRotatedPoint*)element)->setReference((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRotatedPoint::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedPoint::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRotatedPoint::inheritedTypes(void)
{
	QString type;
	iRotatedPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRotatedPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

