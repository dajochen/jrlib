#include "iStructured2DInterpolGrid.h"
#include "tStructured2DInterpolGrid.h"

iStructured2DInterpolGrid::iStructured2DInterpolGrid(tElement *el):iStructured2DGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured2DInterpolGrid::~iStructured2DInterpolGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured2DInterpolGrid::getPropertyName(unsigned int index)
{
	if (index == nInheritedProperties()){
		return "ni";
	} else if (index == nInheritedProperties()+ 1){
		return "nj";
	} else if (index == nInheritedProperties()+ 2){
		return "meshIterations";
	} else {
		return iStructured2DGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured2DInterpolGrid::getPropertyType(unsigned int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Int";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else {
		return iStructured2DGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DInterpolGrid::getPropertyValue(unsigned int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured2DInterpolGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int"){
		*(int*)value = ((tStructured2DInterpolGrid*)element)->ni();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Int"){
		*(int*)value = ((tStructured2DInterpolGrid*)element)->nj();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int"){
		*(int*)value = ((tStructured2DInterpolGrid*)element)->meshIterations();
		return true;
	} else {
		return iStructured2DGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DInterpolGrid::setPropertyValue(unsigned int index, tString type, void* value)
{
	if (index == nInheritedProperties()+0 && type == "Int"){
		((tStructured2DInterpolGrid*)element)->setNi(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Int"){
		((tStructured2DInterpolGrid*)element)->setNj(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int"){
		((tStructured2DInterpolGrid*)element)->setMeshIterations(*(int*)value);
		return true;
	} else {
		return iStructured2DGrid::setPropertyValue(index,type,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DInterpolGrid::isReadOnly(unsigned int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iStructured2DGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DInterpolGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructured2DGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured2DInterpolGrid::inheritedTypes(void)
{
	QString type;
	iStructured2DInterpolGrid::getPropertyValue(0,"String",&type);
	return (iStructured2DGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured2DInterpolGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructured2DGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

