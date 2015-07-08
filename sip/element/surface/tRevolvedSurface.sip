//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRevolvedSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRevolvedSurface :  public tSurface {

%TypeHeaderCode
#include "tRevolvedSurface.h"
%End

public:
	tRevolvedSurface(void *theOwner, tElement *curve, tElement *a, tReal phi0 ,tReal phi1);
	virtual ~tRevolvedSurface();

	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	virtual void refresh();
	tLine* axis();
	tCurve* refCurve();
	void setAxis(tElement *a);
	void setRefCurve(tElement *c);
	tReal startAngle();
	tReal endAngle();
	void setStartAngle(tReal alpha);
	void setEndAngle(tReal alpha);
};
