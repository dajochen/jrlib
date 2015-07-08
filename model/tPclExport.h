#ifndef TPCLEXPORT_H_
#define TPCLEXPORT_H_

#include <QtXml>

#include "model/tModel.h"

#include <set>

class tPclExport
{

private:
  bool visibleOnly;
  QDomDocument *XML;
  int nQuads;
  QString compName;
  QDomElement root, currentCOOS;
  std::map<tDot*,int> *dots;
  tList<tDot*> pclExportDot;

  void exportModel(tElement *el);
  void exportGroup(tElement *el);
  void exportSurface(tElement *el);
  void exportStructured2DGrid(tElement *el);

public:
  tPclExport();
  virtual ~tPclExport();

  bool exportToFile(QString fileName, tModel *m);
};

#endif /*TPCLEXPORT_H_*/
