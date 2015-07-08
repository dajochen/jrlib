#ifndef TREVOLVEDSURFACE_H_
#define TREVOLVEDSURFACE_H_

#include "classes/tVector.h"
#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"
#include "element/curve/tLine.h"

#include "iRevolvedSurface.h"

class tRevolvedSurface : public tSurface
{
	private:
		tCurve *frefCurve;
		tLine *faxis;
		tReal fstartAngle,fendAngle;
	public:
		tRevolvedSurface(void *theOwner);
		tRevolvedSurface(void *theOwner, tElement *curve, tElement *a, tReal phi0 ,tReal phi1);
		virtual ~tRevolvedSurface();

		virtual iElement* intrface(void);

	  virtual tVector vectorAtAccurate(tReal u, tReal v);
	  virtual void refresh(void);

    tLine* axis(void);
    tCurve* refCurve(void);
    void setAxis(tElement *a);
    void setRefCurve(tElement *c);
    tReal startAngle(void);
    tReal endAngle(void);
    void setStartAngle(tReal alpha);
    void setEndAngle(tReal alpha);
};

/*I!
axis Line read:axis write:setAxis
refCurve Curve read:refCurve write:setRefCurve
startAngle Real read:startAngle write:setStartAngle
endAngle Real read:endAngle write:setEndAngle
*/


#endif /*REVOLVEDSURVACE_H_*/
