//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tQuad.h (Mo. Jan. 27 20:43:29 2014)
//------------------------------------------------------------------------

class tQuad :  public tElement {

%TypeHeaderCode
#include "tQuad.h"
%End

public:
	tQuad(void *theowner);
	virtual ~tQuad();

	virtual void refresh();
	virtual iElement* intrface();
	virtual tVector xMin();
	virtual tVector xMax();
	void setCorner(int index, tElement *c);
	void defineQuad(tElement *C1,tElement *C2, tElement *C3,tElement *C4);
	tDot* c(int index);
	tDot* c1();
	tDot* c2();
	tDot* c3();
	tDot* c4();
	tVector normalVector();
	tVector center();
	tReal area();
	tReal size();
	tReal diameter();
	tReal twistiness();
};
