//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOperator.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

enum tVariableType{ vtReal, vtVector, vtList };


class tOperator :  public tElement  /Abstract/ {

%TypeHeaderCode
#include "tOperator.h"
%End

public:
	tOperator(tElement *theowner);
	virtual ~tOperator();

	iElement* intrface();
};
