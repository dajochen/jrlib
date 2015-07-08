#ifndef TFREESHIPEXPORT_H
#define TFREESHIPEXPORT_H

#include <QtCore>
#include "tElement.h"
#include "tModel.h"
#include "tLayer.h"

class tFreeShipExport
{
private:
  void exportElement(QTextStream &out, tElement *el);
  void exportLayer(QTextStream &out, tLayer* l);
  void exportCurve(QTextStream &out, tCurve* c);
  void exportDotListCurve(QTextStream &out, tDotListCurve *dlc);
public:
  tFreeShipExport();

  bool exportToFile(QString fileName, tModel *m);

};

#endif // TFREESHIPEXPORT_H
