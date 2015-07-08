#include "element/curve/tMidCurve.h"

tMidCurve::tMidCurve(void *theOwner) : tCurve(theOwner)
{

}
//-----------------------------------------------------------------------------

tMidCurve::~tMidCurve()
{
  clear();
}
//-----------------------------------------------------------------------------
void tMidCurve::clear(void)
{
  setElementLocked
  int i;
  for (i=0;i<support.count();i++){
    support.at(i)->removeDependent(this);
  }
  support.clear();
}
//-----------------------------------------------------------------------------

void tMidCurve::addElement(tElement *el)
{
  setElementLocked
  tCurve *c = dynamic_cast<tCurve*>(el);
  if (c){
    support.append(c);
    c->addDependent(this);
  }
}
//-----------------------------------------------------------------------------

void tMidCurve::addList(tList<tElement*> *list)
{
  setElementLocked
  int i;
  if (list){
    for (i=0;i<list->count();i++){
      addElement(list->at(i));
    }
  }
}
//-----------------------------------------------------------------------------

void tMidCurve::removeAllCurves(void)
{
  setElementLocked;
  int i,n;
  n = support.count();
  for (i=0;i<n;i++){
    support.at(i)->removeDependent(this);
  }
  support.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tMidCurve::setCurves(tList<tElement*> list)
{
  setElementLocked;
  removeAllCurves();
  addList(&list);
}
//-----------------------------------------------------------------------------

tList<tElement*> tMidCurve::curves(void){
  setElementLocked;
  tList<tElement*> l;
  int i,n;
  n = support.count();
  for (i=0;i<n;i++){
    l.append(support.at(i));
  }
  return l;
}

//-----------------------------------------------------------------------------

void tMidCurve::refresh(void)
{
  // es gibt nichts zu tun...
}
//-----------------------------------------------------------------------------

tVector tMidCurve::vectorAtAccurate(tReal t)
{
  setElementLocked
  int i;
  tVector x;
  update();
  if (support.count() > 0){
    x = support.at(0)->vectorAt(t);
    for (i=1;i<support.count();i++){
      x = x + support.at(i)->vectorAt(t);
    }
    x = x * (1./(tReal)support.count());
  } else {
    x.setZero();
  }
  return x;
}
//-----------------------------------------------------------------------------

iElement* tMidCurve::intrface(void)
{
  if (iface == NULL){
    iface = new iMidCurve(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
