#include "iOffsetCurve2.h"
#include "tOffsetCurve2.h"

iOffsetCurve2::iOffsetCurve2(tElement *el):iCurve(el)
{
}
//-----------------------------------------------------------------------------

iOffsetCurve2::~iOffsetCurve2()
{
}
//-----------------------------------------------------------------------------

tString iOffsetCurve2::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "referenceCurve";
	} else if (index == nInheritedProperties()+ 1){
		return "offset";
	} else {
		return iCurve::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iOffsetCurve2::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Curve";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else {
		return iCurve::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve2::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iOffsetCurve2::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tOffsetCurve2*)element)->referenceCurve();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tOffsetCurve2*)element)->offset();
		return true;
	} else {
		return iCurve::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve2::setPropertyValue(int index, tString type, void* value)
{
	if (iCurve::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tOffsetCurve2*)element)->setReferenceCurve((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tOffsetCurve2*)element)->setOffset(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iOffsetCurve2::isReadOnly(int index)
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

bool iOffsetCurve2::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iCurve::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iOffsetCurve2::inheritedTypes(void)
{
	QString type;
	iOffsetCurve2::getPropertyValue(0,"String",&type);
	return (iCurve::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iOffsetCurve2::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iCurve::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

