#include "element/point/tAbsBead.h"

tAbsBead::tAbsBead(void *theOwner,tElement *CURVE, tReal POS):tDot(theOwner)
{
  curve = NULL;
  setPosition(POS);
  setReference(CURVE);
}
//-----------------------------------------------------------------------------

tAbsBead::~tAbsBead()
{
	if (curve)
		curve->removeDependent(this);
}
//-----------------------------------------------------------------------------
/*
tList<tElement*> tAbsBead::usedElements(void)
{
	tList<tElement*> L;
	L.append(curve);
	return L;
} */
//-----------------------------------------------------------------------------

void tAbsBead::refresh(void){

  if (curve){
	  X = curve->vectorAt(pos);
  } else {
    X.setZero();
  }
}
//-----------------------------------------------------------------------------

tReal tAbsBead::position(void){
  setElementLocked
	return pos;
}
//-----------------------------------------------------------------------------

void tAbsBead::setPosition(tReal POS){

  setElementLocked

	pos = POS;
	invalidate(this);
}
//-----------------------------------------------------------------------------

tCurve* tAbsBead::reference(void)
{
  setElementLocked;

	return curve;
}
//-----------------------------------------------------------------------------

void tAbsBead::setReference(tElement *el)
{
  setElementLocked;

	if (curve){
		curve->removeDependent(this);
  }
  curve = dynamic_cast<tCurve*>(el);
	if (curve && !curve->addDependent(this)){
    curve = NULL;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tAbsBead::intrface(void)
{
	if (iface == NULL){
		iface = new iAbsBead(this);
	}
	return iface;
}
