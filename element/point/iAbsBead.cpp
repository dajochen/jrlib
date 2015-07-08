#include "iAbsBead.h"
#include "tAbsBead.h"

iAbsBead::iAbsBead(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iAbsBead::~iAbsBead()
{
}
//-----------------------------------------------------------------------------

tString iAbsBead::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "position";
	} else if (index == nInheritedProperties()+ 1){
		return "referenceCurve";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iAbsBead::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Curve";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iAbsBead::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iAbsBead::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tAbsBead*)element)->position();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tAbsBead*)element)->reference();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iAbsBead::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tAbsBead*)element)->setPosition(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tAbsBead*)element)->setReference((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iAbsBead::isReadOnly(int index)
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

bool iAbsBead::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iAbsBead::inheritedTypes(void)
{
	QString type;
	iAbsBead::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iAbsBead::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

