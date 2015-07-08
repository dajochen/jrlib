//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbstractSpline.h (Di. Okt. 7 22:08:28 2014)
//------------------------------------------------------------------------

class tAbstractSpline :  public tDotListCurve /Abstract/ {

%TypeHeaderCode
#include "tAbstractSpline.h"
%End

public:
	tAbstractSpline(void *theOwner, int maxVerts=-1);
	virtual ~tAbstractSpline();

	void addVertex(tElement *el);
	void addVertex(int index, tElement *el);
	void removeAllVertices();
};
