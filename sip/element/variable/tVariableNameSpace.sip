//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVariableNameSpace.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tVariableNameSpace :  public tElement  {

%TypeHeaderCode
#include "tVariableNameSpace.h"
%End

public:
	tVariableNameSpace(void *theowner);
	virtual ~tVariableNameSpace();

	virtual void refresh();
	iElement* intrface();
	tVariable* addRealVariable(QString function);
	tVariable* addVectorVariable(QString function);
	tVariable* addListVariable(QString function);
	tVariable* addVariable(QString function);
	bool contains(QString varName);
	int count();
	tVariable* variable(QString varName);
	tVariable* variable(int count);
	tReal getRealVarValue(QString varName);
	tVector getVectorVarValue(QString varName);
	void clear();
	void removeVariable(tVariable *var);
	void inheritNameSpace(tVariableNameSpace *i);
};
