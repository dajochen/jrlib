#include "iOffsetPoint.h"
#include "tOffsetPoint.h"

iOffsetPoint::iOffsetPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iOffsetPoint::~iOffsetPoint()
{
}
//-----------------------------------------------------------------------------

tString iOffsetPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "offset";
	} else if (index == nInheritedProperties()+ 1){
		return "reference";
	} else if (index == nInheritedProperties()+ 2){
		return "u";
	} else if (index == nInheritedProperties()+ 3){
		return "v";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iOffsetPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Surface";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iOffsetPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tOffsetPoint*)element)->offset();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tOffsetPoint*)element)->reference();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tOffsetPoint*)element)->u();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tOffsetPoint*)element)->v();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tOffsetPoint*)element)->setOffset(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tOffsetPoint*)element)->setReference((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tOffsetPoint*)element)->setU(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Real") {
		((tOffsetPoint*)element)->setV(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iOffsetPoint::isReadOnly(int index)
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

bool iOffsetPoint::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iOffsetPoint::inheritedTypes(void)
{
	QString type;
	iOffsetPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iOffsetPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

