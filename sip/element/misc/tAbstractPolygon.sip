//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbstractPolygon.h (Di. Okt. 14 23:53:08 2014)
//------------------------------------------------------------------------

class tAbstractPolygon :  public tPaintableElement {

%TypeHeaderCode
#include "tAbstractPolygon.h"
%End

public:
	tAbstractPolygon(void* theOwner, int maxVerts);
	virtual ~tAbstractPolygon();

	iElement* intrface();
	virtual void refresh();
	virtual tVector normal();
	virtual tVector center();
	virtual double area();
	virtual int nVertices();
	virtual tDot* vertex(int i);
	void addVertex(tElement *el);
	void removeAllVertices();
	virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool &isSelected);
};
