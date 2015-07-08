//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVectorOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tVectorOperatorType{ // ohne weitere Argumente
													votInvalid, votIsVariable,
													// benoetigt ein Argument
													votBracket,
													// benoetigt zwei Argumente
													votPlus, votMinus, votProduct, votCrossProduct,
													// benoetigt drei Argumente
													votStep, votIsValue
												};


class tVectorOperator :  public tOperator {

%TypeHeaderCode
#include "tVectorOperator.h"
%End

public:
	tVectorOperator(tElement *theowner);
	virtual ~tVectorOperator();

	virtual void refresh();
	iElement* intrface();
	void init(QString term, tVariableNameSpace* nameSpace);
	QString toString();
	tVector value();
	void setValue(tVector v);
	tVariableType type();
	virtual bool isValidOperator();
};
