#ifndef TROTATEDCURVE_H_
#define TROTATEDCURVE_H_


#include "classes/tVector.h"
#include "element/curve/tCurve.h"
#include "element/curve/tLine.h"

#include "element/curve/iRotatedCurve.h"

class tRotatedCurve : public tCurve
{
	private:
		tCurve* RefCurve;
		tLine* Axis;
		tReal Angle;
	public:
		tRotatedCurve(void *theOwner, tElement *curve=NULL, tElement *axis=NULL, tReal phi=0.);
		virtual ~tRotatedCurve();

		virtual iElement* intrface(void);

	  virtual tVector vectorAtAccurate(tReal t);
	  virtual tVector gradientAt(tReal t);
	  virtual tVector curvatureAt(tReal t);
		virtual tReal length(void){setElementLocked if (RefCurve) return RefCurve->length(); else return 0.;};
	  virtual void refresh(void);

    tReal angle(void){setElementLocked return Angle;};
	  tLine* axis() {setElementLocked return Axis;};
	  tCurve* reference() {setElementLocked return RefCurve;};

    void setAngle(tReal a){setElementLocked Angle = a; invalidate(this);};
	  void setAxis(tElement* a);
	  void setReference(tElement *Curve);
};

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
angle Real read:angle write:setAngle
referenceAxis Line read:axis write:setAxis
referenceCurve Curve read:reference write:setReference
*/
#endif /*TROTATEDCURVE_H_*/
