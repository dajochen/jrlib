#include "element/misc/tNetPoint.h"

tNetPoint::tNetPoint(void *theowner, tNet *net, tDot *refPoint) : tDot(theowner)
{
  fnet = NULL;
  setNet(net);
  setRefPoint(refPoint);
}
//-----------------------------------------------------------------------------

tNetPoint::~tNetPoint()
{
  setRefPoint(NULL);
  setNet(NULL);
}
//-----------------------------------------------------------------------------

void tNetPoint::refresh(void)
{
  X = fnet->getVector(this);
}
//-----------------------------------------------------------------------------

tNet* tNetPoint::net(void)
{
  setElementLocked 
  return fnet;
}
//-----------------------------------------------------------------------------
void tNetPoint::setNet(tElement* net)
{
  setElementLocked 
  if (fnet){
    fnet->setRefPoint(this,NULL);
    fnet->removeDependent(this);
  }
  fnet = dynamic_cast<tNet*>(net);
  if (fnet && !fnet->addDependent(this)){
    fnet = NULL;
  }
  invalidate(this); 
}
//-----------------------------------------------------------------------------
tDot* tNetPoint::refPoint(void)
{
  setElementLocked 
  if (fnet){
    return fnet->getRefPoint(this);
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------
void tNetPoint::setRefPoint(tElement* refPoint)
{
  setElementLocked 
  if (fnet){
    fnet->setRefPoint(this,refPoint);
  }
  invalidate(this);   
}
//-----------------------------------------------------------------------------

iElement* tNetPoint::intrface(void)
{
  if (iface == NULL){
    iface = new iNet(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
