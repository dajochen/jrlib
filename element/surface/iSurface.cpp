#include "iSurface.h"
#include "tSurface.h"

iSurface::iSurface(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iSurface::~iSurface()
{
}
//-----------------------------------------------------------------------------

tString iSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "uDiv";
	} else if (index == nInheritedProperties()+ 1){
		return "vDiv";
	} else if (index == nInheritedProperties()+ 2){
		return "uRes";
	} else if (index == nInheritedProperties()+ 3){
		return "vRes";
	} else if (index == nInheritedProperties()+ 4){
		return "orientation";
	} else if (index == nInheritedProperties()+ 5){
		return "accurate";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "Int";
	} else if (index == nInheritedProperties()+4){
		return "Bool";
	} else if (index == nInheritedProperties()+5){
		return "Bool";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tSurface*)element)->uDiv();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tSurface*)element)->vDiv();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tSurface*)element)->uRes();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Int") {
		*(int*)value = ((tSurface*)element)->vRes();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Bool") {
		*(bool*)value = ((tSurface*)element)->orientation();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "Bool") {
		*(bool*)value = ((tSurface*)element)->accurate();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Int") {
		((tSurface*)element)->setUDiv(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tSurface*)element)->setVDiv(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tSurface*)element)->setURes(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Int") {
		((tSurface*)element)->setVRes(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "Bool") {
		((tSurface*)element)->setOrientation(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "Bool") {
		((tSurface*)element)->setAccurate(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else if (index == nInheritedProperties()+4){
		return false;
	} else if (index == nInheritedProperties()+5){
		return false;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iSurface::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iSurface::inheritedTypes(void)
{
	QString type;
	iSurface::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

