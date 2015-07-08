//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tBasicPlane.h (Mi. Jan. 29 20:14:48 2014)
//------------------------------------------------------------------------

class tBasicPlane :  public tElement {

%TypeHeaderCode
#include "tBasicPlane.h"
%End

public:
	tBasicPlane(void* theOwner);
	virtual ~tBasicPlane();

	virtual tVector xMin();
	virtual tVector xMax();
	virtual tVector normal();
	virtual tVector center();
	virtual tVector horizontalDir();
	virtual tReal distance(const tVector& x);
	virtual bool isValidPlane();
	virtual tVector projectToPlane(const tVector& x);
	virtual tVector projectToPlaneCoords(const tVector& x);
};
