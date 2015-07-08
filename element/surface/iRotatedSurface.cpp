#include "iRotatedSurface.h"
#include "tRotatedSurface.h"

iRotatedSurface::iRotatedSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iRotatedSurface::~iRotatedSurface()
{
}
//-----------------------------------------------------------------------------

tString iRotatedSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "axis";
	} else if (index == nInheritedProperties()+ 1){
		return "referenceSurface";
	} else if (index == nInheritedProperties()+ 2){
		return "angle";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iRotatedSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Line";
	} else if (index == nInheritedProperties()+1){
		return "Surface";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iRotatedSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "Line"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedSurface*)element)->axis();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tRotatedSurface*)element)->refSurface();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tRotatedSurface*)element)->angle();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "Line" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Line")))) {
		((tRotatedSurface*)element)->setAxis((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tRotatedSurface*)element)->setRefSurface((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tRotatedSurface*)element)->setAngle(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iRotatedSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iRotatedSurface::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iRotatedSurface::inheritedTypes(void)
{
	QString type;
	iRotatedSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iRotatedSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

