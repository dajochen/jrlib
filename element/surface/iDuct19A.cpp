#include "iDuct19A.h"
#include "tDuct19A.h"

iDuct19A::iDuct19A(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iDuct19A::~iDuct19A()
{
}
//-----------------------------------------------------------------------------

tString iDuct19A::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "referencePropeller";
	} else if (index == nInheritedProperties()+ 1){
		return "adaptToPropellerPitch";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iDuct19A::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "KaSeries";
	} else if (index == nInheritedProperties()+1){
		return "Bool";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iDuct19A::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iDuct19A::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "KaSeries"|| propType=="Element")) {
		*(tElement**)value = ((tDuct19A*)element)->propeller();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Bool") {
		*(bool*)value = ((tDuct19A*)element)->adaptToPropellerPitch();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iDuct19A::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "KaSeries" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("KaSeries")))) {
		((tDuct19A*)element)->setPropeller((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Bool") {
		((tDuct19A*)element)->setAdaptToPropellerPitch(*(bool*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iDuct19A::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iDuct19A::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iDuct19A::inheritedTypes(void)
{
	QString type;
	iDuct19A::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iDuct19A::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

