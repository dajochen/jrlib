#include "element/surface/tRevolvedSurface.h"

tRevolvedSurface::tRevolvedSurface(void *theOwner): tSurface(theOwner)
{
	faxis = NULL;
	frefCurve = NULL;
	fstartAngle = 0.;
	fendAngle = M_PI*2.;
}
//-----------------------------------------------------------------------------

tRevolvedSurface::tRevolvedSurface(void *theOwner, tElement *curve, tElement *a, tReal startAngle, tReal endAngle): tSurface(theOwner)
{
	faxis = NULL;
	frefCurve = NULL;
	fstartAngle= startAngle;
	fendAngle = endAngle;
	setRefCurve(curve);
	setAxis(a);
}

//-----------------------------------------------------------------------------
tRevolvedSurface::~tRevolvedSurface()
{
	if (faxis) faxis->removeDependent(this);
	if (frefCurve) frefCurve->removeDependent(this);
}
//-----------------------------------------------------------------------------

iElement* tRevolvedSurface::intrface(void)
{
	if (iface == NULL){
		iface = new iRevolvedSurface(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tRevolvedSurface::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked
	update();
	tVector x,x0,x1;
//	x = refSurface->vectorAt(u,v);
	if (frefCurve && faxis){
    x = frefCurve->vectorAt(u);
    if (faxis->length()>0){
      x = x.rotate(faxis->start()->vector(),faxis->end()->vector(),fstartAngle*(1-v)+fendAngle*v);
    }
	} else {
	  x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tLine* tRevolvedSurface::axis(void)
{
  setElementLocked;
  return faxis;
}
//-----------------------------------------------------------------------------

tCurve* tRevolvedSurface::refCurve(void)
{
  setElementLocked;
  return frefCurve;
}
//-----------------------------------------------------------------------------

void tRevolvedSurface::setAxis(tElement* a)
{
  setElementLocked;
	if (faxis) faxis->removeDependent(this);
  faxis = dynamic_cast<tLine*>(a);
	if (faxis && !faxis->addDependent(this)){
    faxis = NULL;
  }
	invalidate(this);
}

//-----------------------------------------------------------------------------
void tRevolvedSurface::setRefCurve(tElement *el)
{
  setElementLocked;
  if (frefCurve) frefCurve->removeDependent(this);
  frefCurve = dynamic_cast<tCurve*>(el);
	if (frefCurve && !frefCurve->addDependent(this)){
    frefCurve = NULL;
  }
	invalidate(this);
}

//-----------------------------------------------------------------------------
void tRevolvedSurface::refresh(void)
{
	// es gibt nichts zu tun.
}

//-----------------------------------------------------------------------------

tReal tRevolvedSurface::startAngle(void)
{
  return fstartAngle;
}
//-----------------------------------------------------------------------------

tReal tRevolvedSurface::endAngle(void)
{
  return fendAngle;
}
//-----------------------------------------------------------------------------

void tRevolvedSurface::setStartAngle(tReal alpha)
{
  setElementLocked;
  fstartAngle = alpha;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tRevolvedSurface::setEndAngle(tReal alpha)
{
  setElementLocked;
  fendAngle = alpha;
  invalidate(this);
}
//-----------------------------------------------------------------------------

