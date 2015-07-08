#include "element/point/tRelPoint.h"

tRelPoint::tRelPoint(void *theOwner,tElement *el, tVector DX):tDot(theOwner)
{
  dot = NULL;
  setOffset(DX);
	setReference(el);
}
//-----------------------------------------------------------------------------

tRelPoint::~tRelPoint()
{
  if (dot){
    dot->removeDependent(this);
  }
}
//-----------------------------------------------------------------------------

void tRelPoint::refresh(void){
  if (dot){
    X = dot->vector()+dx;
  } else {
    X.setZero();
  }
}
//-----------------------------------------------------------------------------

tVector tRelPoint::offset(void){
  setElementLocked
	return dx;
}
//-----------------------------------------------------------------------------

void tRelPoint::setOffset(tVector v){
  setElementLocked
	dx = v;
	invalidate(this);
}
//-----------------------------------------------------------------------------

tDot* tRelPoint::reference(void)
{
  setElementLocked
	return dot;
}
//-----------------------------------------------------------------------------

void tRelPoint::setReference(tElement *el)
{
  setElementLocked
	if (dot){
		dot->removeDependent(this);
	}
  dot = dynamic_cast<tDot*>(el);
	if (dot && !dot->addDependent(this)){
		dot = NULL;
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

  iElement* tRelPoint::intrface(void)
{
	if (iface == NULL){
		iface = new iRelPoint(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
