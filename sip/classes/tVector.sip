
 
class tVector {


%TypeHeaderCode
#include "tVector.h"
%End

  public:
    //tReal x,y,z;

    tVector();
    tVector (tReal ax,tReal ay,tReal az);
    //tVector (tReal a[3]);
    //tVector operator = (const tVector& C);
    //tReal* operator [] (int i);
    //tVector operator + (const tVector& C) const;
    //tVector operator - (const tVector& C) const;
    //tVector operator * (double scalar) const;
    //double operator * (const tVector& C) const;
    //tVector operator % (const tVector& C) const;

    double length() const;
    double length_squared() const;
    tVector normalize(const double& l=1) const;
    void setZero();
    tVector rotate(const tVector& x0,const tVector& Axis,tReal alpha) const;
    tVector rotate(const tVector& Axis,tReal alpha) const;
    tVector mirror(const tVector& center, tVector normal) const;
    tVector toCylCOS(const tVector& Center, tVector xDir, tVector phi0, tReal minAngle=-M_PI) const;
    tVector toKarthesianCOS(const tVector& Center, tVector xDir, tVector phi0) const;
};
