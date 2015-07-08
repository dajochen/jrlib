//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tGroup.h (Do. Sep. 25 23:02:24 2014)
//------------------------------------------------------------------------

class tGroup :  public tElement {

%TypeHeaderCode
#include "tGroup.h"
%End

public:
	tGroup(void* theOwner, const QString& allowedType="");
	virtual ~tGroup();

	virtual int nElements(QString type);
	virtual tElement* element(int index);
	virtual tElement* last();
	virtual tElement* first();
	bool contains(tElement* el);
	virtual tElement* append(tElement* el);
	virtual tElement* prepend(tElement* el);
	virtual void removeElement(int i);
	virtual bool removeAllElements(tElement *el);
	virtual void clear();
	virtual void removeAllButLast();
	virtual void removeAllButFirst();
	virtual void reverse();
	virtual tVector xMin();
	virtual tVector xMax();
	virtual void moveElement(int from, int to);
	virtual iElement* intrface();
};
