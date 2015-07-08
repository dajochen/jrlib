//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetCurve2.h (Fr. Sep. 12 22:42:55 2014)
//------------------------------------------------------------------------

class tOffsetCurve2 :  public tCurve {

%TypeHeaderCode
#include "tOffsetCurve2.h"
%End

public:
	tOffsetCurve2(void *theOwner);
	virtual ~tOffsetCurve2();

	iElement* intrface();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
	void setReferenceCurve(tElement* el);
	tDotListCurve* referenceCurve();
	void setOffset(double value);
	double offset();
};
