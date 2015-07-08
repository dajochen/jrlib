#ifndef TTRANSFORMEDDOTLISTCURVE_H_
#define TTRANSFORMEDDOTLISTCURVE_H_

#include "element/curve/tDotListCurve.h"
#include "element/curve/tLine.h"

#include "iTransformedDotListCurve.h"


class tTransformedDotListCurve : public tDotListCurve
{	
	private: 
    tVector shift_;
    tReal alpha_;
    tLine* axis_;
    tDotListCurve* dlc_;
    tVector transformed(tVector x);

	public:
		tTransformedDotListCurve(void *theOwner);
		virtual ~tTransformedDotListCurve();

        iElement* intrface(void);
		virtual void refresh(void);

    virtual tVector vectorAtAccurate(tReal t);

    virtual tVector shift(void) const {return shift_;}
    virtual tReal angle (void) const {return alpha_;}
    virtual tElement* axis (void) const {return axis_;}
    virtual tElement* referenceCurve (void) const {return dlc_;}

    virtual void setShift(tVector x){ setElementLocked; shift_=x; invalidate(this);}
    virtual void setAngle (tReal alpha){ setElementLocked; alpha_=alpha; invalidate(this);}
    virtual void setAxis (tElement* axis);
    virtual void setReferenceCurve (tElement* dlc);

};

/*I!
referenceCurve Curve read:referenceCurve write:setReferenceCurve
axis Line read:axis write:setAxis
angle Real read:angle write:setAngle
shift Vector write:setShift read:shift
*/

#endif /*TTRANSFORMEDDOTLISTCURVE_H_*/
