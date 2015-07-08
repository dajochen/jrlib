//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRotatedPoint :  public tDot {

%TypeHeaderCode
#include "tRotatedPoint.h"
%End

public:
	tRotatedPoint(void *theOwner,tElement *REFDOT=NULL, tElement *AXIS=NULL, tReal angle=0.);
	virtual ~tRotatedPoint();

	iElement* intrface();
	virtual void refresh();
	tReal angle();
	tLine* axis();
	tDot* reference();
	void setAngle(tReal a);
	void setAxis(tElement *el);
	void setReference(tElement *el);
};
