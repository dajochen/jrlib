#include "element/surface/tRotatedSurface.h"

tRotatedSurface::tRotatedSurface(void *theOwner): tSurface(theOwner)
{
	faxis = NULL;
	frefSurface = NULL;
	fangle = 0;
}
//-----------------------------------------------------------------------------

tRotatedSurface::tRotatedSurface(void *theOwner, tSurface *surf, tLine *a, tReal phi): tSurface(theOwner)
{
	faxis = NULL;
	frefSurface = NULL;
	fangle = phi;
	setRefSurface(surf);
	setAxis(a);
}

//-----------------------------------------------------------------------------
tRotatedSurface::~tRotatedSurface()
{
	if (faxis) faxis->removeDependent(this);
	if (frefSurface) frefSurface->removeDependent(this);
}
//-----------------------------------------------------------------------------
/*
tList<tElement*> tRotatedSurface::usedElements(void)
{
	tList<tElement*> L;
	if (axis) L.append(axis);
	if (refSurface) L.append(refSurface);
	return L;
}*/
//-----------------------------------------------------------------------------

iElement* tRotatedSurface::intrface(void)
{
	if (iface == NULL){
		iface = new iRotatedSurface(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tRotatedSurface::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked
	update();
	tVector x,x0,x1;
	if (faxis && frefSurface){
    x = frefSurface->vectorAt(u,v);
    if (faxis->length()>0){
      x0 = *faxis->start();
      x1 = ((tVector)*faxis->end())-x0;
    } else {
      // Wenn keine Rotationsachse vorhanden ist, wird die x-Achse verwendet.
      x0.setZero();
      x1.setZero();
      x1.x = 1.;
    }
    x = x.rotate(x0,x1,fangle);
	} else {
	  x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tRotatedSurface::normalVectorAt(tReal u, tReal v)
{
  setElementLocked
	update();
	tVector n,x0,x1;
	if (faxis && frefSurface){
    n = frefSurface->normalVectorAt(u,v);
    if (faxis->length()>0){
      x0 = *faxis->start();
      x1 = ((tVector)*faxis->end())-x0;
    } else {
      // Wenn keine Rotationsachse vorhanden ist, wird die x-Achse verwendet.
      x0.setZero();
      x1.setZero();
      x1.x = 1.;
    }
    n = n.rotate(x0,x1,fangle);
	} else {
	  n.setZero();
	}
	return n;
}
//-----------------------------------------------------------------------------

void tRotatedSurface::setAxis(tElement *el)
{
  setElementLocked
	if (faxis) faxis->removeDependent(this);
  faxis = dynamic_cast<tLine*>(el);
	if (faxis && !faxis->addDependent(this)){
	 faxis = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRotatedSurface::setRefSurface(tElement *el)
{
  setElementLocked
	if (frefSurface) frefSurface->removeDependent(this);
  frefSurface = dynamic_cast<tSurface*>(el);
	if (frefSurface && !frefSurface->addDependent(this)){
    frefSurface = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRotatedSurface::setAngle(tReal alpha)
{
  setElementLocked
  fangle = alpha;
  invalidate(this);
}

//-----------------------------------------------------------------------------
void tRotatedSurface::refresh(void)
{
	// es gibt nichts zu tun.
}

//-----------------------------------------------------------------------------
