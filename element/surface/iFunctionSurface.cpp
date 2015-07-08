#include "iFunctionSurface.h"
#include "tFunctionSurface.h"

iFunctionSurface::iFunctionSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iFunctionSurface::~iFunctionSurface()
{
}
//-----------------------------------------------------------------------------

tString iFunctionSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "addReference";
	} else if (index == nInheritedProperties()+ 1){
		return "availableVariables";
	} else if (index == nInheritedProperties()+ 2){
		return "addFunction";
	} else if (index == nInheritedProperties()+ 3){
		return "clear";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iFunctionSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Element";
	} else if (index == nInheritedProperties()+1){
		return "String";
	} else if (index == nInheritedProperties()+2){
		return "String";
	} else if (index == nInheritedProperties()+3){
		return "Bool";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iFunctionSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Element"|| propType=="Element")) {
		*(tElement**)value = ((tFunctionSurface*)element)->lastAddedReference();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "String") {
		*(tString*)value = ((tFunctionSurface*)element)->variableStringList();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "String") {
		*(tString*)value = ((tFunctionSurface*)element)->functionsStringList();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Bool") {
		*(bool*)value = ((tFunctionSurface*)element)->isCleared();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Element" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Element")))) {
		((tFunctionSurface*)element)->addReference((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2 && type == "String") {
		((tFunctionSurface*)element)->addFunction(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Bool") {
		((tFunctionSurface*)element)->clear(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iFunctionSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iFunctionSurface::isOptional(QString propName)
{
  if (QString(",addReference,addFunction,clear,").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iFunctionSurface::inheritedTypes(void)
{
	QString type;
	iFunctionSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iFunctionSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

