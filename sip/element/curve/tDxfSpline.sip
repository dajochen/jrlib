//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDxfSpline.h (Sa. Mär. 21 22:43:43 2015)
//------------------------------------------------------------------------

class tDxfSpline :  public tAbstractSpline {

%TypeHeaderCode
#include "tDxfSpline.h"
%End

public:
	tDxfSpline(void *theOwner);
	virtual ~tDxfSpline();

	iElement* intrface();
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal t);
};
