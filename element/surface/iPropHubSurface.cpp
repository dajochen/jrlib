#include "iPropHubSurface.h"
#include "tPropHubSurface.h"

iPropHubSurface::iPropHubSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iPropHubSurface::~iPropHubSurface()
{
}
//-----------------------------------------------------------------------------

tString iPropHubSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "propellerSurface";
	} else if (index == nInheritedProperties()+ 1){
		return "hubContour";
	} else if (index == nInheritedProperties()+ 2){
		return "leadingPartition";
	} else if (index == nInheritedProperties()+ 3){
		return "trailingPartition";
	} else if (index == nInheritedProperties()+ 4){
		return "leadingAlpha";
	} else if (index == nInheritedProperties()+ 5){
		return "trailingAlpha";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPropHubSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "PropSurface";
	} else if (index == nInheritedProperties()+1){
		return "Curve";
	} else if (index == nInheritedProperties()+2){
		return "Real";
	} else if (index == nInheritedProperties()+3){
		return "Real";
	} else if (index == nInheritedProperties()+4){
		return "Real";
	} else if (index == nInheritedProperties()+5){
		return "Real";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPropHubSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPropHubSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && (propType == "PropSurface"|| propType=="Element")) {
		*(tElement**)value = ((tPropHubSurface*)element)->propellerSurface();
		return true;
	} else if (index == nInheritedProperties()+1 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropHubSurface*)element)->hubContour();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Real") {
		*(tReal*)value = ((tPropHubSurface*)element)->leadingPartition();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Real") {
		*(tReal*)value = ((tPropHubSurface*)element)->trailingPartition();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Real") {
		*(tReal*)value = ((tPropHubSurface*)element)->leadingAlpha();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "Real") {
		*(tReal*)value = ((tPropHubSurface*)element)->trailingAlpha();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPropHubSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && ( type == "PropSurface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("PropSurface")))) {
		((tPropHubSurface*)element)->setPropellerSurface((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropHubSurface*)element)->setHubContour((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Real") {
		((tPropHubSurface*)element)->setLeadingPartition(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Real") {
		((tPropHubSurface*)element)->setTrailingPartition(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "Real") {
		((tPropHubSurface*)element)->setLeadingAlpha(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "Real") {
		((tPropHubSurface*)element)->setTrailingAlpha(*(tReal*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPropHubSurface::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return false;
	} else if (index == nInheritedProperties()+1){
		return false;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else if (index == nInheritedProperties()+4){
		return false;
	} else if (index == nInheritedProperties()+5){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPropHubSurface::isOptional(QString propName)
{
  if (QString(",").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPropHubSurface::inheritedTypes(void)
{
	QString type;
	iPropHubSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPropHubSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

