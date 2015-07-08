#ifndef TFUNCTIONSURFACE_H_
#define TFUNCTIONSURFACE_H_

#include "element/surface/tSurface.h"
#include "element/variable/tVariableNameSpace.h"
#include "element/variable/tRealVariable.h"
#include "element/variable/tVectorVariable.h"
#include <QStringList>

#include "iFunctionSurface.h"

class tFunctionSurface : public tSurface
/* A FunctionSurface allows a description of a surface by a mathematic formula. As all
 * other surfaces the functionSurface is parameterized from 0..1 in u- and v-direction.
 * The x- y- and z- Komponent of a surface can be set by: setFunction(x=0.2*v)
 * setFunction(y=0.3*u*v) and setFunction(z=sqrt(v)) for example.
 *
 * A FunctionSurface may also refer to other surfaces. Such a surface has to be added with
 * addSurface(mySurface). Afterwards the functions may also refer to the x- y- and z-component
 * of this reference surface. The setFunction-call would then possibly have the following
 * argument: z=mySurface.z+mySurface.y+sqrt(v)
 *
 * Also other additional functions may be introduced. E.g.:
 * setFunction(r=10);
 * setFunction(x=r*sin(v));
 * setFunction(y=r*cos(v));
 * setFunction(z=u);
 *
 */

{
	private:
		tList<tSurface*> refList;
		QStringList aliasList;
		tVariableNameSpace *ns;
		tRealVariable *u,*v, *x,*y,*z;
		tList<tRealVariable*> refVars;
		tVectorVariable *X;

	public:
		tFunctionSurface(void *theOwner, tVariableNameSpace *externVariables = NULL);
		virtual ~tFunctionSurface();

	  virtual void refresh(void);
		virtual iElement* intrface(void);

		void clear(bool doSo=true);
		virtual tVector vectorAtAccurate(tReal U, tReal V);

	  void addFunction(QString func);
	  void addReference(tElement *reference, QString alias="");
    tElement* lastAddedReference(void);

    QString functionsStringList(void);
    QString variableStringList(void);

	  bool isCleared(void){if (refVars.count()+refList.count() > 0){return false;} else {return true;}};
};

/*-----------------------------------------------------------------------------
 * Das Interface
 * --------------------------------------------------------------------------*/
/*I!
optional addReference Element read:lastAddedReference write:addReference
availableVariables String read:variableStringList
optional addFunction String read:functionsStringList write:addFunction
optional clear Bool read:isCleared write:clear
*/

#endif /*TFUNCTIONSURFACE_H_*/
