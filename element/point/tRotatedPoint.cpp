#include "element/point/tRotatedPoint.h"

tRotatedPoint::tRotatedPoint(void *theOwner,tElement *REFDOT, tElement *AXIS, tReal angle):tDot(theOwner)
{
	refDot = NULL;
	Axis = NULL;

	setAngle(angle);
	setReference(REFDOT);
	setAxis(AXIS);
}
//-----------------------------------------------------------------------------

tRotatedPoint::~tRotatedPoint()
{
	refDot->removeDependent(this);
	Axis->removeDependent(this);
}
//-----------------------------------------------------------------------------

void tRotatedPoint::refresh(void){
	tVector x,x0,x1;
	if (refDot && Axis && Axis->length()>0){
		x = refDot->vector();
		x0 = *Axis->start();
		x1 = ((tVector)*Axis->end())-x0;
		X = x.rotate(x0,x1,Angle);
	} else {
		X.setZero();
	}
}
//-----------------------------------------------------------------------------

tReal tRotatedPoint::angle(void){
  setElementLocked
	return Angle;
}
//-----------------------------------------------------------------------------

void tRotatedPoint:: setAngle(tReal a){
  setElementLocked
	Angle = a;
	invalidate(this);
}
//-----------------------------------------------------------------------------

tDot* tRotatedPoint::reference(void)
{
  setElementLocked
	return refDot;
}
//-----------------------------------------------------------------------------

void tRotatedPoint::setReference(tElement *el)
{
  setElementLocked
	if (refDot){
		refDot->removeDependent(this);
	}
	refDot = dynamic_cast<tDot*>(el);
	if (refDot &&	!refDot->addDependent(this)){
    refDot = NULL;
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

tLine* tRotatedPoint::axis(void)
{
  setElementLocked
	return Axis;
}
//-----------------------------------------------------------------------------

void tRotatedPoint::setAxis(tElement *el)
{
  setElementLocked
	if (Axis){
		Axis->removeDependent(this);
	}
	Axis = dynamic_cast<tLine*>(el);
	if (Axis && !Axis->addDependent(this)){
    Axis = NULL;
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tRotatedPoint::intrface(void)
{
	if (iface == NULL){
		iface = new iRotatedPoint(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
/*
tList<tElement*> tRotatedPoint::usedElements(void)
{
	tList<tElement*> L;
	L.append(refDot);
	L.append(Axis);
	return L;
}*/
//-----------------------------------------------------------------------------
