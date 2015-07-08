/*
 * tDistortedSpline.cpp
 *
 *  Created on: 28.02.2012
 *      Author: hundemj
 */

#include "element/curve/tDistortedSpline.h"

#include "element/point/tDot.h"
#include "element/point/tAbsMagnet.h"
#include "element/point/tStickyMagnet.h"
#include "element/surface/tSurface.h"
#include "element/curve/tHermiteSpline.h"

tDistortedSpline::tDistortedSpline(void *theOwner)
 : tDotListCurve(theOwner)
{
  fbaseSpline = NULL;
  fbaseFaces = NULL;
  fdistortedFaces = NULL;

  tHermiteSpline* hsp = new tHermiteSpline(this);
  hsp->setBias(1);
  hsp->setTension(1);
  hsp->setContinuity(1);
  fdistortedSpline = hsp;

}
//------------------------------------------------------------------------------------

tDistortedSpline::~tDistortedSpline()
{
  clear();
  fdistortedSpline->releaseOwner(this);
}
//------------------------------------------------------------------------------------

iElement* tDistortedSpline::intrface(void)
{
  if (iface == NULL){
    iface = new iDistortedSpline(this);
  }
  return iface;
}
//------------------------------------------------------------------------------------

void tDistortedSpline::invalidate(tElement *sender){
  tCurve::invalidate(sender);
}

void tDistortedSpline::refresh(void)
{
  if (fbaseSpline && fbaseFaces && fdistortedFaces) {
    if (fdistortedSpline){
        fdistortedSpline->update();
    }
    tList<tElement*> pInList = fbaseSpline->vertices();

    vertices_.clear();

    for (int i=0; i<pInList.count(); i++) {

      tDot* d = dynamic_cast<tDot*>(pInList.at(i));

      if (d) {
        tStickyMagnet* sMag = new tStickyMagnet(NULL);
        sMag->setReferenceDot(d);
        sMag->setStickyFaces(fbaseFaces);

        tSurface *stickyFace = sMag->reference(),
                 *distortedFace = NULL;

        double u = sMag->uPosition(),
               v = sMag->vPosition();

        // Verzerrtes "Ziel"-face ermitteln
        for (int j=0; j<fbaseFaces->nElements() && j<fdistortedFaces->nElements(); j++){
          if (fbaseFaces->element(j) == stickyFace){
            distortedFace = dynamic_cast<tSurface*>(fdistortedFaces->element(j));
            j = fbaseFaces->nElements();
          }
        }

        tAbsMagnet* aMag = dynamic_cast<tAbsMagnet*>(new tAbsMagnet(NULL));
        aMag->intrface()->setName(d->intrface()->name());
        aMag->setReference(distortedFace);
        aMag->setUPosition(u);
        aMag->setVPosition(v);

        vertices_.append(aMag);
      }
    }

    fdistortedSpline->setVertices(vertices_);

  }
}
//------------------------------------------------------------------------------------

tVector tDistortedSpline::vectorAtAccurate(tReal t)
{
  setElementLocked
  update();
  if (fdistortedSpline) {
    return fdistortedSpline->vectorAtAccurate(t);
  } else {
    return tVector(0,0,0);
  }
}
//------------------------------------------------------------------------------------

void tDistortedSpline::clear(void)
{
  setBaseSpline(NULL);
  setBaseFaces(NULL);
  setDistortedFaces(NULL);
}
//------------------------------------------------------------------------------------

void tDistortedSpline::setBaseSpline(tElement* spl)
{
  tAbstractSpline *base = dynamic_cast<tAbstractSpline*>(spl);
  if (fbaseSpline){
    fbaseSpline->removeDependent(this);
  }
  fbaseSpline = base;
  if (fbaseSpline){
    fbaseSpline->addDependent(this);
  }
  invalidate(this);
}
//------------------------------------------------------------------------------------

void tDistortedSpline::setBaseFaces(tElement* faces)
{
  tGroup *base = dynamic_cast<tGroup*>(faces);
  if (fbaseFaces){
    fbaseFaces->removeDependent(this);
  }
  fbaseFaces = base;
  if (fbaseFaces){
    fbaseFaces->addDependent(this);
  }
  invalidate(this);
}
//------------------------------------------------------------------------------------

void tDistortedSpline::setDistortedFaces(tElement* faces){
  if (fdistortedFaces){
    fdistortedFaces->removeDependent(this);
  }
  fdistortedFaces = dynamic_cast<tGroup*>(faces);
  if (fdistortedFaces){
      fdistortedFaces->addDependent(this);
  }
  invalidate(this);
}
//------------------------------------------------------------------------------------

//tList<tElement*> tDistortedSpline::vertices(void){
//  //!!!!weg damit, nicht schön, da punkte nggf. gelöscht werden...
//  setElementLocked
//  tList<tElement*> v = fdistortedSpline->vertices();
//
//  return v;
//
//}


//------------------------------------------------------------------------------------
