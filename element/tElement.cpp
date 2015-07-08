#include "element/tElement.h"
//#include "element/tPropertyLinker.h"

#include "classes/utils.h"

//A global Mutex
QMutex jrMutex(QMutex::Recursive);

using namespace std;

/**
 * Construct the element and set the owner of the element.
 */
tElement::tElement(void* theOwner)
{
//  myMutex = new QMutex(QMutex::Recursive);
  addOwner(theOwner);
  isValid = true;
  iface = NULL;
}
//-----------------------------------------------------------------------------

/**
 * Destroy the element
 */
tElement::~tElement()
{
  //map<QString, tElement*>::iterator it;

  blockInvalidateList.clear();

  // Die PropertyLinker entfernen
  //for (it=propertyLinkerMap.begin(); it!=propertyLinkerMap.end(); it++ ){
  //  it->second->removeDependent(this);
  //}
  //propertyLinkerMap.clear();

  if (iface)
    delete(iface);
}
//-----------------------------------------------------------------------------

/**
 * If the element is valid all dependent elements are invalidated to. It is possible to block this mechanism,
 * if the list blockInvalidateList containes the calling element. Also its interface - if there is any -
 * will be invalidated.
 */
void tElement::invalidate(tElement *sender){

  //for (int i=0;i<fdependent.count();i++){
  //  iElement::updateLinkedProperties(fdependent.at(i), this);
  //}

  if (isValid && !blockInvalidateList.contains(sender)){//!!!! ToDo: Streng genommen sollte nicht nur sender verfolgt werden, sondern alle Elemente die von diesem abhaengen
  	isValid = false;
/*    if (iface){
      iface->invalidate();
    }*/
    for (int i=0;i<fdependent.count();i++){
  		fdependent.at(i)->invalidate(sender);
  	}
  }// else {
   // Wenn das Element nicht mehr gueltig ist, sind auch die abhaengigen
   // ungueltig. Ein erneutes invalidate stiftet Verwirrung...
   // }
}
//-----------------------------------------------------------------------------
/**
 * Some properties don't require a full update, if they change. If the color or
 * the name of an element changes, geometrical quantities won't change but a repaint
 * of the element is enough. In such a case repaint should be called and not invalidate
 * to speed up the process.
 */
void tElement::repaintElement(tElement *sender)
/* Eine abgeschwaechte Version von invalidate. Teilt den Abhaengigen mit,
 * dass es neu gemalt werden will.*/
{
	int i, ni;
	ni = fdependent.count();
	for (i=0;i<ni;i++){
        fdependent.at(i)->repaintElement(sender);
        iElement::updateLinkedProperties(fdependent.at(i), this);
	}
}
//-----------------------------------------------------------------------------

/**
 * A standardised function which calls refresh and sets isValid to true.
 */
void tElement::update(void){
  if (!isValid){
    //if (iface) iface->updateLinkedProperties(); has to be updated during invalidate call :-(
		isValid = true;
		refresh();
	}
}
//-----------------------------------------------------------------------------

/**
 * Tells an Element, that another element doesn't need it any longer. This function
 * is usually called from the dependent function (parent->removeDependent(this)).
 */
void tElement::removeDependent (tElement *element){
	int i;
	if (element != NULL){
		i = fdependent.lastIndexOf(element);
	  if (i!= -1){
	  	fdependent.removeAt(i);
	  }
	}
  if (fdependent.isEmpty()/* && support.isEmpty()*/ && owner.isEmpty()){
  	delete this;
  }
}
//-----------------------------------------------------------------------------
/**
 * Returns a pointer towards the dependent element with the given index.
 */
tElement* tElement::dependent(int index)
{
	setElementLocked
	if (index >=0 && index < fdependent.count()){
		return fdependent.at(index);
	}
    return NULL;
}

tList<tElement *> tElement::dependents(bool recursive)
{
    setElementLocked;
    tList<tElement*> list;
    for(int i=0;i<fdependent.count();i++){
        tElement *el = fdependent.at(i);
        if (!list.contains(el)){
            list.append(el);
            if (recursive) {
                list.append(el->dependents(recursive));
            }
        }
    }
    return list;
}
//-----------------------------------------------------------------------------

/**
 * A PropertyLinker enables a property of the interface to be coupled to another
 * property of a different element, if they are of the same type. This is done
 * via a so called propertyLinker. In such a case the element will become a
 * dependent of the linker.
 *//*
void tElement::installPropertyLinker(const QString& property, tElement *sender)
{
  map<QString, tElement*>::iterator it;

  it = propertyLinkerMap.find(property);
  if (it != propertyLinkerMap.end()){
    it->second->uninstallPropertyLinker(property);
  }
  propertyLinkerMap[property] = sender;
  sender->addDependent(this);
}*/
//-----------------------------------------------------------------------------

/**
 * Removes an installed linker.
 *//*
void tElement::uninstallPropertyLinker(const QString& property)
{
  map<QString, tElement*>::iterator it;
  it = propertyLinkerMap.find(property);
  if (it != propertyLinkerMap.end()){
    it->second->removeDependent(this);
    propertyLinkerMap.erase(it);
  }
}*/
//-----------------------------------------------------------------------------

/*void tElement::updateLinkedProperties(void)
{
  map<QString, tElement*>::iterator it;
  for (it=propertyLinkerMap.begin(); it != propertyLinkerMap.end(); it++){
    tPropertyLinker* pl = dynamic_cast<tPropertyLinker*>(it->second);
    pl->updateProperty();
  }
}*/
//-----------------------------------------------------------------------------

/**
 * Copies the list of the "fDependents" into the list "*list".
 */
/*void tElement::addDirectDependents(tList<tElement*> *list)
{
	setElementLocked
	tElement *el;
	int i,ni;
	ni = fdependent.count();
  for(i=0;i<ni;i++){
  	el = fdependent.at(i);
  	if (!list->contains(el)){
  		list->append(el);
  	}
  }
}*/
//-----------------------------------------------------------------------------
/**
 * Add the depending elements to the list "*list" recursively.
 */
/*void tElement::addAllDependents(tList<tElement*> *list)
{
    setElementLocked;
    int i,ni;
    addDirectDependents(list);
    ni = fdependent.count();
    for(i=0;i<ni;i++){
        fdependent.at(i)->addAllDependents(list);
    }
}*/
//-----------------------------------------------------------------------------
/**
 * An element may have several owners. The sense is, that an other element might require the element to be accessible in memory,
 * but does not depend on it, which means that update - dependency - mechanism is not required.
 */
void tElement::addOwner(void* theOwner){
  if (theOwner){
    owner.append(theOwner);
  }
}
//-----------------------------------------------------------------------------
/**
 * Removes the owner from the element. The pointer "theOwner" must match the owner given
 * in the constructor.
 */
bool tElement::releaseOwner(void* theOwner){
  bool found = owner.contains(theOwner);
  if (found || (owner.isEmpty() && theOwner==NULL)) {
        owner.removeAt(owner.lastIndexOf(theOwner));
        //owner.removeLast(theOwner);
		removeDependent(NULL);
	}
	return found;
}
//-----------------------------------------------------------------------------
/**
 * Add a dependent to the "fDependent"-list. This is only possible if the new
 * element is not a support of the element, as this would result in an endless
 * loop during the update-mechnism.
 */
bool tElement::addDependent (tElement *element)
{
	if (!element->isSupportOf(this)){
		fdependent.append(element);
		return true;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------
/**
 * Test whether the element is support of the element given in the argument.
 */
bool tElement::isSupportOf(tElement* element)
{
	int i;
	if (element){
		if (element == this){
			return true;
		}
		for (i=0;i<fdependent.count();i++){
			if (fdependent.at(i) == element || fdependent.at(i)->isSupportOf(element)){
				return true;
			}
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
/*
tList<tElement*> tElement::usedElements(void)
{
	tList<tElement*> L;
	return L;
}*/
//-----------------------------------------------------------------------------

/**
 * return the minimum value of a geometric element. Here, a default function is
 * implemented
 */
tVector tElement::xMin(void)
{
  return tVector(0,0,0);
/*  int i;
  tVector x,x1;
  if (support.count() > 0){
    x = support.at(i)->xMin();
  } else {
    x.setZero();
    return x;
  }
  for (i=1;i<support.count();i++){
    x1 = support.at(i)->xMin();
    x.x = min(x.x,x1.x);
    x.y = min(x.y,x1.y);
    x.z = min(x.z,x1.z);
  }
  return x;*/
}
//-----------------------------------------------------------------------------
/**
 * return the maximum value of a geometric element. Here, a default function is
 * implemented
 */
tVector tElement::xMax(void){
  return tVector(0,0,0);
/*  int i;
  tVector x,x1;
  if (support.count() > 0){
    x = support.at(i)->xMax();
  } else {
    x.setZero();
    return x;
  }
  for (i=1;i<support.count();i++){
    x1 = support.at(i)->xMax();
    x.x = max(x.x,x1.x);
    x.y = max(x.y,x1.y);
    x.z = max(x.z,x1.z);
  }
  return x;*/
}
//-----------------------------------------------------------------------------

iElement* tElement::intrface(void)
{
  if (iface == NULL){
    iface = new iElement(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------


