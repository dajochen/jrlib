//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSumCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tSumCurve :  public tCurve {

%TypeHeaderCode
#include "tSumCurve.h"
%End

public:
	tSumCurve(void *theOwner);
	virtual ~tSumCurve();

	void clear();
	void addSupport(tElement *el);
	int nCurves();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
	iElement* intrface();
};
