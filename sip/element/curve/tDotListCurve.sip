//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDotListCurve.h (Sa. Okt. 4 13:40:59 2014)
//------------------------------------------------------------------------

class tDotListCurve :  public tCurve /Abstract/ {

%TypeHeaderCode
#include "tDotListCurve.h"
%End

public:
	tDotListCurve(void *theOwner);
	virtual ~tDotListCurve();

	virtual int nVertices();
	virtual tDot* vertex(int i);
};
