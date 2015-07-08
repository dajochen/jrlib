/*
 * tStlExport.h
 *
 *  Created on: 25.03.2011
 *      Author: jochen
 */

#ifndef TSTLEXPORT_H_
#define TSTLEXPORT_H_
#include "model/tModel.h"
#include <QtCore>
class tStlExport
{
public:
  tStlExport();
  virtual ~tStlExport();
  QString exportTri(tVector x1,tVector x2,tVector  x3, tVector n);
  QString exportQuad(tVector x1,tVector x2,tVector x3, tVector x4, tVector n);
  QString exportSurface(tSurface* f);
  QString exportElement(tElement *el);
  bool exportToFile(QString fileName, tElement *m);
};

#endif /* TSTLEXPORT_H_ */
