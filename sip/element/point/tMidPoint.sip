//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tMidPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tMidPoint :  public tDot {

%TypeHeaderCode
#include "tMidPoint.h"
%End

public:
	tMidPoint(void *theOwner, tElement *element=NULL);
	virtual ~tMidPoint();

	void addDot(tElement* d);
	void removeDot(tElement* d);
	void removeAll();
	virtual void refresh();
	iElement* intrface();
};
