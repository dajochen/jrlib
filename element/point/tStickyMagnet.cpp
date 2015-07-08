/*
 * tStickyMagnet.cpp
 *
 *  Created on: 19 Feb 2012
 *      Author: jochen
 */

#include "element/point/tStickyMagnet.h"
#include <limits>


OF_StickyMagnet::OF_StickyMagnet(tSurface *f, tVector refPoint)
{
  f_ = f;
  refPoint_ = refPoint;

}
//-----------------------------------------------------------------------------

double OF_StickyMagnet::evaluate (double uv[2]) const
{
  double rr;
  if (f_){
    tVector delta = f_->vectorAt(uv[0],uv[1])-refPoint_;
    rr = delta.length_squared();
    return rr;
  } else {
    return std::numeric_limits<double>::max();
  }
}
//-----------------------------------------------------------------------------


tStickyMagnet::tStickyMagnet(void *theOwner)
 : tMagnet(theOwner)
{
  selectedFace = NULL;
  refDot = NULL;
  refFaces = NULL;
  u = 0.;
  v = 0.;
  refDotLocation.setZero();
}
//-----------------------------------------------------------------------------

tStickyMagnet::~tStickyMagnet()
{
  setStickyFaces(NULL);
  //clearFaces();
}
//-----------------------------------------------------------------------------

iElement* tStickyMagnet::intrface(void){
  if (iface == NULL){
    iface = new iStickyMagnet(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tStickyMagnet::refresh(void){
  tSurface *currentFace = NULL;
  selectedFace = NULL;

  //double small = 1e-3;

  //double u,v;

  if (refDot && refFaces->nElements()>0){

    refDotLocation = refDot->vector();
  //  double minDist = std::numeric_limits<double>::max();

    for (int i=0; i<refFaces->nElements(); i++){
      tSurface* face = dynamic_cast<tSurface*>(refFaces->element(i));
      if (face){
        int icount,ifault, numres;//, kcount, konvge;
        int n = 2;
        double reqmin,
              ynewlo,
              *start = new double[n],
              *step = new double[n],
              *xmin = new double[n];

        currentFace = face;

        start[0] = 0.5;
        start[1] =  0.5;


        step[0] = 0.1;
        step[1] = 0.1;

        reqmin = 1.0E-08;
  //      konvge = 10;
  //      kcount = 500;

        OF_StickyMagnet of(currentFace, refDotLocation);

        ynewlo = of.evaluate(start);

        nelderMeadMinimumSearch( of, n,
            start, xmin, step, &ynewlo, &icount, &numres, &ifault, reqmin);

        if (0 < xmin[0] && xmin[0]<1
            && 0 < xmin[1] && xmin[1]<1
            ){
     //     minDist = ynewlo;
          selectedFace = currentFace;
          u = xmin[0];
          v = xmin[1];
          i = refFaces->nElements();
        }
//        if (ynewlo < reqmin && selectedFace==currentFace){
//          i = refFaces->nElements();
//        }

        delete start;
        delete step;
        delete xmin;
      }
    }
  } else {
    u=0.2;
    v=0.5;
  }

  if (selectedFace){
    X = selectedFace->vectorAt(u,v);
  } else {
    X.setZero();
  }
}
//-----------------------------------------------------------------------------

//void tStickyMagnet::clearFaces(void)
//{
//  for (int i=0; i<refFaces.count(); i++){
//    if (refFaces.at(i)){
//      refFaces.at(i)->removeDependent(this);
//    }
//  }
//  invalidate(this);
//}
//-----------------------------------------------------------------------------

void tStickyMagnet::setReferenceDot(tElement *d)
{
  if (refDot){
    refDot->removeDependent(this);
  }
  refDot = dynamic_cast<tDot*>(d);
  if (refDot){
    refDot->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tStickyMagnet::setStickyFaces(tElement* faces)
{
  if (refFaces){
    refFaces->removeDependent(this);
  }
  refFaces = dynamic_cast<tGroup*>(faces);
  if (refFaces){
      refFaces->addDependent(this);
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------
