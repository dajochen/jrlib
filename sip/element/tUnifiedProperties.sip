//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tUnifiedProperties.h (Di. Nov. 5 22:07:23 2013)
//------------------------------------------------------------------------

class tUnifiedProperties :  public tElement {

%TypeHeaderCode
#include "tUnifiedProperties.h"
%End

public:
	tUnifiedProperties(void *theOwner);
	virtual ~tUnifiedProperties();

	iElement* intrface();
	virtual void refresh();
	QString commonProperty();
	void setCommonProperty(QString property);
};
