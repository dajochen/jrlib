//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tYPlane.h (Di. Jan. 28 21:48:12 2014)
//------------------------------------------------------------------------

class tYPlane :  public tBasicPlane {

%TypeHeaderCode
#include "tYPlane.h"
%End

public:
	tYPlane(void* theOwner);
	virtual ~tYPlane();

	virtual iElement* intrface();
	virtual void refresh();
	double y();
	void setY (double ay);
};
