//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolygonCurve.h (Do. Okt. 16 19:57:19 2014)
//------------------------------------------------------------------------

class tPolygonCurve :  public tAbstractSpline {

%TypeHeaderCode
#include "tPolygonCurve.h"
%End

public:
	tPolygonCurve(void* theOwner, int maxVerts=-1);
	virtual ~tPolygonCurve();

	virtual void refresh();
	iElement* intrface();
	void setIsLoop(bool isLoop);
	bool isLoop();
	virtual tVector vectorAtAccurate(tReal t);
};
