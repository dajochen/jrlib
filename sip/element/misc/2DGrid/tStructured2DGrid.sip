//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured2DGrid :  public tStructuredAbstractGrid /Abstract/ {

%TypeHeaderCode
#include "tStructured2DGrid.h"
%End

public:
	tStructured2DGrid(void *theowner);
	virtual ~tStructured2DGrid();

	bool orientation();
	void setOrientation(bool orient);
	virtual tDot* edgePointAt(int edge,int index);
};
