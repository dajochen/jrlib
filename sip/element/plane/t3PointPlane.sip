//------------------------------------------------------------------------
//Automatically generated interface class
//generated from t3PointPlane.h (Di. Jan. 28 23:37:56 2014)
//------------------------------------------------------------------------

class t3PointPlane :  public tBasicPlane {

%TypeHeaderCode
#include "t3PointPlane.h"
%End

public:
	t3PointPlane(void theOwner);
	virtual ~t3PointPlane();

	virtual void refresh();
	virtual void setCenter(tElement *center);
	virtual void setP1(tElement* p);
	virtual void setP2(tElement* p);
	virtual tDot* centerPoint();
	virtual tDot* p1();
	virtual tDot* p2();
};
