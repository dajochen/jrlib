//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tZPlane.h (Di. Jan. 28 22:15:13 2014)
//------------------------------------------------------------------------

class tZPlane :  public tBasicPlane {

%TypeHeaderCode
#include "tZPlane.h"
%End

public:
	tZPlane(void* theOwner);
	virtual ~tZPlane();

	virtual void refresh();
	virtual iElement* intrface();
	double z();
	void setZ (double az);
};
