//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbsMagnet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tAbsMagnet :  public tDot {

%TypeHeaderCode
#include "tAbsMagnet.h"
%End

public:
	tAbsMagnet(void *theOwner,tElement *surf=NULL, tReal U=0.5, tReal V=0.5);
	virtual ~tAbsMagnet();

	iElement* intrface();
	virtual void refresh();
	virtual tReal uPosition();
	virtual tReal vPosition();
	void setPosition(tReal U, tReal V);
	void setUPosition(tReal U);
	void setVPosition(tReal V);
	tSurface* reference();
	void setReference(tElement *newSurface);
};
