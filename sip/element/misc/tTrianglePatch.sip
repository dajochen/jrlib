//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tTrianglePatch.h (Do. Okt. 16 20:04:42 2014)
//------------------------------------------------------------------------

class tTrianglePatch :  public tPaintableElement {

%TypeHeaderCode
#include "tTrianglePatch.h"
%End

public:
	tTrianglePatch(void * theOwner);
	virtual ~tTrianglePatch();

	iElement* intrface();
	virtual void refresh();
	int nTriangles();
	virtual tTriangle* triangle(int i);
	void addTriangle(tElement *el);
	void clear();
	void randomizeOrientation();
	void alignOrientation();
	void paintGL(const tVector &EyePoint, const tVector &ObjectPoint, const tRGB &rgb, const tVector &defaultN, const bool &isSelected);
};
