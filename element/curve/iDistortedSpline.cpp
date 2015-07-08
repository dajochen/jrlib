#include "iDistortedSpline.h"
#include "tDistortedSpline.h"

iDistortedSpline::iDistortedSpline(tElement *el):iDotListCurve(el)
{
}
//-----------------------------------------------------------------------------

iDistortedSpline::~iDistortedSpline()
{
}
//-----------------------------------------------------------------------------

tString iDistortedSpline::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "baseSpline";
	} else if (index == nInheritedProperties()+ 1){
		return "baseSurfaces";
	} else if (index == nInheritedProperties()+ 2){
		return "distortedSurfaces";
	} else {
		return iDotListCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iDistortedSpline::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "AbstractSpline";
	} else if (index == nInheritedProperties()+1){
		return "Group";
	} else if (index == nInheritedProperties()+2){
		return "Group";
	} else {
		return iDotListCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iDistortedSpline::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iDistortedSpline::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "AbstractSpline"|| propType=="Element")) {
		*(tElement**)value = ((tDistortedSpline*)element)->baseSpline();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Group"|| propType=="Element")) {
		*(tElement**)value = ((tDistortedSpline*)element)->baseFaces();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Group"|| propType=="Element")) {
		*(tElement**)value = ((tDistortedSpline*)element)->distortedFaces();
		return true;
	} else {
		return iDotListCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iDistortedSpline::setPropertyValue(int index, tString type, void* value)
{
	if (iDotListCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "AbstractSpline" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("AbstractSpline")))) {
		((tDistortedSpline*)element)->setBaseSpline((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Group" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Group")))) {
		((tDistortedSpline*)element)->setBaseFaces((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Group" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Group")))) {
		((tDistortedSpline*)element)->setDistortedFaces((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iDistortedSpline::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iDotListCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iDistortedSpline::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDotListCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iDistortedSpline::inheritedTypes(void)
{
	QString type;
	iDistortedSpline::getPropertyValue(0,"String",&type);
	return (iDotListCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iDistortedSpline::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDotListCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

