#include "iAbstractSpline.h"
#include "tAbstractSpline.h"

iAbstractSpline::iAbstractSpline(tElement *el):iDotListCurve(el)
{
}
//-----------------------------------------------------------------------------

iAbstractSpline::~iAbstractSpline()
{
}
//-----------------------------------------------------------------------------

tString iAbstractSpline::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "vertices";
	} else {
		return iDotListCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iAbstractSpline::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "DotList";
	} else {
		return iDotListCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractSpline::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iAbstractSpline::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tAbstractSpline*)element)->vertices();
		return true;
	} else {
		return iDotListCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractSpline::setPropertyValue(int index, tString type, void* value)
{
	if (iDotListCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "DotList") {
		((tAbstractSpline*)element)->setVertices(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iAbstractSpline::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iDotListCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractSpline::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDotListCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iAbstractSpline::inheritedTypes(void)
{
	QString type;
	iAbstractSpline::getPropertyValue(0,"String",&type);
	return (iDotListCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iAbstractSpline::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDotListCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

