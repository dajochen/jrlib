//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tSurface :  public tElement /Abstract/ {

%TypeHeaderCode
#include "tSurface.h"
%End

public:
	tSurface(void *theOwner);
	virtual ~tSurface();

	virtual tVector xMin();
	virtual tVector xMax();
	virtual void invalidate(tElement *sender);
	virtual tVector vectorAt(tReal u, tReal v);
	virtual tVector normalVectorAt(tReal u, tReal v);
	virtual void setUDiv(int UDIV);
	virtual void setURes(int URES);
	virtual void setVDiv(int VDIV);
	virtual void setVRes(int VRES);
	int uDiv();
	int uRes();
	int vDiv();
	int vRes();
	tVector* uvCache();
	bool accurate();
	void setAccurate(bool a);
	bool orientation();
	void setOrientation(bool o);
};
