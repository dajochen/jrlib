/*
 * tOffsetCurve.cpp
 *
 *  Created on: 16.07.2010
 *      Author: Jochen
 */

#include "element/curve/tOffsetCurve.h"

tOffsetCurve::tOffsetCurve(void *theOwner) : tCurve(theOwner)
{
  refSnake = NULL;
  fOffset = 0.;
}
//-----------------------------------------------------------------------------

tOffsetCurve::~tOffsetCurve()
{
  if (refSnake){removeDependent(refSnake);};
}
//-----------------------------------------------------------------------------

iElement* tOffsetCurve::intrface(void)
{
  if (iface == NULL){
    iface = new iOffsetCurve(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tOffsetCurve::refresh(void)
{
  // Es gibt eigentlich nichts neues zu tun...
}
//-----------------------------------------------------------------------------

tVector tOffsetCurve::vectorAtAccurate(tReal t)
{
  tReal u,v;
  if (refSnake && refSnake->reference()){
    refSnake->uvPosition(t,&u,&v);
    return refSnake->vectorAt(t) + refSnake->reference()->normalVectorAt(u,v)*fOffset;
  } else {
    return tVector(0,0,0);
  }
}
//-----------------------------------------------------------------------------

void tOffsetCurve::setReferenceSnake(tElement *el)
{
  tSnake *s;
  s = dynamic_cast<tSnake*>(el);
  if (refSnake){refSnake->removeDependent(this);};
  if (s->addDependent(this)){
    refSnake = s;
  } else {
    refSnake = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------
