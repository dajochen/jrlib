#include "iPolygonCurve.h"
#include "tPolygonCurve.h"

iPolygonCurve::iPolygonCurve(tElement *el):iAbstractSpline(el)
{
}
//-----------------------------------------------------------------------------

iPolygonCurve::~iPolygonCurve()
{
}
//-----------------------------------------------------------------------------

tString iPolygonCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "isLoop";
	} else {
		return iAbstractSpline::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPolygonCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Bool";
	} else {
		return iAbstractSpline::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPolygonCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPolygonCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Bool") {
		*(bool*)value = ((tPolygonCurve*)element)->isLoop();
		return true;
	} else {
		return iAbstractSpline::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPolygonCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iAbstractSpline::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Bool") {
		((tPolygonCurve*)element)->setIsLoop(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPolygonCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iAbstractSpline::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPolygonCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iAbstractSpline::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPolygonCurve::inheritedTypes(void)
{
	QString type;
	iPolygonCurve::getPropertyValue(0,"String",&type);
	return (iAbstractSpline::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPolygonCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iAbstractSpline::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

