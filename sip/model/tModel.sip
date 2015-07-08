//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tModel.h (So. Jan. 26 11:35:18 2014)
//------------------------------------------------------------------------

class tModel :  public tLayer {

%TypeHeaderCode
#include "tModel.h"
%End

public:
	tModel(void *theOwner);
	virtual ~tModel();

	virtual iElement* intrface();
	tLayer* currentLayer();
	void setCurrentLayer(tLayer *layer);
	void clearSelection();
	void addToSelection(tElement *el);
	void removeFromSelection(tElement *el);
	void setSelection(tElement *el);
	void shiftSelection(const tVector& dx);
	void rotateSelection(const tVector& origin, const tVector& domega);
	void flipSelection(const tVector& origin, const tVector& flipAxis);
	void doublicateFirstSelectedElement();
	QString name();
	void setName(QString name);
	virtual tVector xMin();
	virtual tVector xMax();
};
