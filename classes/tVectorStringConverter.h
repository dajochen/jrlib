#ifndef TVECTORSTRINGCONVERTER_H_
#define TVECTORSTRINGCONVERTER_H_

#include <QStringList>
#include "classes/tVector.h"

class tVectorStringConverter
{
public:
	tVectorStringConverter();
	virtual ~tVectorStringConverter();
  static QString toString(tVector x, QString separator=" ");
  static tVector toVector(QString vector, QRegExp separator=QRegExp("\\s+"), bool *ok=NULL );
};

#endif /*TVECTORSTRINGCONVERTER_H_*/
