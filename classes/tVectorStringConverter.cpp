#include "classes/tVectorStringConverter.h"
#include <QLocale>

tVectorStringConverter::tVectorStringConverter()
{
}
//-----------------------------------------------------------------------------

tVectorStringConverter::~tVectorStringConverter()
{
}
//-----------------------------------------------------------------------------

QString tVectorStringConverter::toString(tVector x, QString separator){
  QString vector;
  vector = QString::number(x.x) +  separator + QString::number(x.y) +  separator + QString::number(x.z);
  return vector;
}
//-----------------------------------------------------------------------------

tVector tVectorStringConverter::toVector(QString str, QRegExp separator, bool *ok){

  QLocale style(QLocale::English);
  tVector x;
  QStringList vector;
  int i;
  bool myOk;
  tReal value;

  if (!ok){
    ok = &myOk;
  }

  vector = str.split(separator, QString::SkipEmptyParts);
  if (vector.count()!=3){
    *ok = false;
    return x;
  } else {
    *ok = true;
  }
  
  for (i=0;i<3 && i<vector.count();i++){ 
      value = style.toDouble( vector[i].replace(',','.'), ok );
    //  value = vector[i].replace(',','.').toDouble(ok);
    if (!*ok){
      value = 0.;
    }
    *x[i] = value;
  }
  return x;

}
//-----------------------------------------------------------------------------
