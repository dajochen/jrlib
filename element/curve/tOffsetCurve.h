/*
 * tOffsetCurve.h
 *
 *  Created on: 16.07.2010
 *      Author: Jochen
 */

#ifndef TOFFSETCURVE_H_
#define TOFFSETCURVE_H_

#include "element/curve/tCurve.h"
#include "element/curve/snake/tSnake.h"
#include "iOffsetCurve.h"

/**
 * An OffsetCurve is a curve, which has a certain distance to a surface. The path of the curve is described by a snake,
 * which also defines the surface to follow.
 */
class tOffsetCurve : public tCurve{
private:
  tSnake *refSnake;
  tReal fOffset;


protected:

public:
  tOffsetCurve(void *theOwner);
  virtual ~tOffsetCurve();

  virtual iElement* intrface(void);
  virtual tVector vectorAtAccurate(tReal t);
  virtual void refresh(void);

  void setReferenceSnake(tElement *s);
  tSnake* referenceSnake(void){return refSnake;};

  tReal offset(void){return fOffset;};
  void setOffset(tReal o){fOffset = o; invalidate(this);};
};

/*I!
offset Real read:offset write:setOffset
referenceSnake Snake read:referenceSnake write:setReferenceSnake
*/

#endif /* TOFFSETCURVE_H_ */
