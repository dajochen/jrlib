//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tThreePointPlane.h (Mi. Jan. 29 20:51:14 2014)
//------------------------------------------------------------------------

class tThreePointPlane :  public tBasicPlane {

%TypeHeaderCode
#include "tThreePointPlane.h"
%End

public:
	tThreePointPlane(void* theOwner);
	virtual ~tThreePointPlane();

	virtual void refresh();
	virtual void setCenter(tElement *center);
	virtual void setP1(tElement* p);
	virtual void setP2(tElement* p);
	virtual tDot* centerPoint();
	virtual tDot* p1();
	virtual tDot* p2();
};
