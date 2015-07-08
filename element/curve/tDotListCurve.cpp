/*
 * tDotListCurve.cpp
 *
 *  Created on: 24.02.2012
 *      Author: hundemj
 */

#include "element/curve/tDotListCurve.h"

tDotListCurve::tDotListCurve(void *theOwner)
: tCurve(theOwner)
{
}

tDotListCurve::~tDotListCurve()
{
  removeAllVertices();
}
//-----------------------------------------------------------------------------

tList<tElement*> tDotListCurve::vertices(void)
{
  tList<tElement*> l;
  int i;
  update();
  for (i=0;i<vertices_.count();i++){
    l.append(vertices_.at(i));
//    tVector x0, x1;
//    x0 = vertices_.at(i)->vector();
//    double f = i/(vertices_.count()-1);
//    x1 = vectorAtAccurate(f);
//    f = 0.;
  }
  return l;
}
//-----------------------------------------------------------------------------

void tDotListCurve::removeAllVertices()
{
  setElementLocked
  int i;
  for (i=0;i<vertices_.count();i++){
    vertices_.at(i)->removeDependent(this);
  }
  vertices_.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

