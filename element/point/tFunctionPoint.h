#ifndef TFUNCTIONPOINT_H_
#define TFUNCTIONPOINT_H_

#include "element/point/tDot.h"
#include "element/variable/tVariableNameSpace.h"
#include "element/variable/tRealVariable.h"
#include "element/variable/tVectorVariable.h"
#include <QStringList>

#include "iFunctionPoint.h"

class tFunctionPoint : public tDot
/* A FunctionPoint allows a description of a Point by a formula.
 * The x- y- anPointcomponent of a Point can be set by: setFunction(x=0.2*v)
 * setFunction(y=0.3*u*v) and setFunction(z=sqrt(v)) for example.
 *
 * A FunctionPoint may also refer to other Points. Such a Point has to be added with
 * addPoint(myPoint). Afterwards the functions may also refer to the x- y- and z-component
 * of this reference Point. The setFunction-call would then possibly have the following
 * argument: z=myPoint.z+myPoint.y
 *
 * Also other additional functions may be introduced. E.g.:
 * setFunction(r=10);
 * setFunction(x=r);
 * setFunction(y=r*r);
 * setFunction(z=0);
 *
 */

{
	private:
		tList<tDot*> refList;
		QStringList aliasList;
		tVariableNameSpace *ns, *referenceVars;//, *coordinates;
		tRealVariable *x,*y,*z;
		tList<tRealVariable*> refVars;
		tVectorVariable *Xpos;

		QString lastAddedFunc;

		void clearRefList(void);
		void clearFunctions(void);

	public:
		tFunctionPoint(void *theOwner, tVariableNameSpace *externVariables);
		virtual ~tFunctionPoint();

	  virtual void refresh(void);
		virtual iElement* intrface(void);

		void clear(bool doSo=true);
		//virtual tVector vectorAtAccurate(tReal T);

    void addFunction(QString func);
	  void addReference(tElement *reference, QString alias="");

	  void addFunctionManually(QString func){lastAddedFunc = func; addFunction(func);};
    QString lastAddedFunction(void) {return (lastAddedFunc);};

    QString variableStringList(void);

    tList<tElement*> referenceDots(void);
    void setReferenceDots(const tList<tElement*>& list);

    QString functions(void);
    void setFunctions(const QString& funcs);

	  bool isCleared(void){if (refVars.count()+refList.count() > 0){return (false);} else {return (true);}};
};

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
availableVariables String read:variableStringList
references DotList read:referenceDots write:setReferenceDots
functions String read:functions write:setFunctions
optional addFunction String read:lastAddedFunction write:addFunctionManually
*/

#endif /*TFUNCTIONPOINT_H_*/
