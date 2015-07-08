//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tProjectedPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tProjectedPoint :  public tDot {

%TypeHeaderCode
#include "tProjectedPoint.h"
%End

public:
	tProjectedPoint(void *theOwner);
	virtual ~tProjectedPoint();

	iElement* intrface();
	virtual void refresh();
	tVector origin();
	void setOrigin(tVector v);
	tPlane* plane();
	void setPlane(tElement *el);
	tDot* refDot();
	void setRefDot(tElement *el);
};
