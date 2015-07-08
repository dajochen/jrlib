//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLine.h (Mo. Okt. 13 22:34:44 2014)
//------------------------------------------------------------------------

class tLine :  public tCurve {

%TypeHeaderCode
#include "tLine.h"
%End

public:
	tLine(void *theOwner,tElement *C1=NULL, tElement *C2=NULL);
	virtual ~tLine();

	iElement* intrface();
	virtual void refresh();
	tDot* start();
	tDot* end();
	void setStart(tElement *el);
	void setEnd(tElement *el);
	void setVortex(int i, tElement *el);
	void setVertices(tElement *C1, tElement *C2);
	virtual tVector vectorAtAccurate(tReal t);
	virtual tVector gradientAt(tReal t);
	virtual tVector curvatureAt(tReal t);
	virtual tReal length();
	virtual tVector xMin();
	virtual tVector xMax();
};
