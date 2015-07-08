//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRealOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tRealOperatorType{ // ohne weitere Argumente
                        rotInvalid, rotIsVariable, rotIsValue,
                        // benoetigt ein Argument
                        rotBracket,
                        rotSinus, rotCosinus, rotTangens, rotArccos, rotArcsin, rotArctan,
                        rotSquareroot, rotAbsolut, rotRoundIt, rotCeilIt, rotFloorIt,
                        // benoetigt zwei Argumente
                        rotPlus, rotMinus, rotMultiply, rotDivide, rotModulo, rotPower,
                        rotArctan2,
                        rotIsEqual, rotIsLess, rotIsLessOrEqual, rotIsGreater, rotIsGreaterOrEqual, rotLogicalAnd, rotLogicalOr,
                        // benoetigt drei Argumente
                        rotStep,
                        // beliebig viele Argumente
                        rotMinimum, rotMaximum
                      };


class tRealOperator :  public tOperator  {

%TypeHeaderCode
#include "tRealOperator.h"
%End

public:
	tRealOperator(tElement *theowner);
	virtual ~tRealOperator();

	virtual void refresh();
	iElement* intrface();
	virtual tReal value();
	virtual void setValue(tReal v);
	virtual void init(QString term, tVariableNameSpace* nameSpace);
	virtual QString toString();
	tVariableType type();
	virtual bool isValidOperator();
};
