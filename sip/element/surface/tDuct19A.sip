//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDuct19A.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tDuct19A :  public tSurface {

%TypeHeaderCode
#include "tDuct19A.h"
%End

public:
	tDuct19A(void *theOwner);
	virtual ~tDuct19A();

	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	void setPropeller(tElement *p);
	tKaSeries* propeller();
	bool adaptToPropellerPitch();
	void setAdaptToPropellerPitch(bool value);
};
