#include "iOffsetCurve.h"
#include "tOffsetCurve.h"

iOffsetCurve::iOffsetCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iOffsetCurve::~iOffsetCurve()
{
}
//-----------------------------------------------------------------------------

tString iOffsetCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "offset";
	} else if (index == nInheritedProperties()+ 1){
		return "referenceSnake";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iOffsetCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Snake";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iOffsetCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tOffsetCurve*)element)->offset();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Snake"|| propType=="Element")) {
		*(tElement**)value = ((tOffsetCurve*)element)->referenceSnake();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tOffsetCurve*)element)->setOffset(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Snake" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Snake")))) {
		((tOffsetCurve*)element)->setReferenceSnake((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iCurve::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iOffsetCurve::inheritedTypes(void)
{
	QString type;
	iOffsetCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iOffsetCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

