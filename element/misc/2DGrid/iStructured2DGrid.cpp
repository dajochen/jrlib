#include "iStructured2DGrid.h"
#include "tStructured2DGrid.h"

iStructured2DGrid::iStructured2DGrid(tElement *el):iStructuredAbstractGrid(el)
{
}
//-----------------------------------------------------------------------------

iStructured2DGrid::~iStructured2DGrid()
{
}
//-----------------------------------------------------------------------------

tString iStructured2DGrid::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "orientation";
	} else {
		return iStructuredAbstractGrid::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStructured2DGrid::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Bool";
	} else {
		return iStructuredAbstractGrid::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DGrid::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStructured2DGrid::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Bool") {
		*(bool*)value = ((tStructured2DGrid*)element)->orientation();
		return true;
	} else {
		return iStructuredAbstractGrid::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DGrid::setPropertyValue(int index, tString type, void* value)
{
	if (iStructuredAbstractGrid::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Bool") {
		((tStructured2DGrid*)element)->setOrientation(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DGrid::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iStructuredAbstractGrid::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStructured2DGrid::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iStructuredAbstractGrid::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStructured2DGrid::inheritedTypes(void)
{
	QString type;
	iStructured2DGrid::getPropertyValue(0,"String",&type);
	return (iStructuredAbstractGrid::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStructured2DGrid::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iStructuredAbstractGrid::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

