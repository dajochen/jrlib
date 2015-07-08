#include "element/point/tDot.h"
#include "iDot.h"

tDot::tDot(void *theOwner):tElement(theOwner)
{
}
//-----------------------------------------------------------------------------

tDot::~tDot()
{
}
//-----------------------------------------------------------------------------

tVector tDot::xMin(void)
{
  setElementLocked
  update();
	return X;
}
//-----------------------------------------------------------------------------

tVector tDot::xMax(void)
{
  setElementLocked
  update();
	return X;	
}
//-----------------------------------------------------------------------------

tReal tDot::x(void)
{
  setElementLocked
  update();
  return X.x;
}
//-----------------------------------------------------------------------------

tReal tDot::y(void)
{
  setElementLocked
  update(); 
  return X.y;
}
//-----------------------------------------------------------------------------

tReal tDot::z(void)
{
  setElementLocked
  update();
  return X.z;
}
//-----------------------------------------------------------------------------

tVector tDot::vector(void)
{
  setElementLocked
  update(); 
  return X;
}
//-----------------------------------------------------------------------------

