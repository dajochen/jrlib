#include "iDrapedPatch.h"
#include "tDrapedPatch.h"

iDrapedPatch::iDrapedPatch(tElement *el):iPaintableElement(el)
{
}
//-----------------------------------------------------------------------------

iDrapedPatch::~iDrapedPatch()
{
}
//-----------------------------------------------------------------------------

tString iDrapedPatch::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "patch";
	} else if (index == nInheritedProperties()+ 1){
		return "meshSize";
	} else if (index == nInheritedProperties()+ 2){
		return "initialPoint";
	} else if (index == nInheritedProperties()+ 3){
		return "initialPointProjectionDir";
	} else if (index == nInheritedProperties()+ 4){
		return "initialFiberDir";
	} else {
		return iPaintableElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iDrapedPatch::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "TrianglePatch";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Dot";
	} else if (index == nInheritedProperties()+3){
		return "Line";
	} else if (index == nInheritedProperties()+4){
		return "Line";
	} else {
		return iPaintableElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iDrapedPatch::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iDrapedPatch::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "TrianglePatch"|| propType=="Element")) {
		*(tElement**)value = ((tDrapedPatch*)element)->patch();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tDrapedPatch*)element)->meshSize();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tDrapedPatch*)element)->initialPoint();
		return true;
	} else if (index == nInheritedProperties()+3 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tDrapedPatch*)element)->initialPointProjectionDir();
		return true;
	} else if (index == nInheritedProperties()+4 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tDrapedPatch*)element)->initialFiberDir();
		return true;
	} else {
		return iPaintableElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iDrapedPatch::setPropertyValue(int index, tString type, void* value)
{
	if (iPaintableElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "TrianglePatch" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("TrianglePatch")))) {
		((tDrapedPatch*)element)->setPatch((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tDrapedPatch*)element)->setMeshSize(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tDrapedPatch*)element)->setInitialPoint((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tDrapedPatch*)element)->setInitialPointProjectionDir((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tDrapedPatch*)element)->setInitialFiberDir((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iDrapedPatch::isReadOnly(int index)
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
	} else {
		return iPaintableElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iDrapedPatch::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iPaintableElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iDrapedPatch::inheritedTypes(void)
{
	QString type;
	iDrapedPatch::getPropertyValue(0,"String",&type);
	return (iPaintableElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iDrapedPatch::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPaintableElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------


QString iDrapedPatch::getActionName(int index)
{
	if (index == nInheritedActions()){
		return "runDrapingSimulation";
	} else {
		return iPaintableElement::getActionName(index);
	}
}
//-----------------------------------------------------------------------------

void iDrapedPatch::runAction(int index)
{
	if (index == nInheritedActions()){
		((tDrapedPatch*)element)->runDrapingSimulation();
	} else {
		iPaintableElement::runAction(index);
	}
}
//-----------------------------------------------------------------------------

