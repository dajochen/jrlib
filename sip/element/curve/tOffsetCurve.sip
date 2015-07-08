//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tOffsetCurve :  public tCurve {

%TypeHeaderCode
#include "tOffsetCurve.h"
%End

public:
	tOffsetCurve(void *theOwner);
	virtual ~tOffsetCurve();

	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal t);
	virtual void refresh();
	void setReferenceSnake(tElement *s);
	tSnake* referenceSnake();
	tReal offset();
	void setOffset(tReal o);
};
