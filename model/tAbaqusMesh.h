/*
 * tAbaqusMesh.h
 *
 *  Created on: 07.06.2011
 *      Author: jochen
 */

#ifndef TABAQUSMESH_H_
#define TABAQUSMESH_H_

#include <QString>
#include <QTextStream>
#include <QMap>
#include "element/tElement.h"
#include "element/tGroup.h"
#include "model/tModel.h"
#include "element/point/tDot.h"
#include "element/misc/3DGrid/tStructured3DGrid.h"
#include "element/misc/2DGrid/tStructured2DGrid.h"


class tAbaqusMesh
{

private:

  class AbqElement {
  public:
    QList<tDot*> vertices;       // Vertices of the element (must fit to the given type in the AbqElementSet)
  };

  class AbqElementSet {
  public:
    QString caption;              //Caption of the element set (here the name of the tGroup-Element
    QString type;                 //Abaqus element type
    QList<AbqElement> abqElements;//List of Elements
  };

  // Element Sets:
  QList<AbqElementSet> abqSets ;
  // NodeSets:
  QMap<QString, QList<tDot*> > nodeSets_;
  QList<tElement*> lockedElements;

  void exportModel(tElement *el, QTextStream& stream);
  void exportLayer(tElement *el);
  void exportStructured3DGrid(tElement *el);
  void exportStructured2DGrid(tElement *el);

public:
  tAbaqusMesh();
  virtual ~tAbaqusMesh();

  bool exportToFile(QString fileName, tModel *m);
};

#endif /* TABAQUSMESH_H_ */
