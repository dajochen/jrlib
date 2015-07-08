#include "iLine.h"
#include "tLine.h"

iLine::iLine(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iLine::~iLine()
{
}
//-----------------------------------------------------------------------------

tString iLine::getPropertyName(int index)
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

tString iLine::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Dot";
	} else if (index == nInheritedProperties()+1){
		return "Dot";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iLine::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iLine::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tLine*)element)->start();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tLine*)element)->end();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iLine::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tLine*)element)->setStart((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tLine*)element)->setEnd((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iLine::isReadOnly(int index)
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

bool iLine::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iLine::inheritedTypes(void)
{
	QString type;
	iLine::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iLine::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

