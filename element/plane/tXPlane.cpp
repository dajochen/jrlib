#include "element/plane/tXPlane.h"

tXPlane::tXPlane(void* theOwner):tBasicPlane(theOwner)
{
    fcenter = tVector(0.,0.,0.);
    fnormal = tVector(1.,0.,0.);
    fHorizontalDir = tVector(0.,1.,0.);
}
//-----------------------------------------------------------------------------

tXPlane::~tXPlane()
{
}
//-----------------------------------------------------------------------------

iElement* tXPlane::intrface(void)
{
  if (!iface) iface = new iXPlane(this);
  return iface;
}
//-----------------------------------------------------------------------------

