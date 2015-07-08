//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDot.h (So. Jan. 26 23:45:54 2014)
//------------------------------------------------------------------------

class tDot :  public tElement /Abstract/ {

%TypeHeaderCode
#include "tDot.h"
%End

public:
	tDot(void *theowner);
	virtual ~tDot();

	tReal x();
	tReal y();
	tReal z();
	tVector vector();
	virtual tVector xMin();
	virtual tVector xMax();
};
