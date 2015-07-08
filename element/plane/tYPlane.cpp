#include "element/plane/tYPlane.h"

tYPlane::tYPlane(void* theOwner):tBasicPlane(theOwner)
{
    fcenter = tVector(0.,0.,0.);
    fnormal = tVector(0.,1.,0.);
    fHorizontalDir = tVector(0.,0.,1.);
}
//-----------------------------------------------------------------------------

tYPlane::~tYPlane()
{
}
//-----------------------------------------------------------------------------

iElement* tYPlane::intrface(void)
{
  if (!iface) iface = new iYPlane(this);
  return iface;
}

//-----------------------------------------------------------------------------
