#include "iStructured2DSubGrid.h"
#include "tStructured2DSubGrid.h"

iStructured2DSubGrid::iStructured2DSubGrid(tElement *el):iStructured2DGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured2DSubGrid::~iStructured2DSubGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured2DSubGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "parentGrid";
	} else if (index == nInheritedProperties()+ 1){
		return "ni";
	} else if (index == nInheritedProperties()+ 2){
		return "nj";
	} else if (index == nInheritedProperties()+ 3){
		return "iOffset";
	} else if (index == nInheritedProperties()+ 4){
		return "jOffset";
	} else if (index == nInheritedProperties()+ 5){
		return "niSkip";
	} else if (index == nInheritedProperties()+ 6){
		return "njSkip";
	} else if (index == nInheritedProperties()+ 7){
		return "dirOffsetOn3DGrid";
	} else if (index == nInheritedProperties()+ 8){
		return "dirOn3DGrid";
	} else {
		return iStructured2DGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured2DSubGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "StructuredAbstractGrid";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "Int";
	} else if (index == nInheritedProperties()+4){
		return "Int";
	} else if (index == nInheritedProperties()+5){
		return "Int";
	} else if (index == nInheritedProperties()+6){
		return "Int";
	} else if (index == nInheritedProperties()+7){
		return "Int";
	} else if (index == nInheritedProperties()+8){
		return "Int";
	} else {
		return iStructured2DGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSubGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured2DSubGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "StructuredAbstractGrid"|| propType=="Element")) {
		*(tElement**)value = ((tStructured2DSubGrid*)element)->parentGrid();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->offsetI();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->offsetJ();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->niSkip();
		return true;
	} else if (index == nInheritedProperties()+6 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->njSkip();
		return true;
	} else if (index == nInheritedProperties()+7 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->dirOffsetOn3DGrid();
		return true;
	} else if (index == nInheritedProperties()+8 && propType == "Int") {
		*(int*)value = ((tStructured2DSubGrid*)element)->dirOn3DGrid();
		return true;
	} else {
		return iStructured2DGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSubGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructured2DGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "StructuredAbstractGrid" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("StructuredAbstractGrid")))) {
		((tStructured2DSubGrid*)element)->setParentGrid((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int") {
		((tStructured2DSubGrid*)element)->setNi(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tStructured2DSubGrid*)element)->setNj(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Int") {
		((tStructured2DSubGrid*)element)->setOffsetI(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "Int") {
		((tStructured2DSubGrid*)element)->setOffsetJ(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "Int") {
		((tStructured2DSubGrid*)element)->setNiSkip(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+6 && type == "Int") {
		((tStructured2DSubGrid*)element)->setNjSkip(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+7 && type == "Int") {
		((tStructured2DSubGrid*)element)->setDirOffsetOn3DGrid(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+8 && type == "Int") {
		((tStructured2DSubGrid*)element)->setDirOn3DGrid(*(int*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DSubGrid::isReadOnly(int index)
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

bool iStructured2DSubGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructured2DGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured2DSubGrid::inheritedTypes(void)
{
	QString type;
	iStructured2DSubGrid::getPropertyValue(0,"String",&type);
	return (iStructured2DGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured2DSubGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructured2DGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

