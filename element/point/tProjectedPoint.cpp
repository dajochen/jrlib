#include "element/point/tProjectedPoint.h"

tProjectedPoint::tProjectedPoint(void *theOwner):tDot(theOwner)
{
  fdot = NULL;
  fplane = NULL;
  forigin.setZero();
}
//-----------------------------------------------------------------------------

tProjectedPoint::~tProjectedPoint()
{
  if (fdot){
    fdot->removeDependent(this);
  }
  if (fplane){
    fplane->removeDependent(this);
  }
}
//-----------------------------------------------------------------------------

void tProjectedPoint::refresh(void){

  tVector n, x;
  if (fplane){
    n = fplane->normal();
    if (fdot){
      X = fdot->vector()-n*(n*(fdot->vector()-fplane->center()));
    } else {
      X = forigin-n*(n*(forigin-fplane->center()));
    }
  } else {
    X.setZero();
  }
}
//-----------------------------------------------------------------------------

iElement* tProjectedPoint::intrface(void)
{
if (iface == NULL){
  iface = new iProjectedPoint(this);
}
return iface;
}
//-----------------------------------------------------------------------------

tVector tProjectedPoint::origin(void)
{
  if (fdot){
    return fdot->vector();
  } else {
    return forigin;
  }
}
//-----------------------------------------------------------------------------

void tProjectedPoint::setOrigin(tVector v)
{
  setElementLocked
  forigin = v;
  if (fdot){
    fdot->removeDependent(this);
    fdot = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tPlane* tProjectedPoint::plane(void)
{
  return fplane;
}
//-----------------------------------------------------------------------------

void tProjectedPoint::setPlane(tElement *el)
{
  setElementLocked
  tPlane *p;
  p = dynamic_cast<tPlane*>(el);
  if (fplane!=p){
    if(fplane){
      fplane->removeDependent(this);
    }
    fplane = p;
    if (p){
      p->addDependent(this);
    }
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------

tDot* tProjectedPoint::refDot(void)
{
  return fdot;
}
//-----------------------------------------------------------------------------

void tProjectedPoint::setRefDot(tElement *el)
{
  setElementLocked
  tDot *d;
  d = dynamic_cast<tDot*>(el);
  if (fdot!=d){
    if(fdot){
      fdot->removeDependent(this);
    }
    fdot = d;
    if (d){
      d->addDependent(this);
    }
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------
