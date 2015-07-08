//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPropHubSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tPropHubSurface :  public tSurface  {

%TypeHeaderCode
#include "tPropHubSurface.h"
%End

public:
	tPropHubSurface(void *theOwner);
	virtual ~tPropHubSurface();

	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	void clear();
	void setPropellerSurface(tElement* p);
	tPropSurface* propellerSurface();
	void setHubContour(tElement *h);
	tCurve* hubContour();
	void setLeadingPartition(tReal frac);
	tReal leadingPartition();
	void setTrailingPartition(tReal frac);
	tReal trailingPartition();
	void setLeadingAlpha(tReal a);
	tReal leadingAlpha();
	void setTrailingAlpha(tReal a);
	tReal trailingAlpha();
};
