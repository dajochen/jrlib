//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStickyMagnet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStickyMagnet :  public tMagnet {

%TypeHeaderCode
#include "tStickyMagnet.h"
%End

public:
	tStickyMagnet(void *theOwner);
	virtual ~tStickyMagnet();

	iElement* intrface();
	virtual void refresh();
	virtual tReal uPosition();
	virtual tReal vPosition();
	virtual tSurface* reference();
	tDot* referenceDot();
	void setReferenceDot(tElement *d);
	tGroup* stickyFaces();
	void setStickyFaces(tElement* faces);
};
