//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSubCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tSubCurve :  public tCurve {

%TypeHeaderCode
#include "tSubCurve.h"
%End

public:
	tSubCurve(void *theOwner,tAbsBead *C1, tAbsBead *C2);
	virtual ~tSubCurve();

	iElement* intrface();
	virtual void refresh();
	tAbsBead* start();
	tAbsBead* end();
	void setStart(tElement *el);
	void setEnd(tElement *el);
	void setVertex(int i, tElement *El);
	void setVertices(tElement *C1, tElement *C2);
	virtual tVector vectorAtAccurate(tReal t);
	virtual tVector gradientAt(tReal t);
};
