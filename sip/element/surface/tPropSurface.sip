//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPropSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tPropSurface :  public tSurface {

%TypeHeaderCode
#include "tPropSurface.h"
%End

public:
	tPropSurface(void *theOwner);
	virtual ~tPropSurface();

	void clear();
	bool savePff(QString fileName);
	QString propellerFileName();
	void importExportPropeller(QString);
	virtual void refresh();
	virtual tVector vectorAtAccurate(tReal u, tReal v);
	virtual iElement* intrface();
	virtual tVector camberLineAt(tReal u, tReal v);
	tCurve* pitch();
	tCurve* chord();
	tCurve* rake();
	tCurve* skew();
	tCurve* maxThick();
	tSurface* thickness();
	tSurface* camber();
	void setPitch(tElement *el);
	void setChord(tElement *el);
	void setRake(tElement *el);
	void setSkew(tElement *el);
	void setMaxThick(tElement *el);
	void setThickness(tElement *el);
	void setCamber(tElement *el);
	tReal diameter();
	void setDiameter(tReal d);
	tReal hubDiameter();
	void setHubDiameter(tReal d);
	tReal scale();
	void setScale(tReal s);
	int bladeNumber();
	void setBladeNumber(int z);
	bool rotationDirection();
	void setRotationDirection(bool o);
	bool roundedTip();
	void setRoundedTip(bool type);
	bool autoRoundTE();
	void setAutoRoundTE(bool type);
	bool autoRoundTip();
	void setAutoRoundTip(bool type);
	QString radialRefinement();
	void setRadialRefinement(QString refFunc);
	QString peripherRefinement();
	void setPeripherRefinement(QString refFunc);
	virtual tReal pitchAt(tReal rR);
	virtual tReal chordAt(tReal rR);
	virtual tReal rakeAt(tReal rR);
	virtual tReal skewAt(tReal rR);
	virtual tReal maxThicknessAt(tReal rR);
	virtual tReal hubRadiusAt(tReal x);
	bool isInReadingMode();
	void setReadWriteMode(bool mode);
};
