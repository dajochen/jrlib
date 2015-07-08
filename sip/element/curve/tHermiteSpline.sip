//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tHermiteSpline.h (Mi. Apr. 2 22:07:46 2014)
//------------------------------------------------------------------------

class tHermiteSpline :  public tAbstractSpline {

%TypeHeaderCode
#include "tHermiteSpline.h"
%End

public:
	tHermiteSpline(void *theOwner);
	virtual ~tHermiteSpline();

	iElement* intrface();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
	tReal tension();
	tReal bias();
	tReal continuity();
	void setTension(tReal t);
	void setBias(tReal b);
	void setContinuity(tReal c);
};
