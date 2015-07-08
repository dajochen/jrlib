#include "iSubSurface.h"
#include "tSubSurface.h"

iSubSurface::iSubSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iSubSurface::~iSubSurface()
{
}
//-----------------------------------------------------------------------------

tString iSubSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "reference";
	} else if (index == nInheritedProperties()+ 1){
		return "boundingSnakes";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iSubSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Surface";
	} else if (index == nInheritedProperties()+1){
		return "SnakeList";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iSubSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iSubSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tSubSurface*)element)->reference();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "SnakeList") {
		*(tList<tElement*>*)value = ((tSubSurface*)element)->boundingSnakes();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iSubSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1 && type == "SnakeList") {
		((tSubSurface*)element)->setBoundingSnakes(*(tList<tElement*>*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iSubSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iSubSurface::isOptional(QString propName)
{
  if (QString(",reference,").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iSubSurface::inheritedTypes(void)
{
	QString type;
	iSubSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iSubSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

