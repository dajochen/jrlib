#ifndef TCLOFT_H_
#define TCLOFT_H_

#include "element/surface/tSurface.h"
#include "element/curve/tCurve.h"
#include "element/curve/tCSpline.h"
#include "element/tGroup.h"
#include "element/point/tPoint.h"

#include "iCLoft.h"

class tCLoft : public tSurface
{
	private:
		tList<tCurve*> uCurves; // Die Stützkurven
		tVector ****A;          // Matrix, die die Koeffizienten der Fläche speichert
		int fDegree;  					// Grad der Interpolation

    void clearMatrixA();
		void transformUV(tReal u,tReal v,int *i, int *j, tReal *uEps, tReal *vEps);

                            // transformiert ein u-v-Paar in die entsprechenden i,j, uEps und vEps-Werte

	public:
		tCLoft(void *theOwner);
		virtual ~tCLoft();

		virtual iElement* intrface(void);
	  virtual tVector xMin(void);
	  virtual tVector xMax(void);

	  virtual tVector vectorAtAccurate(tReal u, tReal v);
	  virtual tVector normalVectorAt(tReal u, tReal v);

    virtual void setUDiv(int UDIV);
    virtual void setURes(int URES);

	  virtual void refresh(void);

	  void appendCurve(tCurve* c);
	  void insertCurve(int index, tCurve* c);
	  void insertGroup(int index, tGroup *g);
		void insertList(int index, tList<tElement*> *l);

		void setCurves(tList<tElement*> list);
		tList<tElement*> curves(void);
		void removeAllCurves(void);
		int nCurves(void) {return uCurves.count();};

		int degree(void){return fDegree;};
		void setDegree(int deg){fDegree = deg; invalidate(this);}

    void clear(void);
};

/*I!
numberOfCurves Int read:nCurves
curves CurveList read:curves write:setCurves
degree Int read:degree write:setDegree
*/

#endif /*TCLOFT_H_*/
