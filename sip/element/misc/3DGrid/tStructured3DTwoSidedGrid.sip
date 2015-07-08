//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DTwoSidedGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured3DTwoSidedGrid :  public tStructured3DGrid {

%TypeHeaderCode
#include "tStructured3DTwoSidedGrid.h"
%End

public:
	tStructured3DTwoSidedGrid(void *theowner);
	virtual ~tStructured3DTwoSidedGrid();

	virtual iElement* intrface();
	virtual void refresh();
	virtual void setNi(int n);
	virtual void setNj(int n);
	virtual void setNk(int n);
	virtual void setFace(int f, tElement* el);
};
