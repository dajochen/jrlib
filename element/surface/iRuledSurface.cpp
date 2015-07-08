#include "iRuledSurface.h"
#include "tRuledSurface.h"

iRuledSurface::iRuledSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iRuledSurface::~iRuledSurface()
{
}
//-----------------------------------------------------------------------------

tString iRuledSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "boundingCurves";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRuledSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "CurveList";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRuledSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRuledSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "CurveList") {
		*(tList<tElement*>*)value = ((tRuledSurface*)element)->curves();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRuledSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "CurveList") {
		((tRuledSurface*)element)->setCurves(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRuledSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRuledSurface::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRuledSurface::inheritedTypes(void)
{
	QString type;
	iRuledSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRuledSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

