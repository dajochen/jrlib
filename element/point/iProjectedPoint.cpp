#include "iProjectedPoint.h"
#include "tProjectedPoint.h"

iProjectedPoint::iProjectedPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iProjectedPoint::~iProjectedPoint()
{
}
//-----------------------------------------------------------------------------

tString iProjectedPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "origin";
	} else if (index == nInheritedProperties()+ 1){
		return "refDot";
	} else if (index == nInheritedProperties()+ 2){
		return "plane";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iProjectedPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Dot";
	} else if (index == nInheritedProperties()+2){
		return "Plane";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iProjectedPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iProjectedPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tProjectedPoint*)element)->origin();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tProjectedPoint*)element)->refDot();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Plane"|| propType=="Element")) {
		*(tElement**)value = ((tProjectedPoint*)element)->plane();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iProjectedPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Vector") {
		((tProjectedPoint*)element)->setOrigin(*(tVector*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tProjectedPoint*)element)->setRefDot((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Plane" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Plane")))) {
		((tProjectedPoint*)element)->setPlane((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iProjectedPoint::isReadOnly(int index)
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

bool iProjectedPoint::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iProjectedPoint::inheritedTypes(void)
{
	QString type;
	iProjectedPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iProjectedPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

