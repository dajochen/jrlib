//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCSpline.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tCSplineType{jrCSVortexBased,jrCSLengthBased};


class tCSpline :  public tCurve {

%TypeHeaderCode
#include "tCSpline.h"
%End

public:
	tCSpline(void *theOwner, tList<tElement*> *l);
	virtual ~tCSpline();

	iElement* intrface();
	virtual void refresh();
	tCSplineType CSplineType();
	void setCSplineType(int t);
	int degree();
	void setDegree(int deg);
	bool addVortex(tDot *P);
	bool insertVortex(int i, tElement *P);
	void addVertices(tGroup *Group);
	void clear();
	virtual tVector vectorAtAccurate(tReal t);
	virtual tVector gradientAt(tReal t);
	virtual tVector curvatureAt(tReal t);
	tDot* getVortex(int index);
	tReal tAtVortex(int index);
};
