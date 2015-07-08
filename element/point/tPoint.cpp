#include "element/point/tPoint.h"

tPoint::tPoint(void *theOwner, tVector xx): tDot(theOwner)
{
	setVector(xx);
}
//-----------------------------------------------------------------------------

tPoint::tPoint(void *theOwner, tReal x, tReal y, tReal z): tDot(theOwner)
{
	setVector(tVector(x,y,z));
}
//-----------------------------------------------------------------------------

tPoint::~tPoint()
{
}
//-----------------------------------------------------------------------------

void tPoint::setX(tReal xx){
  setElementLocked
	X.x = xx;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPoint::setY(tReal yy){
  setElementLocked
	X.y = yy;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPoint::setZ(tReal zz){
  setElementLocked
	X.z = zz;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPoint::setVector(tVector xx){
  setElementLocked
	X = xx;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tPoint::refresh(){
	// gibt nichts zu tun.
}
//-----------------------------------------------------------------------------

iElement* tPoint::intrface(void){
	if (iface == NULL){
		iface = new iPoint(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
