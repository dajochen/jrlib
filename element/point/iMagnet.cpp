#include "iMagnet.h"
#include "tMagnet.h"

iMagnet::iMagnet(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iMagnet::~iMagnet()
{
}
//-----------------------------------------------------------------------------

tString iMagnet::getPropertyName(int index)
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

tString iMagnet::getPropertyType(int index)
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

bool iMagnet::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iMagnet::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tMagnet*)element)->uPosition();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tMagnet*)element)->vPosition();
		return true;
	} else if (index == nInheritedProperties()+2 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tMagnet*)element)->reference();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iMagnet::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2){
		return false;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iMagnet::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return true;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iMagnet::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iMagnet::inheritedTypes(void)
{
	QString type;
	iMagnet::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iMagnet::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

