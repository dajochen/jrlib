#include "element/plane/tZPlane.h"

tZPlane::tZPlane(void* theOwner):tBasicPlane(theOwner)
{
  fcenter = tVector(0.,0.,0.);
  fnormal = tVector(0.,0.,1.);
  fHorizontalDir = tVector(0.,1.,0.);
}
//-----------------------------------------------------------------------------

tZPlane::~tZPlane()
{
}
//-----------------------------------------------------------------------------

iElement* tZPlane::intrface(void)
{
  if (!iface) iface = new iZPlane(this);
  return iface;
}
//-----------------------------------------------------------------------------
