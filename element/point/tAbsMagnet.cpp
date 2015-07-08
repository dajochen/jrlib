#include "element/point/tAbsMagnet.h"

//-----------------------------------------------------------------------------
tAbsMagnet::tAbsMagnet(void *theOwner, tElement *surf, tReal U, tReal V):tDot(theOwner)
{
  surface = NULL;
  setPosition(U,V);
	setReference(surf);
}
//-----------------------------------------------------------------------------

tAbsMagnet::~tAbsMagnet()
{
	if (surface)
		surface->removeDependent(this);
}
//-----------------------------------------------------------------------------

void tAbsMagnet::refresh(void){
	if (surface){
		X = surface->vectorAt(u,v);
	} else {
		X.setZero();
	}
}
//-----------------------------------------------------------------------------

void tAbsMagnet::setPosition(tReal U,tReal V){
  setElementLocked
	u = U;
	v = V;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tAbsMagnet::setReference(tElement *newSurface)
{
  setElementLocked
	if (surface)
		surface->removeDependent(this);
	surface = dynamic_cast<tSurface*>(newSurface);
	if (surface && !surface->addDependent(this)){
    surface = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tAbsMagnet::intrface(void)
{
	if (iface == NULL){
		iface = new iAbsMagnet(this);
	}
	return iface;
}
