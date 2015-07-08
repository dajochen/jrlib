//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tKaSeries.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tKaSeries :  public tPropSurface  {

%TypeHeaderCode
#include "tKaSeries.h"
%End

public:
	tKaSeries(void *theOwner, tLayer *hostingLayer = NULL);
	virtual ~tKaSeries();

	virtual void refresh();
	virtual iElement* intrface();
	void setPD(tReal pd);
	tReal PD();
	void setAEA0(tReal aeao);
	tReal AEA0();
};
