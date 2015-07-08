//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCSnake.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

class tCSnake :  public tSnake {

%TypeHeaderCode
#include "tCSnake.h"
%End

public:
	tCSnake(void *theOwner,tList<tElement*> *List = NULL);
	virtual ~tCSnake();

	iElement* intrface();
	virtual void refresh();
	void removeAllVertices();
	tSurface* reference();
	virtual tVector vectorAtAccurate(tReal t);
	void uvPosition(tReal t, tReal *u, tReal *v);
};
