#include "iVariable.h"
#include "tVariable.h"

iVariable::iVariable(tElement *el):iElement(el)
{
}
//-----------------------------------------------------------------------------

iVariable::~iVariable()
{
}
//-----------------------------------------------------------------------------

tString iVariable::getPropertyName(int index)
{
	if (index == nInheritedProperties()){
		return "variableType";
	} else if (index == nInheritedProperties()+ 1){
		return "isValid";
	} else if (index == nInheritedProperties()+ 2){
		return "fullString";
	} else if (index == nInheritedProperties()+ 3){
		return "RHS";
	} else {
		return iElement::getPropertyName(index);
	}
}
//-----------------------------------------------------------------------------

tString iVariable::getPropertyType(int index)
{
	if (index == nInheritedProperties()){
		return "Int";
	} else if (index == nInheritedProperties()+1){
		return "Bool";
	} else if (index == nInheritedProperties()+2){
		return "String";
	} else if (index == nInheritedProperties()+3){
		return "String";
	} else {
		return iElement::getPropertyType(index);
	}
}
//-----------------------------------------------------------------------------

bool iVariable::getPropertyValue(int index, tString propType, void* value)
{
	if (index == 0 && propType == "String"){
		*(tString*)value = iVariable::theType();
		return true;
	} else if (index == nInheritedProperties()+0 && propType == "Int") {
		*(int*)value = ((tVariable*)element)->type();
		return true;
	} else if (index == nInheritedProperties()+1 && propType == "Bool") {
		*(bool*)value = ((tVariable*)element)->isValidVariable();
		return true;
	} else if (index == nInheritedProperties()+2 && propType == "String") {
		*(tString*)value = ((tVariable*)element)->fullString();
		return true;
	} else if (index == nInheritedProperties()+3 && propType == "String") {
		*(tString*)value = ((tVariable*)element)->RHS();
		return true;
	} else {
		return iElement::getPropertyValue(index,propType,value);
	}
}
//-----------------------------------------------------------------------------

bool iVariable::setPropertyValue(int index, tString type, void* value)
{
	if (iElement::setPropertyValue(index,type,value)){
		return true;
	} else if(index == nInheritedProperties()+0){
		return false;
	} else if(index == nInheritedProperties()+1){
		return false;
	} else if(index == nInheritedProperties()+2 && type == "String") {
		((tVariable*)element)->setFullString(*(tString*)value);
		return true;
	} else if(index == nInheritedProperties()+3 && type == "String") {
		((tVariable*)element)->setRHS(*(tString*)value);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

bool iVariable::isReadOnly(int index)
{
	if (index == nInheritedProperties()){
		return true;
	} else if (index == nInheritedProperties()+1){
		return true;
	} else if (index == nInheritedProperties()+2){
		return false;
	} else if (index == nInheritedProperties()+3){
		return false;
	} else {
		return iElement::isReadOnly(index);
	}
}
//-----------------------------------------------------------------------------

bool iVariable::isOptional(QString propName)
{
  if (QString(",isValid,fullString,").contains("," + propName + ",")) {
    return true;
  } else {
    return iElement::isOptional(propName);
  }
}
//-----------------------------------------------------------------------------

QStringList iVariable::inheritedTypes(void)
{
	QString type;
	iVariable::getPropertyValue(0,"String",&type);
	return (iElement::inheritedTypes() << theType());
}
//-----------------------------------------------------------------------------

bool iVariable::isOfType(QString thetype)
{
	if (theType() == thetype){
		return true;
	} else {
		return iElement::isOfType(thetype); 
	}
}
//-----------------------------------------------------------------------------

