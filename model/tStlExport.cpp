/*
 * tStlExport.cpp
 *
 *  Created on: 25.03.2011
 *      Author: jochen
 */

#include "model/tStlExport.h"

tStlExport::tStlExport()
{
}
//--------------------------------------------------------------
tStlExport::~tStlExport()
{
}
//--------------------------------------------------------------

QString tStlExport::exportTri(tVector x1,tVector x2,tVector x3, tVector n)
{
  QString stl;
//  QLocale style(QLocale::German);
  QLocale style(QLocale::English);
  tVector normal = (x2-x1)%(x3-x1);
  normal = normal*(1./normal.length());
  normal = n;
  int prec=6;
  stl += " facet normal "
      + style.toString(normal.x,'G',prec) + " " + style.toString(normal.y,'G',prec) + " " + style.toString(normal.z,'G',prec) + "\n"
      + "  outer loop\n"
      + "   vertex " + style.toString(x1.x,'G',prec) + " " + style.toString(x1.y,'G',prec) + " " + style.toString(x1.z,'G',prec)+"\n"
      + "   vertex " + style.toString(x2.x,'G',prec) + " " + style.toString(x2.y,'G',prec) + " " + style.toString(x2.z,'G',prec)+"\n"
      + "   vertex " + style.toString(x3.x,'G',prec) + " " + style.toString(x3.y,'G',prec) + " " + style.toString(x3.z,'G',prec)+"\n"
      + "  endloop\n"
      + " endfacet\n";
  return stl;
}
//--------------------------------------------------------------

QString tStlExport::exportQuad(tVector x1,tVector x2,tVector x3, tVector x4, tVector n)
{
  QString stl;
  if ((x4-x2).length_squared() < (x3-x1).length_squared()){
    stl += exportTri(x1,x2,x4,n);
    stl += exportTri(x3,x4,x2,n);
  } else {
    stl += exportTri(x2,x3,x1,n);
    stl += exportTri(x4,x1,x3,n);
  }
  return stl;
}
//--------------------------------------------------------------
QString tStlExport::exportSurface(tSurface* f)
{
  QString stl ;
  int ni = f->uDiv()*f->uRes(),
      nj = f->vDiv()*f->vRes();
  if (ni>0 && nj>0){
    QString surfaceName = f->intrface()->name().simplified();
    surfaceName.replace(" ","_");
    stl = "solid " + surfaceName + "\n";
    for (int i=0; i<ni;i++){
      double ulow = (double)i/(double)ni;
      double uup = (double)(i+1)/(double)ni;
      for (int j=0; j<f->vDiv()*f->vRes();j++){
        double vlow = (double)j/(double)nj;
        double vup = (double)(j+1)/(double)nj;
        stl += exportQuad(f->vectorAt(ulow,vlow), f->vectorAt(ulow,vup), f->vectorAt(uup,vup), f->vectorAt(uup,vlow), f->normalVectorAt((ulow+uup)*0.5,(vlow+vup)*0.5));
     }
    }
    stl += "endsolid " /*+ surfaceName + */"\n";
  }
  return stl;
}
//--------------------------------------------------------------

QString tStlExport::exportElement(tElement *el)
{
  el->lockElement();

  tSurface *f;
  tLayer *l;
  l = dynamic_cast<tLayer*>(el);
  f = dynamic_cast<tSurface*>(el);
  QString out;

  if (l) {
    for (int i=0;i<l->nElements();i++){
      out += exportElement(l->element(i));
    }
  } else if (f){
    out = exportSurface(f);
  } else {
    out = "";
  }
  el->unlockElement();
  return out;
}
//--------------------------------------------------------------

bool tStlExport::exportToFile(QString fileName, tElement* m)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
     return false;
  } else {
    QTextStream out(&file);
    tModel* M = dynamic_cast<tModel*>(m);
    out << exportElement(M);

//    if (M){
//      for(unsigned int i=0; i<M->nElements(); i++){
//        out << exportElement(M->element(i));
//      }
//    }
    return true;
  }
}
//--------------------------------------------------------------
