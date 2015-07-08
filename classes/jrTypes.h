#ifndef JRTYPES_H_
#define JRTYPES_H_

#include <QString>

typedef double tReal;
typedef QString tString;

//#define tReal double

typedef struct { tReal x,y,z; } txyz;

/*enum jrTypes { jrNone, jrBool, jrInt, jrReal, jrVector, jrString, jrRGB,
              jrElement,
							jrDot, jrBead, jrCurve, jrLine, jrSurface,
              jrCSplineType, jrPolylineType, jrPolyCurveType,
              jrElementList };

class jrType{
public:
  jrTypes type;
  QString elementSpecifier;

  bool operator==(const jrType& b)
  {
    return type == b.type;
  };
  bool operator==(const jrTypes& b)
  {
    return type == b;
  };

  jrType& operator= (const jrType& b)
  {
    type = b.type;
    elementSpecifier = b.elementSpecifier;
    return *this;
  };
  jrType& operator= (const jrTypes& b)
  {
    type = b;
    elementSpecifier = "";
    return *this;
  };

//  Type1::operator type();
};*/

#endif /*JRTYPES_H*/
