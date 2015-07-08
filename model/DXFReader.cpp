/*
 * DXFReader.cpp
 *
 *  Created on: 21.02.2012
 *      Author: hundemj!!
 */

#include "model/DXFReader.h"
#ifdef BUILD_WITH_DXFLIB
#include "dl_creationadapter.h" ///usr/include/dxflib/
#include "dl_dxf.h"

DXFReader::DXFReader(tModel *m, QString fileName)
: model(m)
{
  DL_Dxf dxf;
  activeElement = NULL;
  subLayer = NULL;

  if (!dxf.in(fileName.toStdString(), this)) {
//  std::cerr << "drawing.dxf could not be opened.\n";
  }

}

DXFReader::~DXFReader()
{
    for (int i=0;i<addedPolylines.count();i++) {
        tHermiteSpline *spl = addedPolylines.at(i);
        int res = spl->vertices().count();
        spl->setTResolution(std::max(res-1,1));
    }
    addedPolylines.clear();

    for (int i=0;i<addedSplines.count();i++) {
        tDxfSpline *spl = addedSplines.at(i);
        int res = spl->vertices().count();
        spl->setTResolution(std::max((res-1)*8,1));
    }
    addedSplines.clear();

}

int DXFReader::getElementCounter(const QString &type){
  int counter;
  if (elementCounter.contains(type)){
    counter = elementCounter[type]+1;
  } else {
    counter = 0;
  }
  elementCounter[type] = counter;
  return counter;
}

void DXFReader::addSpline(const DL_SplineData &splData){
    tLayer *l = model->currentLayer();
    if (l){
        int flags = splData.flags;
        int nKnots = splData.nKnots;
        int nControl = splData.nControl;


        tDxfSpline *spl = dynamic_cast<tDxfSpline*>(l->addElement(iDxfSpline::theType()));

        if (spl){
            spl->degree = splData.degree;
            spl->isClosed = false;

            spl->setTResolution(100);
            activeElement = spl;
            addedSplines.append(spl);
            QString type = activeElement->intrface()->type();
            type.append(QString::number(getElementCounter(type)));
            activeElement->intrface()->setName(type);
            subLayer = dynamic_cast<tLayer*>(l->addElement(iLayer::theType()));
            subLayer->intrface()->setName(type+"_vertices");
            subLayer->intrface()->setVisibility(false);
        }
    }
}

void DXFReader::addControlPoint(const DL_ControlPointData& data)
{
    tDxfSpline* spl = dynamic_cast<tDxfSpline*>(activeElement);

    if (spl){
      tLayer *l;
      if (subLayer){
        l = subLayer;
      } else {
        l = model->currentLayer();
      }
      tPoint *p = l->addPoint(tVector(data.x, data.y, data.z));
      spl->addVertex(p);

      QString type = p->intrface()->type();
      type.append(QString::number(getElementCounter(type)));
      p->intrface()->setName(activeElement->intrface()->name() + "_" + type);
    }
}

void DXFReader::addKnot(const DL_KnotData& data)
{
    int k = data.k;
}


void DXFReader::addPolyline(const DL_PolylineData&)
{
  tLayer *l = model->currentLayer();
  if (l){
    tHermiteSpline *spl = l->addHermiteSpline();
    if (spl){
      spl->setTResolution(100);
      spl->setBias(1.);
      spl->setContinuity(1.);
      spl->setTension(1.0);
      activeElement = spl;
      addedPolylines.append(spl);
      QString type = activeElement->intrface()->type();
      type.append(QString::number(getElementCounter(type)));
      activeElement->intrface()->setName(type);
      subLayer = dynamic_cast<tLayer*>(l->addElement(iLayer::theType()));
      subLayer->intrface()->setName(type+"_vertices");
      subLayer->intrface()->setVisibility(false);
    }
  }
}

void DXFReader::addPoint(const DL_VertexData &data)
{
    tLayer *layer = model->currentLayer();
    layer->addPoint(tVector(data.x,data.y,data.z));
}

void DXFReader::addLine (const DL_LineData &line)
{
    tLayer *layer = model->currentLayer();
    if (layer){
      tLine *l = layer->addLine();
      if (l){
        l->setTResolution(1);

        activeElement = l;
        QString type = activeElement->intrface()->type();
        type.append(QString::number(getElementCounter(type)));
        activeElement->intrface()->setName(type);
        subLayer = dynamic_cast<tLayer*>(layer->addElement(iLayer::theType()));
        subLayer->intrface()->setName(type+"_vertices");
        subLayer->intrface()->setVisibility(false);

        tDot *d1 = subLayer->addPoint(tVector(line.x1,line.y1,line.z1)),
             *d2 = subLayer->addPoint(tVector(line.x2,line.y2,line.z2));

        l->setVertices(d1,d2);

      }
    }
}



void DXFReader::addVertex(const DL_VertexData &data)
{
  tHermiteSpline* hSpl = dynamic_cast<tHermiteSpline*>(activeElement);
  //tLine* line = dynamic_cast<tLine*>(activeElement);

  if (hSpl){
    tLayer *l;
    if (subLayer){
      l = subLayer;
    } else {
      l = model->currentLayer();
    }
    tPoint *p = l->addPoint(tVector(data.x, data.y, data.z));
    hSpl->addVertex(p);

    QString type = p->intrface()->type();
    type.append(QString::number(getElementCounter(type)));
    p->intrface()->setName(activeElement->intrface()->name() + "_" + type);
  }/* else {

      tLayer *l;
      if (subLayer){
        l = subLayer;
      } else {
        l = model->currentLayer();
      }
      tPoint *p = l->addPoint(tVector(data.x, data.y, data.z));
      if (line->start()==NULL){
          line->setStart(p);
      } else {
          line->setEnd(p);
      }

      QString type = p->intrface()->type();
      type.append(QString::number(getElementCounter(type)));
      p->intrface()->setName(activeElement->intrface()->name() + "_" + type);
  }*/
}




#endif // BUILD_WITH_DXFLIB
