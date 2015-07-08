/*
 * tAbstractSpline.cpp
 *
 *  Created on: 24.02.2012
 *      Author: hundemj
 */

#include "tAbstractSpline.h"

tAbstractSpline::tAbstractSpline(void *theOwner, int maxVerts)
: tDotListCurve(theOwner),
  maxVertices(maxVerts)
{
}

tAbstractSpline::~tAbstractSpline()
{
}
//-----------------------------------------------------------------------------

void tAbstractSpline::addVertex(tElement *el)
{
  setElementLocked
  tDot *d;
  d = dynamic_cast<tDot*>(el);
  if (d && (maxVertices < 0 || vertices_.count() < maxVertices)){
    vertices_.append(d);
    el->addDependent(this);
    invalidate(this);
  }
}
//-----------------------------------------------------------------------------

void tAbstractSpline::addVertex(int index, tElement *el)
{
    setElementLocked
    tDot *d;
    d = dynamic_cast<tDot*>(el);
    if (d && (maxVertices < 0 || vertices_.count() < maxVertices)){
        index = std::max(index, 0);
        index = std::min(index, vertices_.count());
        vertices_.insert(index,d);
        el->addDependent(this);
        invalidate(this);
    }

}
//-----------------------------------------------------------------------------

void tAbstractSpline::addVertices(tList<tElement*> *List)
{
  setElementLocked
  int i;
  if (List){
    for (i=0;i<List->count();i++){
      addVertex(List->at(i));
    }
  }
}
//-----------------------------------------------------------------------------

void tAbstractSpline::setVertices(tList<tElement*> list)
{
  setElementLocked;
  removeAllVertices();
  addVertices(&list);
}
//-----------------------------------------------------------------------------

void tAbstractSpline::setVertices(tList<tDot*> list)
{
  setElementLocked;
  removeAllVertices();
  for (int i=0;i<list.count();i++){
    addVertex(list.at(i));
  }
}
//-----------------------------------------------------------------------------

void tAbstractSpline::removeAllVertices(void)
{
  tDotListCurve::removeAllVertices();
}
//-----------------------------------------------------------------------------

