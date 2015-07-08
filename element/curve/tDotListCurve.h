/*
 * tAbstractSpline.h
 *
 *  Created on: 24.02.2012
 *      Author: hundemj
 */

#ifndef TDOTLISTCURVE_H_
#define TDOTLISTCURVE_H_

#include "element/curve/tCurve.h"
#include "element/point/tDot.h"

#include "iDotListCurve.h"

class tDotListCurve : public tCurve
{
protected:
  tList<tDot*> vertices_;
  virtual void removeAllVertices(void);

public:
  tDotListCurve(void *theOwner);
  virtual ~tDotListCurve();

  virtual int nVertices(void){ update(); return vertices_.count();}
  virtual tList<tElement*> vertices(void);
  virtual tDot* vertex(int i) {update();  return vertices_.at(i%vertices_.count()); }

};
/*sip! isAbstract */
/*I!
nVertices Int read:nVertices
vertices DotList read:vertices
*/

#endif /* TABSTRACTSPLINE_H_ */
