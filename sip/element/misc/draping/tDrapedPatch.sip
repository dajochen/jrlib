//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDrapedPatch.h (Di. Okt. 14 23:53:08 2014)
//------------------------------------------------------------------------

class tDrapedPatch :  public tPaintableElement {

%TypeHeaderCode
#include "tDrapedPatch.h"
%End

public:
	tDrapedPatch(void* theOwner);
	virtual ~tDrapedPatch();

	iElement* intrface();
	virtual void refresh();
	virtual void invalidate(tElement *sender);
	virtual void setInitialPoint(tElement* el);
	virtual void setInitialPointProjectionDir(tElement* el);
	virtual void setInitialFiberDir(tElement* el);
	virtual void setPatch(tElement* el);
	virtual void setMeshSize(double mSize);
	virtual void runDrapingSimulation();
	virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool &isSelected);
};
