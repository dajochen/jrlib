#include "iBSpline.h"
#include "tBSpline.h"

iBSpline::iBSpline(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iBSpline::~iBSpline()
{
}
//-----------------------------------------------------------------------------

tString iBSpline::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nVertices";
	} else if (index == nInheritedProperties()+ 1){
		return "vertices";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iBSpline::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "DotList";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iBSpline::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iBSpline::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tBSpline*)element)->nVertices();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tBSpline*)element)->vertices();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iBSpline::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "DotList") {
		((tBSpline*)element)->setVertices(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iBSpline::isReadOnly(int index)
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

bool iBSpline::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iBSpline::inheritedTypes(void)
{
	QString type;
	iBSpline::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iBSpline::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

