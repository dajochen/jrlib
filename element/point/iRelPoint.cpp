#include "iRelPoint.h"
#include "tRelPoint.h"

iRelPoint::iRelPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iRelPoint::~iRelPoint()
{
}
//-----------------------------------------------------------------------------

tString iRelPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "offset";
	} else if (index == nInheritedProperties()+ 1){
		return "reference";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRelPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Vector";
	} else if (index == nInheritedProperties()+1){
		return "Dot";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRelPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRelPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Vector") {
		*(tVector*)value = ((tRelPoint*)element)->offset();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tRelPoint*)element)->reference();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRelPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Vector") {
		((tRelPoint*)element)->setOffset(*(tVector*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tRelPoint*)element)->setReference((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRelPoint::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRelPoint::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRelPoint::inheritedTypes(void)
{
	QString type;
	iRelPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRelPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

