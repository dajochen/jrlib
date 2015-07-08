#ifndef TFUNCTIONCURVE_H_
#define TFUNCTIONCURVE_H_

#include "element/curve/tCurve.h"
#include "element/variable/tVariableNameSpace.h"
#include "element/variable/tRealVariable.h"
#include "element/variable/tVectorVariable.h"
#include <QStringList>

#include "iFunctionCurve.h"

class tFunctionCurve : public tCurve
/* A FunctionCurve allows a description of a Curve by a formula. As all
 * other Curves the functionCurve is parameterized from 0..1 in u- and v-direction.
 * The x- y- and z- component of a Curve can be set by: setFunction(x=0.2*v)
 * setFunction(y=0.3*u*v) and setFunction(z=sqrt(v)) for example.
 *
 * A FunctionCurve may also refer to other Curves. Such a Curve has to be added with
 * addCurve(myCurve). Afterwards the functions may also refer to the x- y- and z-component
 * of this reference Curve. The setFunction-call would then possibly have the following
 * argument: z=myCurve.z+myCurve.y+sqrt(v)
 *
 * Also other additional functions may be introduced. E.g.:
 * setFunction(r=10);
 * setFunction(x=r*sin(u));
 * setFunction(y=r*cos(u));
 * setFunction(z=u);
 *
 */

{
	private:
		tList<tCurve*> refList;
		QStringList aliasList;
		tVariableNameSpace *ns, *referenceVars;//, *coordinates;
		tRealVariable *t, *x,*y,*z;
		tList<tRealVariable*> refVars;
		tVectorVariable *X;

		QString lastAddedFunc;

		void clearRefList(void);
		void clearFunctions(void);

	public:
		tFunctionCurve(void *theOwner, tVariableNameSpace *externVariables);
		virtual ~tFunctionCurve();

	  virtual void refresh(void);
		virtual iElement* intrface(void);

		void clear(bool doSo=true);
		virtual tVector vectorAtAccurate(tReal T);

    void addFunction(QString func);
	  void addReference(tElement *reference, QString alias="");

	  void addFunctionManually(QString func){lastAddedFunc = func; addFunction(func);};
    QString lastAddedFunction(void) {return lastAddedFunc;};

    QString variableStringList(void);

    tList<tElement*> referenceCurves(void);
    void setReferenceCurves(const tList<tElement*>& list);

    QString functions(void);
    void setFunctions(const QString& funcs);

	  bool isCleared(void){if (refVars.count()+refList.count() > 0){return (false);} else {return (true);}};
};

//optional clear Bool read:isCleared write:clear

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
availableVariables String read:variableStringList
references CurveList read:referenceCurves write:setReferenceCurves
functions String read:functions write:setFunctions
optional addFunction String read:lastAddedFunction write:addFunctionManually
*/

#endif /*TFUNCTIONCURVE_H_*/
