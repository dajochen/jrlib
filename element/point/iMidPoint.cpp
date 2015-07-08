#include "iMidPoint.h"
#include "tMidPoint.h"

iMidPoint::iMidPoint(tElement *el):iDot(el)
{
}
//-----------------------------------------------------------------------------

iMidPoint::~iMidPoint()
{
}
//-----------------------------------------------------------------------------

tString iMidPoint::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "supportDots";
	} else {
		return iDot::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iMidPoint::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "DotList";
	} else {
		return iDot::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iMidPoint::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iMidPoint::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "DotList") {
		*(tList<tElement*>*)value = ((tMidPoint*)element)->dots();
		return true;
	} else {
		return iDot::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iMidPoint::setPropertyValue(int index, tString type, void* value)
{
	if (iDot::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "DotList") {
		((tMidPoint*)element)->setDots(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iMidPoint::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iDot::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iMidPoint::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iDot::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iMidPoint::inheritedTypes(void)
{
	QString type;
	iMidPoint::getPropertyValue(0,"String",&type);
	return (iDot::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iMidPoint::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iDot::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

