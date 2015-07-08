#include "iRevolvedSurface.h"
#include "tRevolvedSurface.h"

iRevolvedSurface::iRevolvedSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iRevolvedSurface::~iRevolvedSurface()
{
}
//-----------------------------------------------------------------------------

tString iRevolvedSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "axis";
	} else if (index == nInheritedProperties()+ 1){
		return "refCurve";
	} else if (index == nInheritedProperties()+ 2){
		return "startAngle";
	} else if (index == nInheritedProperties()+ 3){
		return "endAngle";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRevolvedSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Line";
	} else if (index == nInheritedProperties()+1){
		return "Curve";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRevolvedSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRevolvedSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tRevolvedSurface*)element)->axis();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tRevolvedSurface*)element)->refCurve();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tRevolvedSurface*)element)->startAngle();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tRevolvedSurface*)element)->endAngle();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRevolvedSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tRevolvedSurface*)element)->setAxis((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tRevolvedSurface*)element)->setRefCurve((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tRevolvedSurface*)element)->setStartAngle(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Real") {
		((tRevolvedSurface*)element)->setEndAngle(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRevolvedSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRevolvedSurface::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRevolvedSurface::inheritedTypes(void)
{
	QString type;
	iRevolvedSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRevolvedSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

