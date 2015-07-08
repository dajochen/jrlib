//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRotatedSurface :  public tSurface {

%TypeHeaderCode
#include "tRotatedSurface.h"
%End

public:
	tRotatedSurface(void *theOwner, tSurface *surf, tLine *axis, tReal phi);
	virtual ~tRotatedSurface();

	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	virtual tVector normalVectorAt(tReal u, tReal v);
	virtual void refresh();
	void setAxis(tElement *el);
	void setRefSurface(tElement *el);
	void setAngle(tReal alpha);
	tLine* axis();
	tSurface* refSurface();
	tReal angle();
};
