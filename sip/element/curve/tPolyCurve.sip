//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPolyCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tPolyCurveType{jrPCCurveBased,jrPCLengthBased};


class tPolyCurve :  public tCurve /Abstract/ {

%TypeHeaderCode
#include "tPolyCurve.h"
%End

public:
	tPolyCurve(void *theOwner);
	virtual ~tPolyCurve();

	iElement* intrface();
	virtual void refresh();
	void addElement(tElement* el);
	void removeAllCurves();
	int nCurves();
	virtual tVector vectorAtAccurate(tReal t);
	tPolyCurveType polyCurveType();
	void setPolyCurveType(tPolyCurveType plt);
	bool autoClosePolyCurve();
	void setAutoClosePolyCurve(bool value);
	double gapTolerance();
	void setGapTolerance(tReal value);
};
