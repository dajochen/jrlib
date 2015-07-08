/*
 * DXFReader.h
 *
 *  Created on: 21.02.2012
 *      Author: hundemj!!
 */

#ifndef DXFREADER_H_
#define DXFREADER_H_

#ifdef BUILD_WITH_DXFLIB

#include "model/tModel.h"
#include "dl_creationadapter.h" ///usr/include/dxflib/
#include <QtCore>
//class DL_CreationAdapter;
//class DL_PolylineData;
//class DL_VertexData;

class DXFReader : DL_CreationAdapter
{
private:
  tModel *model;
  tElement *activeElement;
  tLayer *subLayer;
  QHash<QString,int> elementCounter;
  int getElementCounter(const QString &type);
public:
  DXFReader(tModel *m, QString fileName);
  virtual ~DXFReader();
  tList<tHermiteSpline*> addedPolylines;
  tList<tDxfSpline*> addedSplines;

  virtual void addSpline(const DL_SplineData &splData);
  virtual void addControlPoint(const DL_ControlPointData&);
  virtual void addKnot(const DL_KnotData&);

  virtual void addPolyline (const DL_PolylineData &pl);
  virtual void addLine (const DL_LineData &line);
  virtual void addVertex (const DL_VertexData &data);
  virtual void addPoint(const DL_VertexData &data);

};

#endif //BUILD_WITH_DXFLIB
#endif /* DXFREADER_H_ */

