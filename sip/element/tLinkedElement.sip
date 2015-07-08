//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLinkedElement.h (Mo. Okt 28 12:21:08 2013)
//------------------------------------------------------------------------

class tLinkedElement :  public tElement {

%TypeHeaderCode
#include "tLinkedElement.h"
%End

public:
	tLinkedElement();
	virtual ~tLinkedElement();

	iElement* intrface();
	virtual void refresh();
	QString property();
	void setProperty(QString property);
	tElement* reference();
	void setReference(tElement *el);
};
