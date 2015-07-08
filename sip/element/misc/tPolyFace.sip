//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolyFace.h (So. Sep. 14 13:57:48 2014)
//------------------------------------------------------------------------

class tPolyFace :  public tElement {

%TypeHeaderCode
#include "tPolyFace.h"
%End

public:
	tPolyFace(void* theowner);
	virtual ~tPolyFace();

	iElement* intrface();
	virtual void refresh();
	virtual int nVertices();
	virtual tDot* vertex(int i);
	void addVertex(tElement *el);
	void removeAllVertices();
};
