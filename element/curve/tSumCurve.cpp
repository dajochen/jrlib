#include "element/curve/tSumCurve.h"

tSumCurve::tSumCurve(void *theOwner) : tCurve(theOwner)
{

}
//-----------------------------------------------------------------------------

tSumCurve::~tSumCurve()
{
  clear();
}
//-----------------------------------------------------------------------------
void tSumCurve::clear(void)
{
  setElementLocked;
  int i;
  for (i=0;i<support.count();i++){
    support.at(i)->removeDependent(this);
  }
  support.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tSumCurve::addSupport(tElement *el)
{
  setElementLocked;
  tCurve *c = dynamic_cast<tCurve*>(el);
  if (c){
    support.append(c);
    c->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tSumCurve::addSupportList(tList<tElement*> *list)
{
  setElementLocked;
  int i;
  if (list){
    for (i=0;i<list->count();i++){
      addSupport(list->at(i));
    }
  }
}
//-----------------------------------------------------------------------------

void tSumCurve::refresh(void)
{
  // es gibt nichts zu tun...
}
//-----------------------------------------------------------------------------

tVector tSumCurve::vectorAtAccurate(tReal t)
{
  setElementLocked;
  int i;
  tVector x;
  update();
  if (support.count() > 0){
    x = support.at(0)->vectorAt(t);
    for (i=1;i<support.count();i++){
      x = x + support.at(i)->vectorAt(t);
    }
  } else {
    x.setZero();
  }
  return x;
}
//-----------------------------------------------------------------------------

iElement* tSumCurve::intrface(void)
{
  if (iface == NULL){
    iface = new iSumCurve(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

tList<tElement*> tSumCurve::supportList(void)
{
  setElementLocked;
  int i;
  tList<tElement*> l;
  for (i=0;i<support.count();i++){
    l.append(support.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tSumCurve::setSupportList(tList<tElement*> l)
{
  setElementLocked;
  int i;
  clear();
  for (i=0;i<l.count();i++){
    addSupport(l.at(i));
  }
}
//-----------------------------------------------------------------------------
