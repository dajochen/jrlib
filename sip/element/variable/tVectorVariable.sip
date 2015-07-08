//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVectorVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tVectorVariable :  public tVariable  {

%TypeHeaderCode
#include "tVectorVariable.h"
%End

public:
	tVectorVariable(tVariableNameSpace *nameSpace, QString function="");
	virtual ~tVectorVariable();

	virtual void refresh();
	iElement* intrface();
	tVector value();
	void setValue(tVector value);
	virtual void setRHS(QString rhs);
	virtual tVariableType type();
};
