#include "iStructured2DSurfaceGrid.h"
#include "tStructured2DSurfaceGrid.h"

iStructured2DSurfaceGrid::iStructured2DSurfaceGrid(tElement *el):iStructured2DGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured2DSurfaceGrid::~iStructured2DSurfaceGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured2DSurfaceGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "ni";
	} else if (index == nInheritedProperties()+ 1){
		return "nj";
	} else if (index == nInheritedProperties()+ 2){
		return "base";
	} else if (index == nInheritedProperties()+ 3){
		return "uRefinement";
	} else if (index == nInheritedProperties()+ 4){
		return "vRefinement";
	} else if (index == nInheritedProperties()+ 5){
		return "edges";
	} else if (index == nInheritedProperties()+ 6){
		return "corners";
	} else if (index == nInheritedProperties()+ 7){
		return "neighbours";
	} else if (index == nInheritedProperties()+ 8){
		return "neighbourEdges";
	} else {
		return iStructured2DGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured2DSurfaceGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Surface";
	} else if (index == nInheritedProperties()+3){
		return "String";
	} else if (index == nInheritedProperties()+4){
		return "String";
	} else if (index == nInheritedProperties()+5){
		return "CurveList";
	} else if (index == nInheritedProperties()+6){
		return "DotList";
	} else if (index == nInheritedProperties()+7){
		return "Structured2DGridList";
	} else if (index == nInheritedProperties()+8){
		return "IntList";
	} else {
		return iStructured2DGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSurfaceGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured2DSurfaceGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tStructured2DSurfaceGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tStructured2DSurfaceGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tStructured2DSurfaceGrid*)element)->base();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "String") {
		*(tString*)value = ((tStructured2DSurfaceGrid*)element)->uRefinement();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "String") {
		*(tString*)value = ((tStructured2DSurfaceGrid*)element)->vRefinement();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tStructured2DSurfaceGrid*)element)->edges();
		return true;
	} else if (index == nInheritedProperties()+6 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tStructured2DSurfaceGrid*)element)->corners();
		return true;
	} else if (index == nInheritedProperties()+7 && propType == "Structured2DGridList") {
		*(tList<tElement*>*)value = ((tStructured2DSurfaceGrid*)element)->neighbours();
		return true;
	} else if (index == nInheritedProperties()+8 && propType == "IntList") {
		*(tList<int>*)value = ((tStructured2DSurfaceGrid*)element)->neighbourEdges();
		return true;
	} else {
		return iStructured2DGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSurfaceGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructured2DGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Int") {
		((tStructured2DSurfaceGrid*)element)->setNi(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tStructured2DSurfaceGrid*)element)->setNj(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tStructured2DSurfaceGrid*)element)->setBase((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "String") {
		((tStructured2DSurfaceGrid*)element)->setURefinement(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "String") {
		((tStructured2DSurfaceGrid*)element)->setVRefinement(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "CurveList") {
		((tStructured2DSurfaceGrid*)element)->setEdges(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+6 && type == "DotList") {
		((tStructured2DSurfaceGrid*)element)->setCorners(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+7 && type == "Structured2DGridList") {
		((tStructured2DSurfaceGrid*)element)->setNeighbours(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+8 && type == "IntList") {
		((tStructured2DSurfaceGrid*)element)->setNeighbourEdges(*(tList<int>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSurfaceGrid::isReadOnly(int index)
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
	} else if (index == nInheritedProperties()+6){
		return false;
	} else if (index == nInheritedProperties()+7){
		return false;
	} else if (index == nInheritedProperties()+8){
		return false;
	} else {
		return iStructured2DGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSurfaceGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructured2DGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured2DSurfaceGrid::inheritedTypes(void)
{
	QString type;
	iStructured2DSurfaceGrid::getPropertyValue(0,"String",&type);
	return (iStructured2DGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured2DSurfaceGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructured2DGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

