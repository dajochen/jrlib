//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPoint.h (Mi. Nov. 20 21:35:49 2013)
//------------------------------------------------------------------------

class tPoint :  public tDot {

%TypeHeaderCode
#include "tPoint.h"
%End

public:
	tPoint(void *theOwner, tReal x, tReal y, tReal z);
	virtual ~tPoint();

	void setX(tReal X);
	void setY(tReal Y);
	void setZ(tReal Z);
	void setVector(tVector X);
	void refresh();
	virtual iElement* intrface();
};
