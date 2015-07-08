//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbsBead.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tAbsBead :  public tDot {

%TypeHeaderCode
#include "tAbsBead.h"
%End

public:
	tAbsBead(void *theOwner,tElement *CURVE=NULL, tReal POS=0.5);
	virtual ~tAbsBead();

	iElement* intrface();
	virtual void refresh();
	tReal position();
	void setPosition(tReal POS);
	tCurve* reference();
	void setReference(tElement *el);
};
