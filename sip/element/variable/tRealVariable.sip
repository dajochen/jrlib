//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRealVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRealVariable :  public tVariable  {

%TypeHeaderCode
#include "tRealVariable.h"
%End

public:
	tRealVariable(tVariableNameSpace *nameSpace, QString function="");
	virtual ~tRealVariable();

	virtual void refresh();
	iElement* intrface();
	tReal value();
	void setValue(tReal value);
	virtual void setRHS(QString rhs);
	virtual tVariableType type();
};
