//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLineSnake.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tLineSnake :  public tSnake {

%TypeHeaderCode
#include "tLineSnake.h"
%End

public:
	tLineSnake(void *theOwner,tElement *M1, tElement *M2);
	virtual ~tLineSnake();

	iElement* intrface();
	virtual void refresh();
	tAbsMagnet* start();
	tAbsMagnet* end();
	void setStart(tElement *c);
	void setEnd(tElement *c);
	void setMagnet(int i, tElement *c);
	void setMagnets(tElement *C1, tElement *C2);
	virtual tVector vectorAtAccurate(tReal t);
	virtual void uvPosition(tReal t, tReal *u, tReal *v);
	virtual tSurface* reference();
};
