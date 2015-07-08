//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tNetPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tNetPoint :  public tDot {

%TypeHeaderCode
#include "tNetPoint.h"
%End

public:
	tNetPoint(void *theowner, tNet *net, tDot *refPoint);
	virtual ~tNetPoint();

	virtual void refresh();
	tNet* net();
	void setNet(tElement* net);
	tDot* refPoint();
	void setRefPoint(tElement* refPoint);
	virtual iElement* intrface();
};
