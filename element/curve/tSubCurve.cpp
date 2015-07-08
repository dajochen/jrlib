#include "element/curve/tSubCurve.h"

tSubCurve::tSubCurve(void *theOwner): tCurve(theOwner)
{
	c1 = NULL;
	c2 = NULL;
}
//-----------------------------------------------------------------------------

tSubCurve::tSubCurve(void *theOwner,tAbsBead *C1, tAbsBead *C2): tCurve(theOwner)
{
	c1 = NULL;
	c2 = NULL;
	setVertices(C1, C2);
}
//-----------------------------------------------------------------------------

tSubCurve::~tSubCurve()
{
	if (c1)
		c1->removeDependent(this);
	if (c2)
		c2->removeDependent(this);
}
//-----------------------------------------------------------------------------

iElement* tSubCurve::intrface(void){
	if (iface == NULL){
		iface = new iSubCurve(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
void tSubCurve::setVertex(int i, tElement *El)
{
  setElementLocked
  tAbsBead *c;

  c = dynamic_cast<tAbsBead*>(El);
  if (c && c->addDependent(this)){
    if (i==0){
      if (c1 != NULL) c1->removeDependent(this);
      c1 = c;
    } else {
      if (c2 != NULL) c2->removeDependent(this);
      c2 = c;
    }
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------

void tSubCurve::setVertices(tElement *C1, tElement *C2)
{
  setElementLocked
	setVertex(0,C1);
	setVertex(1,C2);
}
//-----------------------------------------------------------------------------

tVector tSubCurve::vectorAtAccurate(tReal t)
{
  setElementLocked
  update();

  tCurve *ref = NULL;
  if (c1->reference() == c2->reference()){
    ref = c1->reference();
  }

  double pos = t*c2->position()+(1-t)*c1->position();

  tVector x(0,0,0);
  if (ref){
    x = ref->vectorAtAccurate(pos);
  }
  return x;
}
//-----------------------------------------------------------------------------

tVector tSubCurve::gradientAt(tReal t)
{
  setElementLocked
  update();

  tCurve *ref = NULL;
  if (c1->reference() == c2->reference()){
    ref = c1->reference();
  }
  double start = c1->position(),
         end=c2->position();

  double pos = t*end+(1-t)*start;

  tVector x(0,0,0);
  if (ref){
    x = ref->gradientAt(pos);
  }
  if (end < start){
    x = x * (-1.);
  }
  return x;
}
//-----------------------------------------------------------------------------
/*
tVector tSubCurve::curvatureAt(tReal t)
{
  setElementLocked

	update();

	tCurve *ref = NULL;
	if (c1->reference() == c2->reference()){
	  ref = c1->reference();
	}

	double pos = t*c2->position()+(1-t)*c1->position();

	tVector x(0,0,0);
	if (ref){
	  x = ref->curvatureAt(pos);
	}

	return x;
}*/
//-----------------------------------------------------------------------------

//tReal tSubCurve::getSFromT(tReal t)
//{
//  setElementLocked
//	tReal s,s1,s2;
//	update();
//
//	if (c1 && c2 && c1->reference() && c2->reference()){
//		s1 = c1->reference()->getSFromT(c1->position());
//		s2 = c2->reference()->getSFromT(c2->position());
//		s = c1->reference()->getSFromT(t);
//		s = (s-s1)/(s2-s1);
//	} else if (c1 && c1->reference()){
//		return c1->position();
//	} else if (c2 && c2->reference()){
//		return c2->position();
//	} else {
//		return 0.;
//	}
//
//	return s;
//}
////-----------------------------------------------------------------------------
//
//tReal tSubCurve::getTFromS(tReal s)
//{
//  setElementLocked
//	tReal t,t1,t2,s1,s2;
//
//	update();
//	if (c1 && c2 && c1->reference() && c2->reference()){
//		s1 = c1->reference()->getSFromT(c1->position());
//		s2 = c2->reference()->getSFromT(c2->position());
//		t1 = c1->position();
//		t2 = c2->position();
//
//		s = s*s2+(1-s)*s1;
//		t = c1->reference()->getTFromS(s);
//		t = (t-t1)/(t2-t1);
//		return t;
//	} else if (c1 && c1->reference()){
//		return c1->reference()->getSFromT(c1->position());
//	} else if (c2 && c2->reference()){
//		return c2->reference()->getSFromT(c2->position());
//	} else {
//		return 0.;
//	}
//}
////-----------------------------------------------------------------------------
//tReal tSubCurve::length(void)
//{
//  setElementLocked
//	tReal s1,s2;
//	update();
//	if (c1 && c2){
//		s1 = c1->reference()->getSFromT(c1->position());
//		s2 = c2->reference()->getSFromT(c2->position());
//		return fabs((s2-s1)*c1->reference()->length());
//	} else {
//		return 0.;
//	}
//}
//-----------------------------------------------------------------------------

void tSubCurve::refresh(void)
{
	// es gibt nichts zu tun...
}
//-----------------------------------------------------------------------------
