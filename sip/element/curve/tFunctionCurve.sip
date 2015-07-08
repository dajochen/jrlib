//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionCurve.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tFunctionCurve :  public tCurve {

%TypeHeaderCode
#include "tFunctionCurve.h"
%End

public:
	tFunctionCurve(void *theOwner, tVariableNameSpace *externVariables);
	virtual ~tFunctionCurve();

	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector vectorAtAccurate(tReal T);
	void addFunction(QString func);
	void addFunctionManually(QString func);
	QString lastAddedFunction();
	QString variableStringList();
	QString functions();
	void setFunctions(const QString& funcs);
	bool isCleared();
};
