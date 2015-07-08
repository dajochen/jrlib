#include "element/curve/tLine.h"

#include "classes/utils.h"

tLine::tLine(void *theOwner,tElement *C1, tElement *C2): tCurve(theOwner)
{
	c1 = NULL;
	c2 = NULL;
	setVertices(C1, C2);
}
//-----------------------------------------------------------------------------

tLine::~tLine()
{
	if (c1)
		c1->removeDependent(this);
	if (c2)
		c2->removeDependent(this);
}
//-----------------------------------------------------------------------------
/*
tList<tElement*>& tLine::usedElements(void)
{
	tList<tElement*> L;
	if (c1) L.append(c1);
	if (c2) L.append(c2);
	return L;
}
//-----------------------------------------------------------------------------
*/
iElement* tLine::intrface(void){
	if (iface == NULL){
		iface = new iLine(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

void tLine::setStart(tElement *el)
{
  setElementLocked
  if (c1){
    c1->removeDependent(this);
    c1 = NULL;
  }
  tDot* d = dynamic_cast<tDot*>(el);
  if (d && d->addDependent(this)){
    c1 = d;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tLine::setEnd(tElement *el)
{
  setElementLocked
  if (c2){
    c2->removeDependent(this);
    c2 = NULL;
  }
  tDot* d = dynamic_cast<tDot*>(el);
  if (d && d->addDependent(this)){
    c2 = d;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tLine::setVortex(int i, tElement *el)
{
  setElementLocked
	if (i==0){
    setStart(el);
  } else {
    setEnd(el);
  }
}
//-----------------------------------------------------------------------------

void tLine::setVertices(tElement *C1, tElement *C2)
{
  setElementLocked
	setStart(C1);
	setEnd(C2);
}
//-----------------------------------------------------------------------------

tVector tLine::vectorAtAccurate(tReal t)
{
  setElementLocked
	tVector x;

  update();
	if (c1 && c2){
		x = (tVector)(*c1)*(1.-t)+(tVector)(*c2)*t;
	} else if (c1){
		x = c1->vector();
	} else if (c2){
		x = c2->vector();
	} else {
    x.setZero();
  }
	return x;
}
//-----------------------------------------------------------------------------

tVector tLine::gradientAt(tReal /*t*/)
{
  setElementLocked
  tVector dx;

  update();
  if (c2 && c1){
    dx = (tVector)*c2-(tVector)*c1;
  } else {
    dx.setZero();
  }
	return dx;
}
//-----------------------------------------------------------------------------

tVector tLine::curvatureAt(tReal /*t*/)
{
  setElementLocked
  update();
	return tVector(0.,0.,0.);
}
//-----------------------------------------------------------------------------

//tReal tLine::getSFromT(tReal t)
//{
//  setElementLocked
//	update();
//	return t;
//}
////-----------------------------------------------------------------------------
//
//tReal tLine::getTFromS(tReal s)
//{
//  setElementLocked
//	update();
//	return s;
//}
////-----------------------------------------------------------------------------

tReal tLine::length(void)
{
  setElementLocked
  update();
	if (c1 && c2){
		return (c1->vector()-c2->vector()).length();
	} else {
		return 0.;
	}
}
//-----------------------------------------------------------------------------

tVector tLine::xMin(void)
{
  setElementLocked
	tVector x;
	x.setZero();
  update();
	if (c1 && c2){
		x.x = min(c1->x(),c2->x());
		x.y = min(c1->y(),c2->y());
		x.z = min(c1->z(),c2->z());
	} else if (c1){
		x = c1->vector();
	} else if (c2){
		x = c2->vector();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tLine::xMax(void)
{
  setElementLocked
	tVector x;
	x.setZero();
  update();
	if (c1 && c2){
		x.x = max(c1->x(),c2->x());
		x.y = max(c1->y(),c2->y());
		x.z = max(c1->z(),c2->z());
	}else if (c1){
		x = c1->vector();
	} else if (c2){
		x = c2->vector();
	}
	return x;
}
//-----------------------------------------------------------------------------

void tLine::refresh(void)
{
	// es gibt nichts zu tun...
}
//-----------------------------------------------------------------------------
