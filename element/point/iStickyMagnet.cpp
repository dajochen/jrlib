#include "iStickyMagnet.h"
#include "tStickyMagnet.h"

iStickyMagnet::iStickyMagnet(tElement *el):iMagnet(el)
{
}
//-----------------------------------------------------------------------------

iStickyMagnet::~iStickyMagnet()
{
}
//-----------------------------------------------------------------------------

tString iStickyMagnet::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "referenceDot";
	} else if (index == nInheritedProperties()+ 1){
		return "stickySurfaces";
	} else {
		return iMagnet::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iStickyMagnet::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Dot";
	} else if (index == nInheritedProperties()+1){
		return "Group";
	} else {
		return iMagnet::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iStickyMagnet::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iStickyMagnet::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Dot"|| propType=="Element")) {
		*(tElement**)value = ((tStickyMagnet*)element)->referenceDot();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Group"|| propType=="Element")) {
		*(tElement**)value = ((tStickyMagnet*)element)->stickyFaces();
		return true;
	} else {
		return iMagnet::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iStickyMagnet::setPropertyValue(int index, tString type, void* value)
{
	if (iMagnet::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Dot" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Dot")))) {
		((tStickyMagnet*)element)->setReferenceDot((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Group" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Group")))) {
		((tStickyMagnet*)element)->setStickyFaces((tElement*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iStickyMagnet::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else {
		return iMagnet::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iStickyMagnet::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iMagnet::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iStickyMagnet::inheritedTypes(void)
{
	QString type;
	iStickyMagnet::getPropertyValue(0,"String",&type);
	return (iMagnet::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iStickyMagnet::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iMagnet::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

