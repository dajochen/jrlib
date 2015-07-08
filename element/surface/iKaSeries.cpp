#include "iKaSeries.h"
#include "tKaSeries.h"

iKaSeries::iKaSeries(tElement *el):iPropSurface(el)
{
}
//-----------------------------------------------------------------------------

iKaSeries::~iKaSeries()
{
}
//-----------------------------------------------------------------------------

tString iKaSeries::getPropertyName(int index)
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

tString iKaSeries::getPropertyType(int index)
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

bool iKaSeries::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iKaSeries::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tKaSeries*)element)->PD();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tKaSeries*)element)->AEA0();
		return true;
	} else {
		return iPropSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iKaSeries::setPropertyValue(int index, tString type, void* value)
{
	if (iPropSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tKaSeries*)element)->setPD(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tKaSeries*)element)->setAEA0(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iKaSeries::isReadOnly(int index)
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

bool iKaSeries::isOptional(QString propName)
{
  if (QString(",pitch,chord,rake,skew,maxThickness,thickness,camber,").contains("," + propName + ",")) {
    return true;
  } else {
    return iPropSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iKaSeries::inheritedTypes(void)
{
	QString type;
	iKaSeries::getPropertyValue(0,"String",&type);
	return (iPropSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iKaSeries::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iPropSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

