//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCurve.h (Di. Okt. 14 23:53:08 2014)
//------------------------------------------------------------------------

class tCurve :  public tPaintableElement /Abstract/ {

%TypeHeaderCode
#include "tCurve.h"
%End

public:
	tCurve(void *theOwner);
	virtual ~tCurve();

	virtual void update();
	virtual void invalidate(tElement *sender);
	int tResolution();
	void setTResolution(int res);
	void updateCache();
	virtual tVector vectorAt(tReal t);
	virtual tVector gradientAt(tReal t);
	virtual tVector curvatureAt(tReal t);
	virtual tReal length();
	virtual tVector xMin();
	virtual tVector xMax();
	virtual tReal arrowheadPos();
	virtual void setArrowheadPos(tReal t);
	virtual tReal lineWidth();
	virtual void setLineWidth(tReal w);
	virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector& defaultN, const bool& isSelected);
};
