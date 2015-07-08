#include "iAbstractPolygon.h"
#include "tAbstractPolygon.h"

iAbstractPolygon::iAbstractPolygon(tElement *el):iPaintableElement(el)
{
}
//-----------------------------------------------------------------------------

iAbstractPolygon::~iAbstractPolygon()
{
}
//-----------------------------------------------------------------------------

tString iAbstractPolygon::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "normal";
	} else if (index == nInheritedProperties()+ 1){
		return "area";
	} else if (index == nInheritedProperties()+ 2){
		return "nVertices";
	} else if (index == nInheritedProperties()+ 3){
		return "vertices";
	} else {
		return iPaintableElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iAbstractPolygon::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "DotList";
	} else {
		return iPaintableElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractPolygon::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iAbstractPolygon::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tAbstractPolygon*)element)->normal();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tAbstractPolygon*)element)->area();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tAbstractPolygon*)element)->nVertices();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tAbstractPolygon*)element)->vertices();
		return true;
	} else {
		return iPaintableElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractPolygon::setPropertyValue(int index, tString type, void* value)
{
	if (iPaintableElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2){
		return false;
	} else if(index == nInheritedProperties()+3 && type == "DotList") {
		((tAbstractPolygon*)element)->setVertices(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iAbstractPolygon::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return true;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iPaintableElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbstractPolygon::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iPaintableElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iAbstractPolygon::inheritedTypes(void)
{
	QString type;
	iAbstractPolygon::getPropertyValue(0,"String",&type);
	return (iPaintableElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iAbstractPolygon::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPaintableElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

