#include "element/point/tOffsetPoint.h"

tOffsetPoint::tOffsetPoint(void *theOwner,tElement *S, tReal U, tReal V, tReal D):tDot(theOwner)
{
  surface = NULL;

  setReference(S);
  setOffset(D);
  setU(U);
  setV(V);
}
//-----------------------------------------------------------------------------

tOffsetPoint::~tOffsetPoint()
{
	surface->removeDependent(this);
}
//-----------------------------------------------------------------------------

void tOffsetPoint::refresh(void){
  if (surface){
    X = surface->vectorAt(uu,vv)+ surface->normalVectorAt(uu,vv)*distance;
  } else {
    X.setZero();
  }
}
//-----------------------------------------------------------------------------

void tOffsetPoint::setReference(tElement *el)
{
  setElementLocked
	if (surface){
		surface->removeDependent(this);
	}
	surface = dynamic_cast<tSurface*>(el);
	if (surface && !surface->addDependent(this)){
    surface = NULL;
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tOffsetPoint::intrface(void)
{
	if (iface == NULL){
		iface = new iOffsetPoint(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
/*
tList<tElement*> tOffsetPoint::usedElements(void)
{
	tList<tElement*> L;
	L.append(surface);
	return L;
}*/
//-----------------------------------------------------------------------------

tReal tOffsetPoint::u(void)
{
  setElementLocked
  return uu;
}
//-----------------------------------------------------------------------------

tReal tOffsetPoint::v(void)
{
  setElementLocked
  return vv;
}
//-----------------------------------------------------------------------------

tReal tOffsetPoint::offset(void){
  setElementLocked
  return distance;
}
//-----------------------------------------------------------------------------

tSurface* tOffsetPoint::reference(void){
  setElementLocked
  return surface;
}
//-----------------------------------------------------------------------------

void tOffsetPoint::setU(tReal u)
{
  setElementLocked
  uu = u;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tOffsetPoint::setV(tReal v)
{
  setElementLocked
  vv = v;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tOffsetPoint::setOffset(tReal d)
{
  setElementLocked
  distance = d;
  invalidate(this);
}
//-----------------------------------------------------------------------------

