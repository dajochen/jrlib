#include "element/curve/tTransformedDotListCurve.h"

#include "element/point/tPoint.h"
#include "classes/utils.h"

tTransformedDotListCurve::tTransformedDotListCurve(void *theOwner): tDotListCurve(theOwner)
{
  shift_ = tVector (0,0,0);
  axis_ = NULL;
  alpha_ = 0.;
  dlc_ = NULL;
}
//-----------------------------------------------------------------------------
tTransformedDotListCurve::~tTransformedDotListCurve()
{
  setAxis(NULL);
  setReferenceCurve(NULL);
}
//-----------------------------------------------------------------------------

iElement* tTransformedDotListCurve::intrface(void){
	if (iface == NULL){
		iface = new iTransformedDotListCurve(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tTransformedDotListCurve::transformed(tVector x)
{
  setElementLocked
  if (alpha_!=0. && axis_){
    tVector x0 = axis_->vectorAt(0.),
            x1 = axis_->vectorAt(1.);
    x = x.rotate(x0 ,x1-x0,alpha_);
  }
  x = x + shift_;
  return x;
}

//-----------------------------------------------------------------------------

tVector tTransformedDotListCurve::vectorAtAccurate(tReal t)
{
  setElementLocked
  update();
  if (dlc_){
    return transformed(dlc_->vectorAtAccurate(t));
  } else {
    return tVector(0,0,0);
  }
}
//-----------------------------------------------------------------------------

void tTransformedDotListCurve::refresh(void)
{
  setElementLocked
  //removeAllVertices();
  for (int i=0;i<vertices_.count();i++){
    vertices_.at(i)->removeDependent(this);
  }
  vertices_.clear();


  if (dlc_){
    for (int i=0;i<dlc_->nVertices(); i++){
      tDot *d = dlc_->vertex(i);
      if (d){
        tVector x = d->vector();
        tDot *d =  new tPoint(NULL, transformed(x));
        vertices_.append(d);
        d->addDependent(this);
      }
    }
  }
}
//-----------------------------------------------------------------------------

void tTransformedDotListCurve::setAxis (tElement* axis)
{
  setElementLocked
  if (axis_){
    axis_->removeDependent(this);
  }
  axis_= dynamic_cast<tLine*>(axis);
  if (axis_){
    axis_->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tTransformedDotListCurve::setReferenceCurve (tElement* dlc){
  setElementLocked;
  if (dlc_){
    dlc_->removeDependent(this);
  }
  dlc_=dynamic_cast<tDotListCurve*>(dlc);
  if (dlc_){
    dlc_->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------
