#ifndef TPOLYCURVE_H_
#define TPOLYCURVE_H_

#include "element/point/tAbsBead.h"
#include "element/curve/tCurve.h"
#include "element/curve/tLine.h"

#include "iPolyCurve.h"

enum tPolyCurveType{jrPCCurveBased,jrPCLengthBased};

class tPolyCurve : public tCurve
{
	private:
		tPolyCurveType thePolyCurveType;
		tList<tCurve*> curve, supportCurve;
		tList<tReal> dt;
		tList<int> freversedCurve;

		tReal fgapTolerance;
		bool closePolyCurve;
		void deleteConnections(void);
		void createConnections(void);
	public:
		tPolyCurve(void *theOwner);
		virtual ~tPolyCurve();

		iElement* intrface(void);
		virtual void refresh(void);

		void addElement(tElement* el);
		void addList(tList<tElement*> *list);
		void removeAllCurves(void);

		int nCurves(void){return supportCurve.count();};
	  void setCurves(tList<tElement*> list);
		tList<tElement*> curves(void);


	  virtual tVector vectorAtAccurate(tReal t);
		tPolyCurveType polyCurveType(void);
    void setPolyCurveType(tPolyCurveType plt);
    void setPolyCurveType(int type); //sipIgnore

    bool autoClosePolyCurve(void) {return closePolyCurve;};
    void setAutoClosePolyCurve(bool value){closePolyCurve = value; invalidate(this);};

    tList<int> reversedCurves(void) {return freversedCurve;};
    void setReversedCurves(tList<int> reversed){freversedCurve = reversed; invalidate(this);};

    double gapTolerance(void) {return fgapTolerance;};
    void setGapTolerance(tReal value){fgapTolerance = value; invalidate(this);};
};

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
nSupportingCurves Int read:nCurves
supportingCurves CurveList read:curves write:setCurves
reverseCurve IntList read:reversedCurves write:setReversedCurves
interpolationMode Int read:polyCurveType write:setPolyCurveType
gapTolerance Real read:gapTolerance write:setGapTolerance
autoClosePolyCurve Bool read:autoClosePolyCurve write:setAutoClosePolyCurve
*/

#endif /*TPOLYCURVE_H_*/
