#include "iCLoft.h"
#include "tCLoft.h"

iCLoft::iCLoft(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iCLoft::~iCLoft()
{
}
//-----------------------------------------------------------------------------

tString iCLoft::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "numberOfCurves";
	} else if (index == nInheritedProperties()+ 1){
		return "curves";
	} else if (index == nInheritedProperties()+ 2){
		return "degree";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iCLoft::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "CurveList";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iCLoft::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iCLoft::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tCLoft*)element)->nCurves();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tCLoft*)element)->curves();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tCLoft*)element)->degree();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iCLoft::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "CurveList") {
		((tCLoft*)element)->setCurves(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tCLoft*)element)->setDegree(*(int*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iCLoft::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iCLoft::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iCLoft::inheritedTypes(void)
{
	QString type;
	iCLoft::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iCLoft::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

