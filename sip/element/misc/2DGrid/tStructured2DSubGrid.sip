//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DSubGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tStructured2DSubGrid :  public tStructured2DGrid {

%TypeHeaderCode
#include "tStructured2DSubGrid.h"
%End

public:
	tStructured2DSubGrid(void *theowner);
	virtual ~tStructured2DSubGrid();

	void setOffsetI(int ii);
	void setOffsetJ(int jj);
	int offsetI();
	int offsetJ();
	void setNi(int ii);
	void setNj(int jj);
	virtual int ni();
	virtual int nj();
	void setNiSkip(int ii);
	void setNjSkip(int jj);
	virtual int niSkip();
	virtual int njSkip();
	void setParentGrid(tElement *el);
	tElement* parentGrid();
	void setDirOn3DGrid(int ijk);
	int dirOn3DGrid();
	void setDirOffsetOn3DGrid(int offset);
	int dirOffsetOn3DGrid();
	virtual tDot* gridAt(int i, int j);
	virtual tDot* cornerAt(int index);
	virtual iElement* intrface();
	virtual void refresh();
};
