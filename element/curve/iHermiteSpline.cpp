#include "iHermiteSpline.h"
#include "tHermiteSpline.h"

iHermiteSpline::iHermiteSpline(tElement *el):iAbstractSpline(el)
{
}
//-----------------------------------------------------------------------------

iHermiteSpline::~iHermiteSpline()
{
}
//-----------------------------------------------------------------------------

tString iHermiteSpline::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "tension";
	} else if (index == nInheritedProperties()+ 1){
		return "bias";
	} else if (index == nInheritedProperties()+ 2){
		return "continuity";
	} else {
		return iAbstractSpline::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iHermiteSpline::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else {
		return iAbstractSpline::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iHermiteSpline::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iHermiteSpline::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tHermiteSpline*)element)->tension();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tHermiteSpline*)element)->bias();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tHermiteSpline*)element)->continuity();
		return true;
	} else {
		return iAbstractSpline::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iHermiteSpline::setPropertyValue(int index, tString type, void* value)
{
	if (iAbstractSpline::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tHermiteSpline*)element)->setTension(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tHermiteSpline*)element)->setBias(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tHermiteSpline*)element)->setContinuity(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iHermiteSpline::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iAbstractSpline::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iHermiteSpline::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iAbstractSpline::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iHermiteSpline::inheritedTypes(void)
{
	QString type;
	iHermiteSpline::getPropertyValue(0,"String",&type);
	return (iAbstractSpline::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iHermiteSpline::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iAbstractSpline::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

