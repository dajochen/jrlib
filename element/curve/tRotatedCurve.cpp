#include "element/curve/tRotatedCurve.h"

tRotatedCurve::tRotatedCurve(void *theOwner, tElement *curve, tElement *axis, tReal phi): tCurve(theOwner)
{
	Axis = NULL;
	RefCurve = NULL;
	Angle = phi;
	setReference(curve);
	setAxis(axis);
}

//-----------------------------------------------------------------------------
tRotatedCurve::~tRotatedCurve()
{
	if (Axis) Axis->removeDependent(this);
	if (RefCurve) RefCurve->removeDependent(this);
}
//-----------------------------------------------------------------------------

iElement* tRotatedCurve::intrface(void)
{
	if (iface == NULL){
		iface = new iRotatedCurve(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tRotatedCurve::vectorAtAccurate(tReal t)
{
  setElementLocked
	update();
	tVector x,x0,x1;
	if (RefCurve && Axis){
    x = RefCurve->vectorAt(t);
    if (Axis->length()>0){
      x0 = *Axis->start();
      x1 = ((tVector)*Axis->end())-x0;
    } else {
      // Wenn keine Rotationsachse vorhanden ist, wird die x-Achse verwendet.
      x0.setZero();
      x1.setZero();
      x1.x = 1.;
    }
    x = x.rotate(x0,x1,Angle);
	} else {
	  x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tRotatedCurve::gradientAt(tReal t)
{
  setElementLocked
	update();
	tVector n,x0,x1;
	n = RefCurve->gradientAt(t);
	if (Axis->length()>0){
		x0 = *Axis->start();
		x1 = ((tVector)*Axis->end())-x0;
	} else {
		// Wenn keine Rotationsachse vorhanden ist, wird die x-Achse verwendet.
		x0.setZero();
		x1.setZero();
		x1.x = 1.;
	}
	n = n.rotate(x0,x1,Angle);
	return n;
}
//-----------------------------------------------------------------------------

tVector tRotatedCurve::curvatureAt(tReal t)
{
  setElementLocked
	update();
	tVector n,x0,x1;
	n = RefCurve->curvatureAt(t);
	if (Axis->length()>0){
		x0 = *Axis->start();
		x1 = ((tVector)*Axis->end())-x0;
	} else {
		// Wenn keine Rotationsachse vorhanden ist, wird die x-Achse verwendet.
		x0.setZero();
		x1.setZero();
		x1.x = 1.;
	}
	n = n.rotate(x0,x1,Angle);
	return n;
}
//-----------------------------------------------------------------------------

void tRotatedCurve::setAxis(tElement* el)
{
  setElementLocked
	if (Axis) Axis->removeDependent(this);
  Axis = dynamic_cast<tLine*>(el);
	if (Axis && !Axis->addDependent(this)){
    Axis = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRotatedCurve::setReference(tElement *el)
{
  setElementLocked
	if (RefCurve) RefCurve->removeDependent(this);
  RefCurve = dynamic_cast<tCurve*>(el);
	if (RefCurve && !RefCurve->addDependent(this)){
    RefCurve=NULL;
  };
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRotatedCurve::refresh(void)
{
	// es gibt nichts zu tun.
}
//-----------------------------------------------------------------------------
