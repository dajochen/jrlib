#include "element/surface/tSubSurface.h"

tSubSurface::tSubSurface(void *theOwner,tElement *S1, tElement *S2): tSurface (theOwner)
{
  s1 = NULL;
  s2 = NULL;
  setBoundingSnakes(S1,S2);
}
//-----------------------------------------------------------------------------

tSubSurface::~tSubSurface()
{
  clear();
}
//-----------------------------------------------------------------------------

void tSubSurface::refresh(void){
  // es gibt nichts zu tun...
}

//-----------------------------------------------------------------------------

void tSubSurface::clear(void){
  setElementLocked 

  if (s1){
    s1->removeDependent(this); 
  }
  if (s2){
    s2->removeDependent(this); 
  }
}
//-----------------------------------------------------------------------------

void tSubSurface::setBoundingSnakes(tElement *el1, tElement *el2){
  setElementLocked 
  clear();
  s1 = dynamic_cast<tSnake*>(el1);
  s2 = dynamic_cast<tSnake*>(el2);
  if (s1 && s2 && s1->reference() == s2->reference()){
    if (s1 && !s1->addDependent(this)){
      s1 = NULL; 
    }
    if (s2 && !s2->addDependent(this)){
      s2 = NULL; 
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------
  
tList<tElement*> tSubSurface::boundingSnakes(void)
{
  tList<tElement*> list;
  list.append(s1);
  list.append(s2);
  return list;
}
//-----------------------------------------------------------------------------

void tSubSurface::setBoundingSnakes(tList<tElement*> l)
{
  if (l.count()==0){
    setBoundingSnakes(NULL, NULL);
  } else if (l.count()==1){
      setBoundingSnakes(l.at(0),NULL);
  } else {
    setBoundingSnakes(l.at(0),l.at(1));
  }
}
//-----------------------------------------------------------------------------

iElement* tSubSurface::intrface(void){
  
  if (iface == NULL){
    iface = new iSubSurface(this);
  }
  return iface;
  
}
//-----------------------------------------------------------------------------

tVector tSubSurface::vectorAtAccurate(tReal u, tReal v){
  setElementLocked 
  tSurface *s;
  tVector x;
  tReal u1,v1,u2,v2;
  
  if (s1 && s2){
    s = s1->reference();
    s1->uvPosition(u,&u1,&v1);
    s2->uvPosition(u,&u2,&v2);
    return s->vectorAt((1-v)*u1+v*u2,(1-v)*v1+v*v2);
  } else {
    x.setZero();
    return x; 
  }
}
//-----------------------------------------------------------------------------
  
tSurface* tSubSurface::reference(){
  setElementLocked 
  if (s1 && s2){
    return s1->reference(); 
  } else {
    return NULL;
  } 
}
