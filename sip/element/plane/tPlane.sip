//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPlane.h (Mo. Jan. 27 23:16:24 2014)
//------------------------------------------------------------------------

class tPlane :  public tBasicPlane {

%TypeHeaderCode
#include "tPlane.h"
%End

public:
	tPlane(void* theOwner);
	virtual ~tPlane();

	virtual void refresh();
	virtual void setCenter(tElement *center);
	virtual void setOnNormal(tElement *onNormal);
	virtual void setOnHorizontal(tElement *onHorizontal);
	virtual void setMode (int mode);
	virtual tDot* centerPoint();
	virtual tDot* onNormal();
	virtual tDot* onHorizontal();
	virtual int mode();
};
