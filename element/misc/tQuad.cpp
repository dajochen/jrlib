#include "element/misc/tQuad.h"

#include "classes/utils.h"

tQuad::tQuad(void *theowner) : tElement(theowner)
{
  fC[0] = NULL;
  fC[1] = NULL;
  fC[2] = NULL;
  fC[3] = NULL;
}
//-----------------------------------------------------------------------------

tQuad::~tQuad()
{
	setCorner(0,NULL);
	setCorner(1,NULL);
	setCorner(2,NULL);
	setCorner(3,NULL);
}
//-----------------------------------------------------------------------------

void tQuad::refresh(void)
{
  setElementLocked
  if (fC[0] && fC[1] && fC[2] && fC[3]){
    tVector fC0, fC1, fC2, fC3;
    fC0 = fC[0]->vector();
    fC1 = fC[1]->vector();
    fC2 = fC[2]->vector();
    fC3 = fC[3]->vector();
/*    s1 = fC[2]->vector()-fC[1]->vector();
    s2 = fC[0]->vector()-fC[1]->vector();
    t1 = fC[0]->vector()-fC[3]->vector();
    t2 = fC[2]->vector()-fC[3]->vector();*/
    farea = (((fC2-fC1)%(fC0-fC1)).length()+((fC0-fC3)%(fC2-fC3)).length())*0.5;

    fsize = farea*4/((fC0-fC3).length()+
                     (fC3-fC2).length()+
                     (fC2-fC1).length()+
                     (fC1-fC0).length());

    fdiameter = max((fC0-fC2).length(),(fC3-fC1).length());

    fcenter = (fC1+fC2+fC3+fC0)*0.25;

    fnormalVector = (fC3-fC1)%(fC0-fC2);
    if (fnormalVector.length() > 0) {
      fnormalVector = fnormalVector*(-1./fnormalVector.length());
      double l;
      tVector t1, t2;
      t1 = c1()->vector()-c3()->vector();
      t2 = c2()->vector()-c4()->vector();
      l = sqrt(min(t1.length_squared(),t2.length_squared()));
      t1 = (c1()->vector()+c3()->vector())*0.5;
      t2 = (c2()->vector()+c4()->vector())*0.5;
      ftwistiness = fabs(fnormalVector*(t2-t1))/l;
    } else {
      fnormalVector.setZero();
      ftwistiness = 0.;
    }
  } else {
    farea = 0.;
    fdiameter = 0.;
    fsize = 0.;
    fnormalVector.setZero();
    fcenter.setZero();
  }
}
//-----------------------------------------------------------------------------

iElement* tQuad::intrface(void)
{
  if (iface == NULL){
    iface = new iQuad(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

tVector tQuad::minVector(tVector x1, tVector x2)
{
  tVector x;
  x.x = min(x1.x, x2.x);
  x.y = min(x1.y, x2.y);
  x.z = min(x1.z, x2.z);
  return x;
}
//-----------------------------------------------------------------------------

tVector tQuad::maxVector(tVector x1, tVector x2)
{
  tVector x;
  x.x = max(x1.x, x2.x);
  x.y = max(x1.y, x2.y);
  x.z = max(x1.z, x2.z);
  return x;
}
//-----------------------------------------------------------------------------

tVector tQuad::xMin(void)
{
  setElementLocked
  tVector x;
  if (fC[0] && fC[1] && fC[2] && fC[3]){
    x = minVector(fC[0]->vector(), fC[1]->vector());
    x = minVector(fC[2]->vector(), x);
    x = minVector(fC[3]->vector(), x);
  } else {
    x.setZero();
  }
  return x;
}
//-----------------------------------------------------------------------------

tVector tQuad::xMax(void)
{
  setElementLocked
  tVector x;
  if (fC[0] && fC[1] && fC[2] && fC[3]){
    x = maxVector(fC[0]->vector(), fC[1]->vector());
    x = maxVector(fC[2]->vector(), x);
    x = maxVector(fC[3]->vector(), x);
  } else {
    x.setZero();
  }
  return x;
}
//-----------------------------------------------------------------------------

tDot* tQuad::c(int index)
{
  setElementLocked
  update();
  index = index%4;
  if (index == 1){
    return fC[1];
  } else if (index == 2){
    return fC[2];
  } else if (index == 3){
    return fC[3];
  } else {
    return fC[0];
  }
}
//-----------------------------------------------------------------------------

void tQuad::defineQuad(tElement *C1,tElement *C2, tElement *C3,tElement *C4)
{
  setElementLocked
  setCorner(1,C1);
  setCorner(2,C2);
  setCorner(3,C3);
  setCorner(0,C4);
}

tList<tElement *> tQuad::corners()
{
    tList<tElement*> c;
    c.append(fC[0]);
    c.append(fC[1]);
    c.append(fC[2]);
    c.append(fC[3]);
    return c;
}

void tQuad::setCorners(const tList<tElement *>& c)
{
    for (int i=0; i<4 && i<c.count(); i++) {
        setCorner(i, c.at(i));
    }
}
//-----------------------------------------------------------------------------

void tQuad::setCorner(int index, tElement *c)
{
  setElementLocked
  tDot *dot;
  index = index%4;
  if (fC[index]){
    fC[index]->removeDependent(this);
  }
  dot = dynamic_cast<tDot*>(c);
  if (dot && dot->addDependent(this)){
    fC[index] = dot;
  }
  invalidate(this);
}

//-----------------------------------------------------------------------------

