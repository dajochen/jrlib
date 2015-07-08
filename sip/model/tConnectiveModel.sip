//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tConnectiveModel.h (Mi. Jul 3 23:41:04 2013)
//------------------------------------------------------------------------

class tConnectiveModel :  public QObject,  public tModel {

%TypeHeaderCode
#include "tConnectiveModel.h"
%End

public:
	tConnectiveModel();
	virtual ~tConnectiveModel();

	virtual iElement* intrface();
	virtual void invalidate(tElement *sender);
	virtual void repaint();
	virtual tLayer* addLayer(QString name);
};
