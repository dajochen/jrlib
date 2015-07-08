//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCommonProperty.h (Mo. Nov. 4 00:21:53 2013)
//------------------------------------------------------------------------

class tCommonProperty :  public tElement {

%TypeHeaderCode
#include "tCommonProperty.h"
%End

public:
	tCommonProperty(void *theOwner);
	virtual ~tCommonProperty();

	iElement* intrface();
	virtual void refresh();
	QString commonProperty();
	void setCommonProperty(QString property);
};
