#include "tFreeShipExport.h"
#include "tVectorStringConverter.h"


tFreeShipExport::tFreeShipExport()
{

}

bool tFreeShipExport::exportToFile(QString fileName, tModel *m)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return false;
  } else {
    QTextStream out(&file);
    /*
    out.setRealNumberNotation(QTextStream::SmartNotation);
    out.setRealNumberPrecision(5);
    out.setNumberFlags(QTextStream::ForcePoint);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out.setFieldWidth(20);
    out.setPadChar(' ');
    */

    exportElement(out, m);

    file.close();
    return true;
  }
}

void tFreeShipExport::exportElement(QTextStream &out, tElement *el)
{
  //tModel *m = dynamic_cast<tModel*>(el);
  tLayer *l = dynamic_cast<tLayer*>(el);
  tDotListCurve *dlc = dynamic_cast<tDotListCurve*>(el);
  tCurve *c = dynamic_cast<tCurve*>(el);

  if (l){
    exportLayer(out, l);
  } else if (dlc) {
    exportDotListCurve(out, dlc);
  } else if (c) {
    exportCurve(out, c);
  }
}

void tFreeShipExport::exportLayer(QTextStream &out, tLayer *l)
{
  if (l->intrface()->visibility()){
    for (int i=0; i<l->nElements(); i++){
      exportElement(out, l->element(i));
    }
  }
}

void tFreeShipExport::exportCurve(QTextStream &out, tCurve *c)
{
  //out << c->intrface()->name() << endl;
  int res = c->tResolution();

  if (c->intrface()->visibility()){
    for (int i=0; i<=res; i++){
      double pos = float(i)/float(res);
      tVector x = c->vectorAt(pos);
      out << tVectorStringConverter::toString(x, " ") << endl;
    }
    out << endl;
  }
}

void tFreeShipExport::exportDotListCurve(QTextStream &out, tDotListCurve *dlc)
{

  if (dlc->intrface()->visibility()){
    tList<tElement*> vertices = dlc->vertices();
    for (int i=0; i<vertices.count(); i++){
      tDot* d = dynamic_cast<tDot*>(vertices.at(i));
      if (d){
        tVector x = d->vector();
        out << tVectorStringConverter::toString(x, " ") << endl;
      }
    }
    out << endl;
  }
}

