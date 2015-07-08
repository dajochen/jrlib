#include "iTrianglePatch.h"
#include "tTrianglePatch.h"

iTrianglePatch::iTrianglePatch(tElement *el):iPaintableElement(el)
{
}
//-----------------------------------------------------------------------------

iTrianglePatch::~iTrianglePatch()
{
}
//-----------------------------------------------------------------------------

tString iTrianglePatch::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "nTriangles";
	} else if (index == nInheritedProperties()+ 1){
		return "triangles";
	} else {
		return iPaintableElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iTrianglePatch::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "TriangleList";
	} else {
		return iPaintableElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iTrianglePatch::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iTrianglePatch::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tTrianglePatch*)element)->nTriangles();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "TriangleList") {
		*(tList<tElement*>*)value = ((tTrianglePatch*)element)->triangles();
		return true;
	} else {
		return iPaintableElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iTrianglePatch::setPropertyValue(int index, tString type, void* value)
{
	if (iPaintableElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "TriangleList") {
		((tTrianglePatch*)element)->setTriangles(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iTrianglePatch::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iPaintableElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iTrianglePatch::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iPaintableElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iTrianglePatch::inheritedTypes(void)
{
	QString type;
	iTrianglePatch::getPropertyValue(0,"String",&type);
	return (iPaintableElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iTrianglePatch::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPaintableElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------


QString iTrianglePatch::getActionName(int index)
{
	if (index == nInheritedActions()){
		return "alignOrientation";
	} else if (index == nInheritedActions()+ 1){
		return "randomizeOrientation";
	} else if (index == nInheritedActions()+ 2){
		return "test";
	} else {
		return iPaintableElement::getActionName(index);
	}
}
//-----------------------------------------------------------------------------

void iTrianglePatch::runAction(int index)
{
	if (index == nInheritedActions()){
		((tTrianglePatch*)element)->alignOrientation();
	} else if (index == nInheritedActions()+ 1){
		((tTrianglePatch*)element)->randomizeOrientation();
	} else if (index == nInheritedActions()+ 2){
		((tTrianglePatch*)element)->test();
	} else {
		iPaintableElement::runAction(index);
	}
}
//-----------------------------------------------------------------------------

