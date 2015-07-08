//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRotatedCurve :  public tCurve {

%TypeHeaderCode
#include "tRotatedCurve.h"
%End

public:
	tRotatedCurve(void *theOwner, tElement *curve=NULL, tElement *axis=NULL, tReal phi=0.);
	virtual ~tRotatedCurve();

	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal t);
	virtual tVector gradientAt(tReal t);
	virtual tVector curvatureAt(tReal t);
	virtual tReal length();
	virtual void refresh();
	tReal angle();
	void setAngle(tReal a);
	void setAxis(tElement* a);
	void setReference(tElement *Curve);
};
