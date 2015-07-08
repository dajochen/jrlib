//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tMidCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tMidCurve :  public tCurve {

%TypeHeaderCode
#include "tMidCurve.h"
%End

public:
	tMidCurve(void *theOwner);
	virtual ~tMidCurve();

	void clear();
	void addElement(tElement *el);
	void removeAllCurves();
	int nCurves();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
	iElement* intrface();
};
