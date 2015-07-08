//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tFunctionPoint :  public tDot {

%TypeHeaderCode
#include "tFunctionPoint.h"
%End

public:
	tFunctionPoint(void *theOwner, tVariableNameSpace *externVariables);
	virtual ~tFunctionPoint();

	virtual void refresh();
	virtual iElement* intrface();
	void addFunction(QString func);
	void addFunctionManually(QString func);
	QString lastAddedFunction();
	QString variableStringList();
	QString functions();
	void setFunctions(const QString& funcs);
	bool isCleared();
};
