//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSubSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tSubSurface :  public tSurface {

%TypeHeaderCode
#include "tSubSurface.h"
%End

public:
	tSubSurface(void *theOwner,tElement *S1 = NULL, tElement *S2=NULL);
	virtual ~tSubSurface();

	virtual void refresh();
	void clear();
	void setBoundingSnakes(tElement *el1, tElement *el2);
	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
};
