//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tListVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tListVariable :  public tVariable {

%TypeHeaderCode
#include "tListVariable.h"
%End

public:
	tListVariable(tVariableNameSpace *nameSpace, QString function="");
	virtual ~tListVariable();

	virtual void refresh();
	iElement* intrface();
	virtual void setRHS(QString rhs);
	virtual tVariableType type();
	virtual void appendItem(QString itemName);
	bool isRealOnly();
	tReal minimum();
	tReal maximum();
};
