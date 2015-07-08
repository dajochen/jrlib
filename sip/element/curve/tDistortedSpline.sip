//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDistortedSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tDistortedSpline :  public tDotListCurve {

%TypeHeaderCode
#include "tDistortedSpline.h"
%End

public:
	tDistortedSpline(void *theOwner);
	virtual ~tDistortedSpline();

	iElement* intrface();
	virtual void refresh();
	virtual void invalidate(tElement *sender);
	virtual tVector vectorAtAccurate(tReal t);
	virtual void setBaseSpline(tElement* base);
	virtual tAbstractSpline* baseSpline();
	virtual void setBaseFaces(tElement* base);
	virtual void setDistortedFaces(tElement* base);
	virtual tGroup* baseFaces();
	virtual tGroup* distortedFaces();
};
