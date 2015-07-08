//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRelPoint.h (So. Jan. 26 23:45:49 2014)
//------------------------------------------------------------------------

class tRelPoint :  public tDot {

%TypeHeaderCode
#include "tRelPoint.h"
%End

public:
	tRelPoint(void *theOwner,tElement *el=NULL, tVector DX=tVector(0,0,0));
	virtual ~tRelPoint();

	iElement* intrface();
	virtual void refresh();
	tVector offset();
	void setOffset(tVector v);
	tDot* reference();
	void setReference(tElement *el);
};
