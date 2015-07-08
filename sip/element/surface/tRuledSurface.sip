//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRuledSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRuledSurface :  public tSurface {

%TypeHeaderCode
#include "tRuledSurface.h"
%End

public:
	tRuledSurface(void *theOwner, tCurve *C1, tCurve *C2);
	virtual ~tRuledSurface();

	virtual iElement* intrface();
	virtual tVector xMin();
	virtual tVector xMax();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	virtual tVector normalVectorAt(tReal u, tReal v);
	virtual void refresh();
	void setCurve(int index, tElement *c);
	void setCurves(tElement* C1, tElement *C2);
};
