#include "iRefinedQuad.h"
#include "tRefinedQuad.h"

iRefinedQuad::iRefinedQuad(tElement *el):iQuad(el)
{
}
//-----------------------------------------------------------------------------

iRefinedQuad::~iRefinedQuad()
{
}
//-----------------------------------------------------------------------------

tString iRefinedQuad::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "refinement0";
	} else if (index == nInheritedProperties()+ 1){
		return "refinement1";
	} else if (index == nInheritedProperties()+ 2){
		return "refinement2";
	} else if (index == nInheritedProperties()+ 3){
		return "refinement3";
	} else {
		return iQuad::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRefinedQuad::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "DotList";
	} else if (index == nInheritedProperties()+1){
		return "DotList";
	} else if (index == nInheritedProperties()+2){
		return "DotList";
	} else if (index == nInheritedProperties()+3){
		return "DotList";
	} else {
		return iQuad::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRefinedQuad::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRefinedQuad::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tRefinedQuad*)element)->dotList0();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tRefinedQuad*)element)->dotList1();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tRefinedQuad*)element)->dotList2();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tRefinedQuad*)element)->dotList3();
		return true;
	} else {
		return iQuad::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRefinedQuad::setPropertyValue(int index, tString type, void* value)
{
	if (iQuad::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "DotList") {
		((tRefinedQuad*)element)->setDotList0(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "DotList") {
		((tRefinedQuad*)element)->setDotList1(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "DotList") {
		((tRefinedQuad*)element)->setDotList2(*(tList<tElement*>*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "DotList") {
		((tRefinedQuad*)element)->setDotList3(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRefinedQuad::isReadOnly(int index)
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
		return iQuad::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRefinedQuad::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iQuad::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRefinedQuad::inheritedTypes(void)
{
	QString type;
	iRefinedQuad::getPropertyValue(0,"String",&type);
	return (iQuad::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRefinedQuad::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iQuad::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

