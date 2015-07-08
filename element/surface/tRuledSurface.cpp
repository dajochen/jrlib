#include "element/surface/tRuledSurface.h"
#include "classes/utils.h"

tRuledSurface::tRuledSurface(void *theOwner): tSurface(theOwner)
{
	c1 = c2 = NULL;
}
//-----------------------------------------------------------------------------

tRuledSurface::tRuledSurface(void *theOwner, tCurve *C1, tCurve *C2): tSurface(theOwner)
{
	c1 = c2 = NULL;
	setCurves(C1,C2);
}

//-----------------------------------------------------------------------------
tRuledSurface::~tRuledSurface()
{
	if (c1){
		c1->removeDependent(this);
	}
	if (c2){
		c2->removeDependent(this);
	}
}
//-----------------------------------------------------------------------------

iElement* tRuledSurface::intrface(void)
{
	if (iface == NULL){
		iface = new iRuledSurface(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tRuledSurface::xMin(void)
{
  setElementLocked
	tVector x,x1,x2;
	if (c1 && c2){
		x1 = c1->xMin();
		x2 = c2->xMin();
		x.x = min(x1.x,x2.x);
		x.y = min(x1.y,x2.y);
		x.z = min(x1.z,x2.z);
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tRuledSurface::xMax(void)
{
  setElementLocked
	tVector x,x1,x2;
	if (c1 && c2){
		x1 = c1->xMax();
		x2 = c2->xMax();
		x.x = max(x1.x,x2.x);
		x.y = max(x1.y,x2.y);
		x.z = max(x1.z,x2.z);
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tRuledSurface::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked
	update();
	tVector x,x1,x2;
	if (c1 && c2){
		x1 = c1->vectorAt(u);
		x2 = c2->vectorAt(u);
		x = x1*(1.-v)+x2*v;
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tRuledSurface::normalVectorAt(tReal u, tReal v)
{
  setElementLocked
	update();
	tVector n,x1,x2,u_,v_;
	tReal l;
	if (c1 && c2){
		x1 = c1->vectorAt(u);
		x2 = c2->vectorAt(u);
		v_ = x2-x1;
		x1 = c1->gradientAt(u);
		x2 = c2->gradientAt(u);
		u_ = x1*(1.-v)+x2*v;
		n = u_%v_;
		l = n.length();
		if (l > 0.){
			n = n*(1./l);
		}
	} else {
		n.setZero();
	}
	return n;
}
//-----------------------------------------------------------------------------

void tRuledSurface::setCurve(int index, tElement* c)
{
  setElementLocked
  tCurve *CC;

	if (index == 0 && c1) c1->removeDependent(this);
	if (index != 0 && c2) c2->removeDependent(this);

	CC = dynamic_cast<tCurve*>(c);
	if (CC && CC->addDependent(this)){
    if (index == 0){
      c1 = CC;
    } else {
      c2 = CC;
    }
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRuledSurface::setCurves(tElement* C1, tElement *C2)
{
  setElementLocked
	if (c1) c1->removeDependent(this);
	if (c2) c2->removeDependent(this);
	c1 = dynamic_cast<tCurve*>(C1);
	if (c1 && !c1->addDependent(this)){
    c1 = NULL;
  }
  c2 = dynamic_cast<tCurve*>(C2);
  if (c2 && !c2->addDependent(this)){
    c2 = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

tList<tElement*> tRuledSurface::curves(void)
{
  tList<tElement*> list;
  list.append(c1);
  list.append(c2);
  return list;
}
//-----------------------------------------------------------------------------

void tRuledSurface::setCurves(tList<tElement*> l)
{
  if(l.count()>0){
    setCurve(0, l.at(0));
        //setCurve(0,l.at(0));
  }
  if(l.count()>1){
    setCurve(1,l.at(1));
  }
}
//-----------------------------------------------------------------------------

void tRuledSurface::refresh(void)
{
	// es gibt nichts zu tun.
}

//-----------------------------------------------------------------------------
