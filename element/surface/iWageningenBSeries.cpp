#include "iWageningenBSeries.h"
#include "tWageningenBSeries.h"

iWageningenBSeries::iWageningenBSeries(tElement *el):iPropSurface(el)
{
}
//-----------------------------------------------------------------------------

iWageningenBSeries::~iWageningenBSeries()
{
}
//-----------------------------------------------------------------------------

tString iWageningenBSeries::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "PD";
	} else if (index == nInheritedProperties()+ 1){
		return "AEA0";
	} else {
		return iPropSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iWageningenBSeries::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else {
		return iPropSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iWageningenBSeries::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iWageningenBSeries::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tWageningenBSeries*)element)->PD();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tWageningenBSeries*)element)->AEA0();
		return true;
	} else {
		return iPropSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iWageningenBSeries::setPropertyValue(int index, tString type, void* value)
{
	if (iPropSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tWageningenBSeries*)element)->setPD(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tWageningenBSeries*)element)->setAEA0(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iWageningenBSeries::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iPropSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iWageningenBSeries::isOptional(QString propName)
{
  if (QString(",pitch,chord,rake,skew,maxThickness,thickness,camber,").contains("," + propName + ",")) {
    return true;
  } else {
    return iPropSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iWageningenBSeries::inheritedTypes(void)
{
	QString type;
	iWageningenBSeries::getPropertyValue(0,"String",&type);
	return (iPropSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iWageningenBSeries::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPropSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

