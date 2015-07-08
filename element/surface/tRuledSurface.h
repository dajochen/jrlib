#ifndef TRULEDSURFACE_H_
#define TRULEDSURFACE_H_

#include "element/surface/tSurface.h"
#include "element/curve/tCurve.h"

#include "iRuledSurface.h"

class tRuledSurface : public tSurface
{
	private:
		tCurve *c1,*c2;
	public:
		tRuledSurface(void *theOwner);
		tRuledSurface(void *theOwner, tCurve *C1, tCurve *C2);
		virtual ~tRuledSurface();

//	  virtual tList<tElement*> usedElements(void);

		virtual iElement* intrface(void);
	  virtual tVector xMin(void);
	  virtual tVector xMax(void);

	  virtual tVector vectorAtAccurate(tReal u, tReal v);
	  virtual tVector normalVectorAt(tReal u, tReal v);
	  virtual void refresh(void);

	  void setCurve(int index, tElement *c);
	  void setCurves(tElement* C1, tElement *C2);

	  tList<tElement*> curves(void);
	  void setCurves(tList<tElement*> l);
};

/*I!
boundingCurves CurveList read:curves write:setCurves
*/

#endif /*TRULEDSURFACE_H_*/
