//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCLoft.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tCLoft :  public tSurface {

%TypeHeaderCode
#include "tCLoft.h"
%End

public:
	tCLoft(void *theOwner);
	virtual ~tCLoft();

	virtual iElement* intrface();
	virtual tVector xMin();
	virtual tVector xMax();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	virtual tVector normalVectorAt(tReal u, tReal v);
	virtual void setUDiv(int UDIV);
	virtual void setURes(int URES);
	virtual void refresh();
	void appendCurve(tCurve* c);
	void insertCurve(int index, tCurve* c);
	void insertGroup(int index, tGroup *g);
	void removeAllCurves();
	int nCurves();
	int degree();
	void setDegree(int deg);
	void clear();
};
