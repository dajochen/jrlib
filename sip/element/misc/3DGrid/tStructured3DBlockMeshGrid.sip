//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DBlockMeshGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured3DBlockMeshGrid :  public tStructured3DGrid {

%TypeHeaderCode
#include "tStructured3DBlockMeshGrid.h"
%End

public:
	tStructured3DBlockMeshGrid(void *theowner);
	virtual ~tStructured3DBlockMeshGrid();

	virtual iElement* intrface();
	virtual void refresh();
	virtual void setNi(int n);
	virtual void setNj(int n);
	virtual void setNk(int n);
	virtual void setCorner(int c, tElement* el);
	virtual tDot* corner(int index);
	virtual void setEdge(int e, tElement* el);
	virtual void setFace(int f, tElement* el);
};
