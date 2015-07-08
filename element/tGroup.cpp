#include "element/tGroup.h"
#include "model/tLayer.h"

#include "classes/utils.h"


tGroup::tGroup(void *theOwner, const QString& allowedType)
: tElement(theOwner),
  fAllowedType(allowedType)
{
}
//-----------------------------------------------------------------------------

tGroup::~tGroup()
{
	clear();
}
//-----------------------------------------------------------------------------

int tGroup::nElements()
{
  setElementLocked
  update();
  return member.count();
}
//-----------------------------------------------------------------------------

int tGroup::nElements(QString type)
{
	setElementLocked
	int i,found;


    update();
	found = 0;
	for (i=0; i<member.count(); i++){
	  if (member.at(i)->intrface()->isOfType(type)){
			found ++;
		}
	}
	return found;
}
//-----------------------------------------------------------------------------

tElement* tGroup::append(tElement* el){
  setElementLocked
	if (el
	    && (fAllowedType.isEmpty() || el->intrface()->isOfType(fAllowedType))
	    && el->addDependent(this)){
 		member.append(el);
 	  invalidate(this);
	} else {
	  el = NULL;
	}
  return el;
}

void tGroup::append(const tList<tElement *> &l)
{
    setElementLocked

    for (int i=0;i<l.count(); i++) {
        append(l.at(i));
    }
}
//------------------------------------------------------------------------------

tElement* tGroup::prepend(tElement* el){
  setElementLocked
  if (el
      && (fAllowedType.isEmpty() || el->intrface()->isOfType(fAllowedType))
      && el->addDependent(this)){
 		member.prepend(el);
 	  invalidate(this);
  } else {
    el = NULL;
  }
	return el;
}
//------------------------------------------------------------------------------

void tGroup::setElements(const tList<tElement*> &l)
{
  setElementLocked
  if ( !l.isEqualTo(member) ) {
      clear();
      for (int i=0;i<l.count(); i++) {
          append(l.at(i));
      }
      //member = l; quatsch.
      //invalidate(this);
  }
}
//------------------------------------------------------------------------------

bool tGroup::removeAllElements(tElement *el)
{
  setElementLocked
  int i;
  bool found = false;
  for (i=0;i<member.count();i++){
  	if (member.at(i)==el){
  	  found = true;
  	  removeElement(i);
//  		el->removeDependent(this);
//  		member.removeAt(i);
  		i--;
  	}
  }
  return found;
}
//------------------------------------------------------------------------------

void tGroup::removeElement(int i)
{
  setElementLocked
  if (i>=0 && i<member.count()){
    tElement *el = element(i);
    member.removeAt(i);
    el->removeDependent(this);
    invalidate(this);
  }
}
//------------------------------------------------------------------------------

void tGroup::removeAllElements(QString name, QString type)
{
  for (int i=0; i<member.count(); i++){
    tElement *el = member.at(i);
    if (el->intrface()->name() == name &&
        (type == "" || el->intrface()->isOfType(type))){
      removeElement(i);
      i--;
    } else {
      tGroup *g = dynamic_cast<tGroup*>(el);
      if (g){
        g->removeAllElements(name, type);
      }
    }
  }
}

//------------------------------------------------------------------------------

void tGroup::clear(void)
{
    setElementLocked

    if (member.count() ){
        for (int i=0;i<member.count();i++){
            member.at(i)->removeDependent(this);
        }
        member.clear();
        invalidate(this);
    }
}
//------------------------------------------------------------------------------

void tGroup::removeAllButLast(void)
{
  setElementLocked
	int i,ni;
	ni = member.count()-2;
  for (i=ni;i>=0;i--){
		member.at(i)->removeDependent(this);
		member.removeAt(i);
  }
  invalidate(this);
}
//------------------------------------------------------------------------------

void tGroup::removeAllButFirst(void)
{
  setElementLocked
	int i,ni;
	ni = member.count()-1;
  for (i=ni;i>=1;i--){
		member.at(i)->removeDependent(this);
		member.removeAt(i);
  }
  invalidate(this);
}
//------------------------------------------------------------------------------

tList<tElement*> tGroup::elements(QString type, bool recursive)
{
  setElementLocked
  update();
  tList<tElement*> elems;
  if (type == ""){
    elems = member;
  } else {
    for (int i=0; i<member.count(); i++){
      tElement* e = NULL;
      e = member.at(i);
      if (e->intrface()->isOfType(type)){
        elems.append(e);
      }
    }
  }

  if (recursive) {
      for (int i=0; i<member.count(); i++){
          tLayer* l = dynamic_cast<tLayer*>( member.at(i));
          if (l){
              elems.append( l->elements(type, recursive) );
          }
      }
  }
  return elems;

}
//------------------------------------------------------------------------------

void tGroup::reverse(void){
  setElementLocked
	member.reverse();
  invalidate(this);
}
//------------------------------------------------------------------------------

tElement* tGroup::element(int index){
  setElementLocked
  update();
  if (index < member.count() && index >= 0){
      return member.at(index);
	} else {
      return NULL;
  }
}
//------------------------------------------------------------------------------

/**
 * Looks for an element called <name> which is of the type <type>
 */
tElement* tGroup::elementByName(const QString &name, const QString &type)
{
  setElementLocked

  int i;
  tElement *e;
  iElement *iface;

  update();
  for (i=nElements()-1;i>=0;i--){
    e = element(i);
    iface = e->intrface();

    if (iface->name() == name){
      if (type.isEmpty() || iface->isOfType(type)){
        return e;
      }
    }
    tGroup* g = dynamic_cast<tGroup*>(e);
    if (g){
      e = g->elementByName(name, type);
      if (e){
        return e;
      }
    }
  }

  return NULL;
}
//-----------------------------------------------------------------------------

tElement* tGroup::last(void){
  setElementLocked
  update();
	if (member.count() > 0){
		return member.last();
	} else {
		return NULL;
	}
}
//------------------------------------------------------------------------------

tElement* tGroup::first(void){
  setElementLocked
  update();
	if (member.count() > 0){
		return member.at(0);
	} else {
		return NULL;
	}
}
//------------------------------------------------------------------------------

bool tGroup::contains(tElement* el){
  setElementLocked
  update();
  return (member.contains(el));
}
//------------------------------------------------------------------------------

void tGroup::refresh(void)
{
// nichts zu tun.
}
//------------------------------------------------------------------------------

iElement* tGroup::intrface(void)
{
  setElementLocked
	if (iface == NULL){
		iface = new iGroup(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tGroup::xMin(void)
{
  setElementLocked
	tVector xmin;
	int i;

  update();
	if (member.count()> 0){
		xmin = member.at(0)->xMin();
		for (i=1;i<member.count();i++){
			xmin.x = min(member.at(i)->xMin().x, xmin.x);
			xmin.y = min(member.at(i)->xMin().y, xmin.y);
			xmin.z = min(member.at(i)->xMin().z, xmin.z);
		}
	}
	return xmin;
}
//-----------------------------------------------------------------------------

tVector tGroup::xMax(void)
{
  setElementLocked
	tVector xmax;
	int i;

  update();
	if (member.count()> 0){
		xmax = member.at(0)->xMax();
		for (i=1;i<member.count();i++){
			xmax.x = max(member.at(i)->xMax().x, xmax.x);
			xmax.y = max(member.at(i)->xMax().y, xmax.y);
			xmax.z = max(member.at(i)->xMax().z, xmax.z);
		}
	}
	return xmax;
}
