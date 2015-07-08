#include "iCSpline.h"
#include "tCSpline.h"

iCSpline::iCSpline(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iCSpline::~iCSpline()
{
}
//-----------------------------------------------------------------------------

tString iCSpline::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nVertices";
	} else if (index == nInheritedProperties()+ 1){
		return "smoothingType";
	} else if (index == nInheritedProperties()+ 2){
		return "vertices";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iCSpline::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "DotList";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iCSpline::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iCSpline::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tCSpline*)element)->nVertices();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tCSpline*)element)->CSplineType();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tCSpline*)element)->vertices();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iCSpline::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tCSpline*)element)->setCSplineType(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "DotList") {
		((tCSpline*)element)->setVertices(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iCSpline::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iCSpline::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iCSpline::inheritedTypes(void)
{
	QString type;
	iCSpline::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iCSpline::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

