#include "iAbsMagnet.h"
#include "tAbsMagnet.h"

iAbsMagnet::iAbsMagnet(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iAbsMagnet::~iAbsMagnet()
{
}
//-----------------------------------------------------------------------------

tString iAbsMagnet::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "uPosition";
	} else if (index == nInheritedProperties()+ 1){
		return "vPosition";
	} else if (index == nInheritedProperties()+ 2){
		return "referenceSurface";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iAbsMagnet::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Surface";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbsMagnet::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iAbsMagnet::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tAbsMagnet*)element)->uPosition();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tAbsMagnet*)element)->vPosition();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tAbsMagnet*)element)->reference();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iAbsMagnet::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tAbsMagnet*)element)->setUPosition(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tAbsMagnet*)element)->setVPosition(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tAbsMagnet*)element)->setReference((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iAbsMagnet::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbsMagnet::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iAbsMagnet::inheritedTypes(void)
{
	QString type;
	iAbsMagnet::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iAbsMagnet::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

