#include "element/point/tMidPoint.h"

tMidPoint::tMidPoint(void *theOwner, tElement *element):tDot(theOwner)
{
  addDot(element);
}
//-----------------------------------------------------------------------------

tMidPoint::~tMidPoint()
{
  int i;
  for (i=0;i<dot.count();i++){
    dot.at(i)->removeDependent(this); 
  } 
}
//-----------------------------------------------------------------------------

int tMidPoint::countGroupDots(tGroup *g){
  int i,n;
  tDot *d;
  tGroup *gg;

  n = 0;
  for (i=0;i<g->nElements();i++){
    d = dynamic_cast<tDot*>(g->element(i));
    gg = dynamic_cast<tGroup*>(g->element(i));
    if (d){
      n ++;
    } else if (gg){
      n += countGroupDots(gg);  
    }
  }
  return n;
}
//-----------------------------------------------------------------------------

tVector tMidPoint::sumGroup(tGroup *g){
  tVector X;
  tDot *d;
  tGroup *gg;
  int i; 

  X.setZero();
  for (i=0;i<g->nElements();i++){
    d = dynamic_cast<tDot*>(g->element(i));
    gg = dynamic_cast<tGroup*>(g->element(i));
    if (d){
      X = X + d->vector();
    } else if (gg){
      X = X + sumGroup(gg);  
    }
  }
  return X;
}
//-----------------------------------------------------------------------------
  
void tMidPoint::refresh(void)
{
  int i,n;
  tDot *d;
  tGroup *g;

  n = 0;
  X.setZero();
  for (i=0;i<dot.count();i++){
    d = dynamic_cast<tDot*>(dot.at(i));
    g = dynamic_cast<tGroup*>(dot.at(i));
    if (d){
      X = X + d->vector();
      n ++;
    } else if (g){
      X = X + sumGroup(g);
      n += countGroupDots(g);
    }
  }
  if (i>0){
    X = X *(1./(tReal)n); 
  }
}
//-----------------------------------------------------------------------------

void tMidPoint::addDot(tElement* d){
  setElementLocked
  tDot *theDot;
  tGroup *group;
  theDot = dynamic_cast<tDot*>(d);
  group = dynamic_cast<tGroup*>(d);
  if (theDot){
    dot.append(theDot); 
    d->addDependent(this);
  } else if (group){
    dot.append(group);
    group->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tList<tElement*> tMidPoint::dots(void)
{
  setElementLocked
  int i;
  tList<tElement*> l;
  for (i=0;i<dot.count();i++){
    l.append(dot.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tMidPoint::setDots(tList<tElement*> dList)
{
  setElementLocked
  int i;
  removeAll();
  for (i=0;i<dList.count();i++){
    addDot(dList.at(i));
  }
}
//-----------------------------------------------------------------------------

void tMidPoint::removeDot(tElement* d){
  setElementLocked
  tDot *theDot;
  theDot = dynamic_cast<tDot*>(d);
  if (theDot){
    dot.removeFirst(theDot); 
    theDot->removeDependent(this);
  }
  invalidate(this);  
}
//-----------------------------------------------------------------------------

void tMidPoint::removeAll(){
  setElementLocked
  int i;
  for (i=0;i<dot.count();i++){
    dot.at(i)->removeDependent(this); 
  }
  dot.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

tList<tElement*> tMidPoint::dotList(void){
  return dot;
}
//-----------------------------------------------------------------------------

iElement* tMidPoint::intrface(void)
{
  if (iface == NULL){
    iface = new iMidPoint(this);
  }
  return iface; 
}
//-----------------------------------------------------------------------------

