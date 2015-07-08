//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DSurfaceGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured2DSurfaceGrid :  public tStructured2DGrid  {

%TypeHeaderCode
#include "tStructured2DSurfaceGrid.h"
%End

public:
	tStructured2DSurfaceGrid(void *theowner);
	virtual ~tStructured2DSurfaceGrid();

	virtual iElement* intrface();
	virtual void refresh();
	virtual int ni();
	virtual int nj();
	void setNi(int i);
	void setNj(int j);
	virtual tDot* gridAt(int i, int j);
	virtual tDot* cornerAt(int index);
	void setBase(tElement *el);
	QString uRefinement();
	QString vRefinement();
	void setURefinement(QString func);
	void setVRefinement(QString func);
	tSurface* base();
};
