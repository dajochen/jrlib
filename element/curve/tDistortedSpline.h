/*
 * tDistortedSpline.h
 *
 *  Created on: 28.02.2012
 *      Author: hundemj
 */

#ifndef TDISTORTEDSPLINE_H_
#define TDISTORTEDSPLINE_H_

#include "element/curve/tCurve.h"
#include "element/curve/tDotListCurve.h"
#include "element/curve/tAbstractSpline.h"
#include "element/tGroup.h"

#include "iDistortedSpline.h"

class tDistortedSpline : public tDotListCurve
{
  tAbstractSpline *fbaseSpline, *fdistortedSpline;
  tGroup *fbaseFaces, *fdistortedFaces;
  void clear(void);

protected:

public:
  tDistortedSpline(void *theOwner);
  virtual ~tDistortedSpline();

  iElement* intrface(void);
  virtual void refresh(void);

  virtual void invalidate(tElement *sender);

  virtual tVector vectorAtAccurate(tReal t);

  virtual void setBaseSpline(tElement* base);
  virtual tAbstractSpline* baseSpline(void) {return fbaseSpline;}

  virtual void setBaseFaces(tElement* base);
  virtual void setDistortedFaces(tElement* base);
  virtual tGroup* baseFaces(void) {return fbaseFaces;}
  virtual tGroup* distortedFaces(void) {return fdistortedFaces;}

  //virtual tList<tElement*> vertices(void){update(); return fdistortedSpline->vertices();};

};
/*I!
baseSpline AbstractSpline write:setBaseSpline read:baseSpline
baseSurfaces Group write:setBaseFaces read:baseFaces
distortedSurfaces Group write:setDistortedFaces read:distortedFaces
*/

#endif /* TDISTORTEDSPLINE_H_ */
