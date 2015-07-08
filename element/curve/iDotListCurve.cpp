#include "iDotListCurve.h"
#include "tDotListCurve.h"

iDotListCurve::iDotListCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iDotListCurve::~iDotListCurve()
{
}
//-----------------------------------------------------------------------------

tString iDotListCurve::getPropertyName(int index)
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

tString iDotListCurve::getPropertyType(int index)
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

bool iDotListCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iDotListCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tDotListCurve*)element)->nVertices();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tDotListCurve*)element)->vertices();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iDotListCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iDotListCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iDotListCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iDotListCurve::inheritedTypes(void)
{
	QString type;
	iDotListCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iDotListCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

