/*
 * tAbstractSpline.h
 *
 *  Created on: 24.02.2012
 *      Author: hundemj
 */

#ifndef TABSTRACTSPLINE_H_
#define TABSTRACTSPLINE_H_

#include "element/curve/tDotListCurve.h"
#include "element/point/tDot.h"

#include "iAbstractSpline.h"

class tAbstractSpline : public tDotListCurve
{
private:
    const int maxVertices;
public:
  tAbstractSpline(void *theOwner, int maxVerts=-1);
  virtual ~tAbstractSpline();

  void addVertex(tElement *el);
  void addVertex(int index, tElement *el);
  void addVertices(tList<tElement*> *List);
  void setVertices(tList<tElement*> list);
  void setVertices(tList<tDot*> list);

  void removeAllVertices(void);
};

/*sip!
isAbstract=true
*/
/*I!
vertices DotList read:vertices write:setVertices
*/

#endif /* TABSTRACTSPLINE_H_ */
