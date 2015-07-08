//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tTransformedDotListCurve.h (Fr. Sep. 12 21:28:20 2014)
//------------------------------------------------------------------------

class tTransformedDotListCurve :  public tDotListCurve {

%TypeHeaderCode
#include "tTransformedDotListCurve.h"
%End

public:
	tTransformedDotListCurve(void *theOwner);
	virtual ~tTransformedDotListCurve();

	iElement* intrface();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
	virtual tVector shift();
	virtual tReal angle();
	virtual tElement* axis();
	virtual tElement* referenceCurve();
	virtual void setShift(tVector x);
	virtual void setAngle (tReal alpha);
	virtual void setAxis (tElement* axis);
	virtual void setReferenceCurve (tElement* dlc);
};
