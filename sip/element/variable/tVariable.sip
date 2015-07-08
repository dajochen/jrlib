//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tVariable :  public tElement /Abstract/ {

%TypeHeaderCode
#include "tVariable.h"
%End

public:
	tVariable(tVariableNameSpace *nameSpace);
	virtual ~tVariable();

	iElement* intrface();
	virtual bool isValidVariable();
	virtual QString name();
	virtual void setName(QString name);
	virtual QString RHS();
	virtual QString fullString();
	virtual void setFullString(QString function);
};
