#include "element/curve/snake/tLineSnake.h"

tLineSnake::tLineSnake(void *theOwner): tSnake(theOwner)
{
	m1 = NULL;
	m2 = NULL;
}
//-----------------------------------------------------------------------------

tLineSnake::tLineSnake(void *theOwner,tElement *M1, tElement *M2): tSnake(theOwner)
{
	m1 = NULL;
	m2 = NULL;
	setMagnets(M1, M2);
}
//-----------------------------------------------------------------------------

tLineSnake::~tLineSnake()
{
	if (m1)
		m1->removeDependent(this);
	if (m2)
		m2->removeDependent(this);
}
//-----------------------------------------------------------------------------

iElement* tLineSnake::intrface(void){
	if (iface == NULL){
		iface = new iLineSnake(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------
void tLineSnake::setMagnet(int i, tElement *e)
{
  setElementLocked
	tAbsMagnet *m;
	m = dynamic_cast<tAbsMagnet*>(e);
	if (i==0){
		if (m1 != NULL){
		  m1->removeDependent(this);
		}
		m1 = m;
	} else {
		if (m2 != NULL){
		  m2->removeDependent(this);
		}
		m2 = m;
	}
	if (m!=NULL){
	  m->addDependent(this);
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tLineSnake::setMagnets(tElement *M1, tElement *M2)
{
  setElementLocked
	setMagnet(0,M1);
	setMagnet(1,M2);
}
//-----------------------------------------------------------------------------

tVector tLineSnake::vectorAtAccurate(tReal t)
{
  setElementLocked
	tReal u,v;
	tVector x;

	update();
	if (m1 && m2 && m1->reference()== m2->reference() && m1->reference()){
		u = m1->uPosition()*(1-t)+m2->uPosition()*t;
		v = m1->vPosition()*(1-t)+m2->vPosition()*t;
		x = m1->reference()->vectorAt(u,v);
	} else {
	  x.setZero();
	}
	return x;
}

void tLineSnake::uvPosition(tReal t, tReal *u, tReal *v){
  setElementLocked

  update();
  if (m1 && m2 && m1->reference()== m2->reference()){
    *u = m1->uPosition()*(1-t)+m2->uPosition()*t;
    *v = m1->vPosition()*(1-t)+m2->vPosition()*t;
  } else {
    *u = 0.;
    *v = 0.;
  }
}
//-----------------------------------------------------------------------------

void tLineSnake::refresh(void)
{
	// es gibt nichts zu tun...
}
//-----------------------------------------------------------------------------

tSurface* tLineSnake::reference(void){
  if (m1 && m2 && m1->reference() == m1->reference()){
    return m1->reference();
  } else {
    return NULL;
  }
}
//-----------------------------------------------------------------------------
