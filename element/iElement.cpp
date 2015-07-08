#include "element/iElement.h"
#include "element/tElement.h"

/*-------------------------------------------------------------------------
 * Das Interface
 * ----------------------------------------------------------------------*/

iElement::iElement(tElement *el)
{
  //isValid = false;
	fvisibility = true;
    linksLocked = false;
	fname = "";
    //fcolor = tRGB::MSColor(10);
    fcolor = tRGB(5,122,133,255);
    //fcolor.alpha = 155;
	element = el;
}
//-----------------------------------------------------------------------------

iElement::~iElement()
{
  foreach (const int &propID, linkedElement.keys()) {
    linkedElement[propID]->removeDependent(element);
  }
  linkedElement.clear();
  linkedProperty.clear();
}
//-----------------------------------------------------------------------------

void iElement::invalidate(void)
{  
  //isValid = false;
/*
  int i=0;
  while (element->dependent(i)){
    tElement *el = element->dependent(i);
    if (el->hasInterface()){
      el->intrface()->updateLinkedProperties(element);
      el->intrface()->invalidate();
    }
    i++;
  }*/
}
//-----------------------------------------------------------------------------

bool iElement::visibility()
{
  return fvisibility;
}
//-----------------------------------------------------------------------------

void iElement::setVisibility(bool value)
{
  fvisibility = value;
  element->repaintElement( element );
}
//-----------------------------------------------------------------------------

tRGB iElement::color()
{
  return fcolor;
}
//-----------------------------------------------------------------------------

void iElement::setColor(tRGB value)
{
  fcolor = value;
  element->repaintElement( element );
}
//-----------------------------------------------------------------------------

tString iElement::name()
{
  return fname;
}
//-----------------------------------------------------------------------------

void iElement::setName(QString value)
{
  fname = value;
  element->repaintElement( element );
}
//-----------------------------------------------------------------------------

tString iElement::type() const
{
  return iElement::theType();
}
//-----------------------------------------------------------------------------

QStringList iElement::inheritedTypes(void){
  QString type;
  iElement::getPropertyValue(0,"String",&type);
  return QStringList(type);
}
//-----------------------------------------------------------------------------

bool iElement::isOfType(QString thetype)
{
  return ("Element"==thetype); // Ende der Rekursion.
}
//-----------------------------------------------------------------------------

int iElement::getPropertyIndex(QString name)
{
  int i;
  for (i = nProperties()-1; i>=0 && getPropertyName(i) != name;i--);
  return i;
}
//-----------------------------------------------------------------------------

QString iElement::getPropertyName(int index)
{
  if (index == 0){
		return "type";
	} else if (index == 1){
		return "name";
	} else if (index == 2){
		return "color";
	} else if (index == 3){
		return "xMin";
  } else if (index == 4){
		return "xMax";
	} else if (index == 5){
		return "visibility";
	} else {
	  return "No Property";
	}
}
//-----------------------------------------------------------------------------

QString iElement::getPropertyType(int index)
{
	if (index == 0){
		return "String";
	} else if (index == 1){
	  return "String";
	} else if (index == 2){
	  return "RGB";
	} else if ( index == 3 ||
							index == 4){
	  return "Vector";
	} else if (index == 5){
	  return "Bool";
	} else {
	  return "None";
    }
}

QStringList iElement::getPropertyNames()
{
    QStringList names;
    for (int i=0;i<nProperties(); i++){
        names.append(getPropertyName(i));
    }
    return names;
}

QStringList iElement::getPropertyTypes()
{
    QStringList types;
    for (int i=0;i<nProperties(); i++){
        types.append(getPropertyType(i));
    }
    return types;
}
//-----------------------------------------------------------------------------

bool iElement::getPropertyValue(int index, QString type, void* value)
{
	if (index == 0 && type == "String"){
		*(QString*)value = "Element";
		return true;
	} else if (index == 1 && type == "String"){
    *(QString*)value = name();
		return true;
	} else if (index == 2 && type == "RGB"){
		*(tRGB*)value = fcolor;
		return true;
	} else if (index == 3 && type == "Vector"){
		*(tVector*)value = element->xMin();
		return true;
	} else if (index == 4 && type == "Vector"){
		*(tVector*)value = element->xMax();
		return true;
	} else if (index == 5 && type == "Bool"){
		*(bool*)value = fvisibility;
		return true;
	} else {
	  value = NULL;
	  return false ;
	}
}
//-----------------------------------------------------------------------------

int iElement::getPropertyInt (QString name)
{
  int i;
  if (getPropertyValue(name,"Int",&i)){
     return i;
  } else {
     return 0;
  }
}
//-----------------------------------------------------------------------------

QString iElement::getPropertyString (QString name)
{
  QString s;
  if (getPropertyValue(name,"String",&s))
     return s;
   else
     return "";
}
//-----------------------------------------------------------------------------

bool iElement::getPropertyValue(QString name, QString type, void* value)
{
    int i;
    for (i = 0;i < nProperties() && getPropertyName(i) != name;i++);
    if (i < nProperties())
        return getPropertyValue(i, type, value);
    else
        value = NULL;
    return false;
}
//-----------------------------------------------------------------------------

bool iElement::isReadOnly(int index)
{
	if (index == 1 || index == 2 || index == 5){
		return false;
	} else {
		return true;
	}
}
//-----------------------------------------------------------------------------

bool iElement::isOptional(QString /*name*/)
{
  return false;
}
//-----------------------------------------------------------------------------

bool iElement::setPropertyValue(QString name, QString type, void* value)
{
	int i;
  i = getPropertyIndex(name);
  if (i > -1)
    return setPropertyValue(i, type, value);
  else
	  return false;
}
//-----------------------------------------------------------------------------

bool iElement::setPropertyValue(int index, QString type, void* value)
{
  if (!linksLocked && linkedElement.contains(index)){
    linkedElement[index]->removeDependent(element);
    linkedElement.remove(index);
    linkedProperty.remove(index);
  }

	if (index == 0 && type == "String"){
		return false;
	} else if (index == 1 && type == "String"){
        setName(*(QString*)value);
		return true;
	} else if (index == 2 && type == "RGB"){
        setColor(*(tRGB*)(value));
        return true;
	} else if (index == 3 || index == 4){
		// xMin und xMax koennen nicht gesetzt werden.
		return false;
	} else if (index == 5 && type == "Bool"){
		fvisibility = *(bool*)value;
    element->repaintElement( element );
		return false;
	} else {
	  return false ;
	}
}
//-----------------------------------------------------------------------------

bool iElement::setPropertyString(QString name, QString value)
{
  return setPropertyValue (name, "String", &value);
}
//-----------------------------------------------------------------------------

bool iElement::setPropertyInt(QString name, int value)
{
  return setPropertyValue (name, "Int", &value);
}
//-----------------------------------------------------------------------------

bool iElement::linkProperty(QString property, tElement *sender, QString senderProperty)
{
  int propID = getPropertyIndex(property);
  if (propID>=0 && sender && sender->addDependent(element)){
    linkedElement[propID] = sender;
    linkedProperty[propID] = senderProperty;
    sender->intrface();//init intrface
//    updateLinkedProperties(element, sender);
    sender->invalidate(sender);
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------
/**
 * @brief iElement::updateLinkedProperties
 * static class which is included in the update mechanism. Typically this function is not called by the user.
 * @param receiver
 * The one who will be updated
 * @param from
 * The one who potentially supports receiver
 */
void iElement::updateLinkedProperties(tElement *receiver, tElement *from)
{
  if (receiver->hasInterface()){
    receiver->intrface()->updateLinkedProperties(from);
  }

  int i=0;
  while (receiver->dependent(i)){
    tElement *el = receiver->dependent(i);
    updateLinkedProperties(el, receiver);
    i++;
  }
}
//-----------------------------------------------------------------------------
/**
 * @brief iElement::updateLinkedProperties
 * updates the properties involved between pointer "element" and "from". The function is invoked through
 * updateLinkedProperties(receiver, sender).  Typically this function is not called by the user.
 * @param from
 * A pointer to the class which has changed.
 */
void iElement::updateLinkedProperties(tElement *from)
{
  element->lockElement();
  linksLocked = true;
  foreach (const int &id, linkedElement.keys()) {
    tElement *sender = linkedElement[id];
    int senderID = sender->intrface()->getPropertyIndex(linkedProperty[id]);

    if (sender==from && senderID >=0){
      QString linkType = sender->intrface()->getPropertyType(senderID);
      QString linkToType = linkType; // will be modified if linkType is something like tList<tXXX*>. Here tXXX is derived from tElement.

      void *value =NULL;
      int iVal;
      tReal rVal;
      bool bVal;
      tVector vVal;
      tRGB rgbVal;
      QString strVal;
      tElement *el=NULL;
      tList<int> intList;
      tList<tReal> realList;
      tList<bool> boolList;
      tList<tVector> vectorList;
      tList<tRGB> rgbList;
      tList<QString> stringList;
      tList<tElement*> elementList;

      if (linkType=="Int"){
        value = &iVal;
      } else if (linkType=="Real"){
        value = &rVal;
      } else if (linkType=="Bool"){
        value = &bVal;
      } else if (linkType=="Vector"){
        value = &vVal;
      } else if (linkType=="RGB"){
        value = &rgbVal;
      } else if (linkType=="String"){
        value = &strVal;
      } else {
        if (linkType.endsWith("List")){
          if (linkType.startsWith("Int")){
            value = &intList;
          } else if (linkType.startsWith("Real")){
            value = &realList;
          } else if (linkType.startsWith("Bool")){
            value = &boolList;
          } else if (linkType.startsWith("Vector")){
            value = &vectorList;
          } else if (linkType.startsWith("RGB")){
            value = &rgbList;
          } else if (linkType.startsWith("String")){
            value = &stringList;
          } else {
            linkToType = getPropertyType(id);
            if (linkToType.endsWith("List")){
              linkToType.remove(linkToType.length()-1-4,4);
              if (!iElement::nonElementTypes().contains(linkToType)){
                value = &elementList;
              }
            }
            char dbg[500];
            strcpy (dbg,qPrintable(linkToType));
            linkToType = getPropertyType(id);
          }
        } else {
          value = &el;
        }
      }

      if (value){
        sender->intrface()->getPropertyValue(senderID,linkType,value);
        setPropertyValue(id, linkToType , value);
      }
    }
  }
  linksLocked = false;
  element->unlockElement();
}
//-----------------------------------------------------------------------------

QStringList iElement::getActionNames()
{
    QStringList names;
    for (int i=0;i<nActions(); i++){
        names.append(getActionName(i));
    }
    return names;
}
//-----------------------------------------------------------------------------

int iElement::getActionIndex(QString name)
{
  int i;
  for (i = nActions()-1; i>=0 && getActionName(i) != name;i--);
  return i;
}
