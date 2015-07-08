#ifndef TPATEXPORT_H_
#define TPATEXPORT_H_

#include <QtCore>
#include "model/tModel.h"


class tPatExport
{
private:
	bool isFirstSurface;
	bool visibleOnly;
  void exportElement(tElement *el, QTextStream *out);
//	void exportModel(tElement *el, QTextStream *out);
//  void exportGroup(tElement *el, QTextStream *out);
	void exportLayer(tElement *el, QTextStream *out);
	void exportSurface(tElement *el, QTextStream *out);
  void exportStructured2DGrid(tElement *el, QTextStream *out);
public:
	tPatExport();
	virtual ~tPatExport();

	bool exportToFile(QString fileName, tElement *el);
};

#endif /*TPATEXPORT_H_*/
