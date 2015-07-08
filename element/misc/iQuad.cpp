#include "iQuad.h"
#include "tQuad.h"

iQuad::iQuad(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iQuad::~iQuad()
{
}
//-----------------------------------------------------------------------------

tString iQuad::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "center";
	} else if (index == nInheritedProperties()+ 1){
		return "normalVector";
	} else if (index == nInheritedProperties()+ 2){
		return "area";
	} else if (index == nInheritedProperties()+ 3){
		return "size";
	} else if (index == nInheritedProperties()+ 4){
		return "diameter";
	} else if (index == nInheritedProperties()+ 5){
		return "corners";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iQuad::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Vector";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else if (index == nInheritedProperties()+4){
		return "Real";
	} else if (index == nInheritedProperties()+5){
		return "DotList";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iQuad::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iQuad::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tQuad*)element)->center();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Vector") {
		*(tVector*)value = ((tQuad*)element)->normalVector();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tQuad*)element)->area();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tQuad*)element)->size();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Real") {
		*(tReal*)value = ((tQuad*)element)->diameter();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tQuad*)element)->corners();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iQuad::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2){
		return false;
	} else if(index == nInheritedProperties()+3){
		return false;
	} else if(index == nInheritedProperties()+4){
		return false;
	} else if(index == nInheritedProperties()+5 && type == "DotList") {
		((tQuad*)element)->setCorners(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iQuad::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return true;
	} else if (index == nInheritedProperties()+3){
		return true;
	} else if (index == nInheritedProperties()+4){
		return true;
	} else if (index == nInheritedProperties()+5){
		return false;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iQuad::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iQuad::inheritedTypes(void)
{
	QString type;
	iQuad::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iQuad::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

