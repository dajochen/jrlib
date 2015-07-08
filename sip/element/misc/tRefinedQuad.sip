//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRefinedQuad.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tRefinedQuad :  public tQuad {

%TypeHeaderCode
#include "tRefinedQuad.h"
%End

public:
	tRefinedQuad(void *theowner);
	virtual ~tRefinedQuad();

	virtual iElement* intrface();
	virtual void refresh();
	virtual void setDot(int edge, int pos, tDot* d);
	return dotList(0);
	return dotList(1);
	return dotList(2);
	return dotList(3);
};
