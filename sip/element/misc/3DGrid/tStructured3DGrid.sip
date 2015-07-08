//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured3DGrid :  public tStructuredAbstractGrid /Abstract/ {

%TypeHeaderCode
#include "tStructured3DGrid.h"
%End

public:
	tStructured3DGrid(void *theowner);
	virtual ~tStructured3DGrid();

	virtual iElement* intrface();
	virtual int ni();
	virtual int nj();
	virtual int nk();
	virtual int nIJK(int ijk);
	virtual tDot* gridAt(int i, int j, int k);
};
