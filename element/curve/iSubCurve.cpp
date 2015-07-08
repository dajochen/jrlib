#include "iSubCurve.h"
#include "tSubCurve.h"

iSubCurve::iSubCurve(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iSubCurve::~iSubCurve()
{
}
//-----------------------------------------------------------------------------

tString iSubCurve::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "start";
	} else if (index == nInheritedProperties()+ 1){
		return "end";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iSubCurve::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "AbsBead";
	} else if (index == nInheritedProperties()+1){
		return "AbsBead";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iSubCurve::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iSubCurve::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "AbsBead"|| propType=="Element")) {
		*(tElement**)value = ((tSubCurve*)element)->start();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "AbsBead"|| propType=="Element")) {
		*(tElement**)value = ((tSubCurve*)element)->end();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iSubCurve::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "AbsBead" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("AbsBead")))) {
		((tSubCurve*)element)->setStart((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "AbsBead" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("AbsBead")))) {
		((tSubCurve*)element)->setEnd((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iSubCurve::isReadOnly(int index)
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

bool iSubCurve::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iSubCurve::inheritedTypes(void)
{
	QString type;
	iSubCurve::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iSubCurve::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

