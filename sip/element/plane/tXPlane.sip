//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tXPlane.h (Di. Jan. 28 21:50:56 2014)
//------------------------------------------------------------------------

class tXPlane :  public tBasicPlane {

%TypeHeaderCode
#include "tXPlane.h"
%End

public:
	tXPlane(void* theOwner);
	virtual ~tXPlane();

	virtual void refresh();
	double x();
	void setX (double ax);
};
