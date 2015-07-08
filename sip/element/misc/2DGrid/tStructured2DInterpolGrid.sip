//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DInterpolGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured2DInterpolGrid :  public tStructured2DGrid {

%TypeHeaderCode
#include "tStructured2DInterpolGrid.h"
%End

public:
	tStructured2DInterpolGrid(void *theowner);
	virtual ~tStructured2DInterpolGrid();

	void refresh();
	iElement* intrface();
	tElement* neighbour(int index);
	void setCorner(int i, tElement *el);
	void setEdge(int i, tElement *el);
	void setBase(tElement *el);
	void setNeighbour(int myEdge, tElement *el, int edge);
	virtual void setDistribOnEdge(int i, QString func);
	virtual void setIterations(int iter);
	void setNi(int Ni);
	void setNj(int Nj);
	virtual int ni();
	virtual int nj();
	void setMeshIterations(int iter);
	int meshIterations();
	virtual tDot* gridAt(int i, int j);
	virtual tDot* cornerAt(int index);
	virtual tReal distribOnEdge(int edge, tReal pos);
};
