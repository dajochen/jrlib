#include "iStructured3DBlockMeshGrid.h"
#include "tStructured3DBlockMeshGrid.h"

iStructured3DBlockMeshGrid::iStructured3DBlockMeshGrid(tElement *el):iStructured3DGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured3DBlockMeshGrid::~iStructured3DBlockMeshGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured3DBlockMeshGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "ni";
	} else if (index == nInheritedProperties()+ 1){
		return "nj";
	} else if (index == nInheritedProperties()+ 2){
		return "nk";
	} else if (index == nInheritedProperties()+ 3){
		return "corners";
	} else if (index == nInheritedProperties()+ 4){
		return "edges";
	} else if (index == nInheritedProperties()+ 5){
		return "faces";
	} else {
		return iStructured3DGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured3DBlockMeshGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "DotList";
	} else if (index == nInheritedProperties()+4){
		return "CurveList";
	} else if (index == nInheritedProperties()+5){
		return "SurfaceList";
	} else {
		return iStructured3DGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DBlockMeshGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured3DBlockMeshGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tStructured3DBlockMeshGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tStructured3DBlockMeshGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tStructured3DBlockMeshGrid*)element)->nk();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tStructured3DBlockMeshGrid*)element)->corners();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tStructured3DBlockMeshGrid*)element)->edges();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "SurfaceList") {
		*(tList<tElement*>*)value = ((tStructured3DBlockMeshGrid*)element)->faces();
		return true;
	} else {
		return iStructured3DGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DBlockMeshGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructured3DGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Int") {
		((tStructured3DBlockMeshGrid*)element)->setNi(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tStructured3DBlockMeshGrid*)element)->setNj(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tStructured3DBlockMeshGrid*)element)->setNk(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "DotList") {
		((tStructured3DBlockMeshGrid*)element)->setCorners(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "CurveList") {
		((tStructured3DBlockMeshGrid*)element)->setEdges(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "SurfaceList") {
		((tStructured3DBlockMeshGrid*)element)->setFaces(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DBlockMeshGrid::isReadOnly(int index)
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
		return iStructured3DGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured3DBlockMeshGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructured3DGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured3DBlockMeshGrid::inheritedTypes(void)
{
	QString type;
	iStructured3DBlockMeshGrid::getPropertyValue(0,"String",&type);
	return (iStructured3DGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured3DBlockMeshGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructured3DGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

