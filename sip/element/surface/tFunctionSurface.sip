//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tFunctionSurface :  public tSurface {

%TypeHeaderCode
#include "tFunctionSurface.h"
%End

public:
	tFunctionSurface(void *theOwner, tVariableNameSpace *externVariables = NULL);
	virtual ~tFunctionSurface();

	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal U, tReal V);
	void addFunction(QString func);
	tElement* lastAddedReference();
	QString functionsStringList();
	QString variableStringList();
	bool isCleared();
};
