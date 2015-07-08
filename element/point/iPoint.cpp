#include "iPoint.h"
#include "tPoint.h"

iPoint::iPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iPoint::~iPoint()
{
}
//-----------------------------------------------------------------------------

tString iPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "location";
	} else if (index == nInheritedProperties()+ 1){
		return "x";
	} else if (index == nInheritedProperties()+ 2){
		return "y";
	} else if (index == nInheritedProperties()+ 3){
		return "z";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tPoint*)element)->vector();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tPoint*)element)->x();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tPoint*)element)->y();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tPoint*)element)->z();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Vector") {
		((tPoint*)element)->setVector(*(tVector*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tPoint*)element)->setX(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tPoint*)element)->setY(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Real") {
		((tPoint*)element)->setZ(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPoint::isReadOnly(int index)
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
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPoint::isOptional(QString propName)
{
  if (QString(",x,y,z,").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPoint::inheritedTypes(void)
{
	QString type;
	iPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

