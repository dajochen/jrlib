//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tNet.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tNet :  public tElement {

%TypeHeaderCode
#include "tNet.h"
%End

public:
	tNet(void *theowner);
	virtual ~tNet();

	Startwert des Netzpunktes (Point, AbsBead, AbsMagnet);
	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector xMin();
	virtual tVector xMax();
	tVector getVector(tElement *netPoint);
	tDot* getRefPoint(tElement *netPoint);
	void setRefPoint(tElement* netPoint, tElement *refPoint);
	void setBorderKnot(tElement *netPoint);
	int nSprings();
	tLine* springLine(int index);
	void setNetIterations(int i);
	int netIterations();
	void clear();
	void setColor(tRGB color);
};
