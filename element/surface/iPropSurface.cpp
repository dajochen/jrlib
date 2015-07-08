#include "iPropSurface.h"
#include "tPropSurface.h"

iPropSurface::iPropSurface(tElement *el):iSurface(el)
{
}
//-----------------------------------------------------------------------------

iPropSurface::~iPropSurface()
{
}
//-----------------------------------------------------------------------------

tString iPropSurface::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "diameter";
	} else if (index == nInheritedProperties()+ 1){
		return "scale";
	} else if (index == nInheritedProperties()+ 2){
		return "bladeNumber";
	} else if (index == nInheritedProperties()+ 3){
		return "rotationDirection";
	} else if (index == nInheritedProperties()+ 4){
		return "roundedTipChord";
	} else if (index == nInheritedProperties()+ 5){
		return "autoRoundTrailingEdge";
	} else if (index == nInheritedProperties()+ 6){
		return "autoRoundTipThickness";
	} else if (index == nInheritedProperties()+ 7){
		return "radialRefinement";
	} else if (index == nInheritedProperties()+ 8){
		return "peripherRefinement";
	} else if (index == nInheritedProperties()+ 9){
		return "pitch";
	} else if (index == nInheritedProperties()+ 10){
		return "chord";
	} else if (index == nInheritedProperties()+ 11){
		return "rake";
	} else if (index == nInheritedProperties()+ 12){
		return "skew";
	} else if (index == nInheritedProperties()+ 13){
		return "maxThickness";
	} else if (index == nInheritedProperties()+ 14){
		return "thickness";
	} else if (index == nInheritedProperties()+ 15){
		return "camber";
	} else if (index == nInheritedProperties()+ 16){
		return "isInReadingMode";
	} else if (index == nInheritedProperties()+ 17){
		return "propellerFileName";
	} else {
		return iSurface::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iPropSurface::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Real";
	} else if (index == nInheritedProperties()+1){
		return "Real";
	} else if (index == nInheritedProperties()+2){
		return "Int";
	} else if (index == nInheritedProperties()+3){
		return "Bool";
	} else if (index == nInheritedProperties()+4){
		return "Bool";
	} else if (index == nInheritedProperties()+5){
		return "Bool";
	} else if (index == nInheritedProperties()+6){
		return "Bool";
	} else if (index == nInheritedProperties()+7){
		return "String";
	} else if (index == nInheritedProperties()+8){
		return "String";
	} else if (index == nInheritedProperties()+9){
		return "Curve";
	} else if (index == nInheritedProperties()+10){
		return "Curve";
	} else if (index == nInheritedProperties()+11){
		return "Curve";
	} else if (index == nInheritedProperties()+12){
		return "Curve";
	} else if (index == nInheritedProperties()+13){
		return "Curve";
	} else if (index == nInheritedProperties()+14){
		return "Surface";
	} else if (index == nInheritedProperties()+15){
		return "Surface";
	} else if (index == nInheritedProperties()+16){
		return "Bool";
	} else if (index == nInheritedProperties()+17){
		return "String";
	} else {
		return iSurface::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iPropSurface::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iPropSurface::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Real") {
		*(tReal*)value = ((tPropSurface*)element)->diameter();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Real") {
		*(tReal*)value = ((tPropSurface*)element)->scale();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "Int") {
		*(int*)value = ((tPropSurface*)element)->bladeNumber();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "Bool") {
		*(bool*)value = ((tPropSurface*)element)->rotationDirection();
		return true;
	} else if (index == nInheritedProperties()+4 && propType == "Bool") {
		*(bool*)value = ((tPropSurface*)element)->roundedTip();
		return true;
	} else if (index == nInheritedProperties()+5 && propType == "Bool") {
		*(bool*)value = ((tPropSurface*)element)->autoRoundTE();
		return true;
	} else if (index == nInheritedProperties()+6 && propType == "Bool") {
		*(bool*)value = ((tPropSurface*)element)->autoRoundTip();
		return true;
	} else if (index == nInheritedProperties()+7 && propType == "String") {
		*(tString*)value = ((tPropSurface*)element)->radialRefinement();
		return true;
	} else if (index == nInheritedProperties()+8 && propType == "String") {
		*(tString*)value = ((tPropSurface*)element)->peripherRefinement();
		return true;
	} else if (index == nInheritedProperties()+9 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->pitch();
		return true;
	} else if (index == nInheritedProperties()+10 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->chord();
		return true;
	} else if (index == nInheritedProperties()+11 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->rake();
		return true;
	} else if (index == nInheritedProperties()+12 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->skew();
		return true;
	} else if (index == nInheritedProperties()+13 && (propType == "Curve"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->maxThick();
		return true;
	} else if (index == nInheritedProperties()+14 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->thickness();
		return true;
	} else if (index == nInheritedProperties()+15 && (propType == "Surface"|| propType=="Element")) {
		*(tElement**)value = ((tPropSurface*)element)->camber();
		return true;
	} else if (index == nInheritedProperties()+16 && propType == "Bool") {
		*(bool*)value = ((tPropSurface*)element)->isInReadingMode();
		return true;
	} else if (index == nInheritedProperties()+17 && propType == "String") {
		*(tString*)value = ((tPropSurface*)element)->propellerFileName();
		return true;
	} else {
		return iSurface::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iPropSurface::setPropertyValue(int index, tString type, void* value)
{
	if (iSurface::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0 && type == "Real") {
		((tPropSurface*)element)->setDiameter(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+1 && type == "Real") {
		((tPropSurface*)element)->setScale(*(tReal*)value);
		return true;
	} else if(index == nInheritedProperties()+2 && type == "Int") {
		((tPropSurface*)element)->setBladeNumber(*(int*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "Bool") {
		((tPropSurface*)element)->setRotationDirection(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+4 && type == "Bool") {
		((tPropSurface*)element)->setRoundedTip(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+5 && type == "Bool") {
		((tPropSurface*)element)->setAutoRoundTE(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+6 && type == "Bool") {
		((tPropSurface*)element)->setAutoRoundTip(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+7 && type == "String") {
		((tPropSurface*)element)->setRadialRefinement(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+8 && type == "String") {
		((tPropSurface*)element)->setPeripherRefinement(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+9 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropSurface*)element)->setPitch((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+10 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropSurface*)element)->setChord((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+11 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropSurface*)element)->setRake((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+12 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropSurface*)element)->setSkew((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+13 && ( type == "Curve" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Curve")))) {
		((tPropSurface*)element)->setMaxThick((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+14 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tPropSurface*)element)->setThickness((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+15 && ( type == "Surface" || value==NULL || (type=="Element" && ((tElement*)value)->intrface()->isOfType("Surface")))) {
		((tPropSurface*)element)->setCamber((tElement*)value);
		return true;
	} else if(index == nInheritedProperties()+16 && type == "Bool") {
		((tPropSurface*)element)->setReadWriteMode(*(bool*)value);
		return true;
	} else if(index == nInheritedProperties()+17 && type == "String") {
		((tPropSurface*)element)->importExportPropeller(*(tString*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iPropSurface::isReadOnly(int index)
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
	} else if (index == nInheritedProperties()+6){
		return false;
	} else if (index == nInheritedProperties()+7){
		return false;
	} else if (index == nInheritedProperties()+8){
		return false;
	} else if (index == nInheritedProperties()+9){
		return false;
	} else if (index == nInheritedProperties()+10){
		return false;
	} else if (index == nInheritedProperties()+11){
		return false;
	} else if (index == nInheritedProperties()+12){
		return false;
	} else if (index == nInheritedProperties()+13){
		return false;
	} else if (index == nInheritedProperties()+14){
		return false;
	} else if (index == nInheritedProperties()+15){
		return false;
	} else if (index == nInheritedProperties()+16){
		return false;
	} else if (index == nInheritedProperties()+17){
		return false;
	} else {
		return iSurface::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iPropSurface::isOptional(QString propName)
{
  if (QString(",isInReadingMode,propellerFileName,").contains("," + propName + ",")) {
    return true;
  } else {
    return iSurface::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iPropSurface::inheritedTypes(void)
{
	QString type;
	iPropSurface::getPropertyValue(0,"String",&type);
	return (iSurface::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iPropSurface::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iSurface::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

