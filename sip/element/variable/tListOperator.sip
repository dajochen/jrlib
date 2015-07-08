//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tListOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tListOperatorType{ // ohne weitere Argumente
                        lotInvalid, lotIsVariable, lotIsList
                      };


class tListOperator :  public tOperator  {

%TypeHeaderCode
#include "tListOperator.h"
%End

public:
	tListOperator(tElement *theowner);
	virtual ~tListOperator();

	virtual void refresh();
	iElement* intrface();
	void init(QString term, tVariableNameSpace* nameSpace);
	QString toString();
	tVariableType type();
	virtual bool isValidOperator();
	bool isRealOnly();
	tReal minimum();
	tReal maximum();
	void appendItem(QString itemName, tVariableNameSpace* nameSpace);
};
