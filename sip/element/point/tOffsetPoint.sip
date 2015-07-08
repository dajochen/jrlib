//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tOffsetPoint :  public tDot {

%TypeHeaderCode
#include "tOffsetPoint.h"
%End

public:
	tOffsetPoint(void *theOwner,tElement *S=NULL, tReal U=0.5, tReal V=0.5, tReal D=0.);
	virtual ~tOffsetPoint();

	iElement* intrface();
	virtual void refresh();
	tReal u();
	tReal v();
	tReal offset();
	tSurface* reference();
	void setU(tReal u);
	void setV(tReal v);
	void setOffset(tReal d);
	void setReference(tElement *el);
};
