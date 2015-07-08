//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tWageningenBSeries.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tWageningenBSeries :  public tPropSurface  {

%TypeHeaderCode
#include "tWageningenBSeries.h"
%End

public:
	tWageningenBSeries(void *theOwner, tLayer *hostingLayer = NULL);
	virtual ~tWageningenBSeries();

	virtual void refresh();
	virtual iElement* intrface();
	void setPD(tReal pd);
	tReal PD();
	void setAEA0(tReal aeao);
	tReal AEA0();
};
