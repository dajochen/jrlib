#include "iStructured3DGrid.h"
#include "tStructured3DGrid.h"

iStructured3DGrid::iStructured3DGrid(tElement *el):iStructuredAbstractGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured3DGrid::~iStructured3DGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured3DGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "ni";
	} else if (index == nInheritedProperties()+ 1){
		return "nj";
	} else if (index == nInheritedProperties()+ 2){
		return "nk";
	} else if (index == nInheritedProperties()+ 3){
		return "faceNames";
	} else {
		return iStructuredAbstractGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured3DGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "StringList";
	} else {
		return iStructuredAbstractGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured3DGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tStructured3DGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tStructured3DGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tStructured3DGrid*)element)->nk();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "StringList") {
		*(tList<tString>*)value = ((tStructured3DGrid*)element)->faceNames();
		return true;
	} else {
		return iStructuredAbstractGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructuredAbstractGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2){
		return false;
	} else if(index == nInheritedProperties()+3 && type == "StringList") {
		((tStructured3DGrid*)element)->setFaceNames(*(tList<tString>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DGrid::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return true;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iStructuredAbstractGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructuredAbstractGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured3DGrid::inheritedTypes(void)
{
	QString type;
	iStructured3DGrid::getPropertyValue(0,"String",&type);
	return (iStructuredAbstractGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured3DGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructuredAbstractGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

