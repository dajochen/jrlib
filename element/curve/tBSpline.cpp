#include "element/curve/tBSpline.h"
#include "classes/tSolve.h"
#include "classes/utils.h"
#include "element/point/tPoint.h"

tBSpline::tBSpline(void *theOwner): tCurve(theOwner)
{
//  vertex.append(new tPoint(NULL, 0,0,0));
//  vertex.append(new tPoint(NULL, 0,1,0));
//  vertex.append(new tPoint(NULL, 1,1,0));
//  vertex.append(new tPoint(NULL, 1,0,0));
}
//-----------------------------------------------------------------------------
tBSpline::~tBSpline()
{
  removeAllVertices();
}
//-----------------------------------------------------------------------------

bool tBSpline::addVortex(tDot *P)
{
  setElementLocked
  if (P->addDependent(this)){
  	vertex.append(P);
	  invalidate(this);
	  return true;
  } else {
  	return false;
  }
}
//-----------------------------------------------------------------------------

void tBSpline::addVertices(tGroup *Group)
// Die Elemente der Gruppe werden dem Spline hinzugefuegt. Aendert sich die Gruppe hat dies keine Auswirkungen auf den Spline.
{
  setElementLocked
  tDot* P;
  tGroup *G;
  int i;
  for (i=0;i<Group->nElements();i++){
    P = dynamic_cast<tDot*>(Group->element(i));
    G = dynamic_cast<tGroup*>(Group->element(i));
    if (P){
      if (P->addDependent(this)){
        vertex.append(P);
      }
    } else if (G){
      addVertices(G);
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tBSpline::addVertices(tList<tElement*> *List)
{
  setElementLocked
  tDot* P;
  tGroup *G;
  int i;
  for (i=0;i<List->count();i++){
    P = dynamic_cast<tDot*>(List->at(i));
    G = dynamic_cast<tGroup*>(List->at(i));
    if (P){
      if (P->addDependent(this)){
        vertex.append(P);
      }
    } else if (G){
      addVertices(G);
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

tList<tElement*> tBSpline::vertices(void)
{
  tList<tElement*> l;
  int i;
  for (i=0;i<vertex.count();i++){
    l.append(vertex.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tBSpline::setVertices(tList<tElement*> list)
{
  setElementLocked;
  removeAllVertices();
  addVertices(&list);
}
//-----------------------------------------------------------------------------

void tBSpline::removeAllVertices(void)
{
  setElementLocked
	int i,ni;
  ni = vertex.count();
  for (i=0;i<ni;i++){
    vertex.at(i)->removeDependent(this);
  }
  vertex.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tBSpline::intrface(void){
	if (iface == NULL){
		iface = new iBSpline(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tBSpline::vectorAtAccurate(tReal t)
{
  setElementLocked
  update();
  tVector x;

  if (vertex.count()){
    int index, iMax;
    iMax = vertex.count();
    t = t*(double)(iMax+1);
    index = floor(t);
    t = t-index;
    float it = 1.0f-t;  // the t value inverted

    // calculate blending functions for cubic bspline
    float b0 = it*it*it/6.0f;
    float b1 = (3*t*t*t - 6*t*t +4)/6.0f;
    float b2 = (-3*t*t*t +3*t*t + 3*t + 1)/6.0f;
    float b3 =  t*t*t/6.0f;

    // calculate the x,y and z of the curve point
    x =   vertex.at(max(min(index-2,  iMax-1),0))->vector()*b0
        + vertex.at(max(min(index-1,iMax-1),0))->vector()*b1
        + vertex.at(max(min(index  ,iMax-1),0))->vector()*b2
        + vertex.at(max(min(index+1,iMax-1),0))->vector()*b3;
  } else {
    x.setZero();
  }
	return x;

}
//-----------------------------------------------------------------------------
/*
tVector tBSpline::vectorAt(int section, tReal fraction)
{
	tVector x;

	update();

	return x;
}
//-----------------------------------------------------------------------------
*/
/*
tVector tBSpline::gradientAt(tReal t)
{
	tVector x;
	update();
	// !!!! Gradient berechnen.
	return x;
}
//-----------------------------------------------------------------------------

tVector tBSpline::curvatureAt(tReal t)
{
	tVector x;
	update();
	// !!!! Kr�mmung berechnen.
	return x;
}
//-----------------------------------------------------------------------------

tReal tBSpline::getSFromT(tReal t)
{
	// !!!! Umrechnung !!!!
	return 0.;
}
//-----------------------------------------------------------------------------

tReal tBSpline::getTFromS(tReal l)
{
	// !!!! Umrechnung !!!!
	return 0.;
}
//-----------------------------------------------------------------------------

tReal tBSpline::length(void)
{
	update();
	// !!!! Umrechnung !!!!
	return 0.;
}
*/
//-----------------------------------------------------------------------------
/*
tVector tBSpline::xMin(void)
{
	tVector x,x1;
	int i,ni;

	if (!isValid){
		update();
	}

	if (iface){
		iface->getPropertyValue("2nd Resolution",jrInt,&ni);
	} else {
		ni = 10;
	}
	ni *= vortex.count()-1;
	x = *vortex.at(0);
	for (i=1;i<=ni;i++){
		x1 = vectorAt((tReal)i/(tReal)ni);

		x.x = (((x.x) < (x1.x)) ? (x.x) : (x1.x));
		x.x = min(x.x,x1.x);
		x.y = min(x.y,x1.y);
		x.z = min(x.z,x1.z);
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tBSpline::xMax(void)
{
	tVector x,x1;
	int i,ni;

	if (!isValid){
		update();
	}
	if (iface){
		iface->getPropertyValue("2nd Resolution",jrInt,&ni);
	} else {
		ni = 10;
	}
	ni *= vortex.count()-1;
	x = *vortex.at(0);
	for (i=1;i<=ni;i++){
		x1 = vectorAt((tReal)i/(tReal)ni);
		x.x = max(x.x,x1.x);
		x.y = max(x.y,x1.y);
		x.z = max(x.z,x1.z);
	}
	return x;
}
*/
//-----------------------------------------------------------------------------

void tBSpline::refresh(void)
{
}
//-----------------------------------------------------------------------------
