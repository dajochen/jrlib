//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tBSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tBSpline :  public tCurve {

%TypeHeaderCode
#include "tBSpline.h"
%End

public:
	tBSpline(void *theOwner);
	virtual ~tBSpline();

	iElement* intrface();
	virtual void refresh();
	bool addVortex(tDot *P);
	void addVertices(tGroup *Group);
	virtual tVector vectorAtAccurate(tReal t);
	int nVertices();
	void removeAllVertices();
};
