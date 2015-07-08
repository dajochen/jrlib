#include "iStructured3DTwoSidedGrid.h"
#include "tStructured3DTwoSidedGrid.h"

iStructured3DTwoSidedGrid::iStructured3DTwoSidedGrid(tElement *el):iStructured3DGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured3DTwoSidedGrid::~iStructured3DTwoSidedGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured3DTwoSidedGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "ni";
	} else if (index == nInheritedProperties()+ 1){
		return "nj";
	} else if (index == nInheritedProperties()+ 2){
		return "nk";
	} else if (index == nInheritedProperties()+ 3){
		return "faces";
	} else {
		return iStructured3DGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured3DTwoSidedGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "SurfaceList";
	} else {
		return iStructured3DGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DTwoSidedGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured3DTwoSidedGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tStructured3DTwoSidedGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tStructured3DTwoSidedGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tStructured3DTwoSidedGrid*)element)->nk();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "SurfaceList") {
		*(tList<tElement*>*)value = ((tStructured3DTwoSidedGrid*)element)->faces();
		return true;
	} else {
		return iStructured3DGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DTwoSidedGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructured3DGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Int") {
		((tStructured3DTwoSidedGrid*)element)->setNi(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tStructured3DTwoSidedGrid*)element)->setNj(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tStructured3DTwoSidedGrid*)element)->setNk(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "SurfaceList") {
		((tStructured3DTwoSidedGrid*)element)->setFaces(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DTwoSidedGrid::isReadOnly(int index)
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
		return iStructured3DGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DTwoSidedGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructured3DGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured3DTwoSidedGrid::inheritedTypes(void)
{
	QString type;
	iStructured3DTwoSidedGrid::getPropertyValue(0,"String",&type);
	return (iStructured3DGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured3DTwoSidedGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructured3DGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

