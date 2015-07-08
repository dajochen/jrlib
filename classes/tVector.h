#ifndef TVECTOR_H_
#define TVECTOR_H_

#include <math.h>
#include "classes/jrTypes.h"

class tVector
{
  public:
    tReal x,y,z;

//Ist ein Konstruktor sinnvoll, oder Zeitraubennd?
	  tVector()
	  {
	    x = 0.;
	    y = 0.;
	    z = 0.;
    }
	  //------------------------------------------------------------------------------

	  tVector (tReal ax,tReal ay,tReal az)
	  {
	    x = ax;
	    y = ay;
	    z = az;
    }
	  //------------------------------------------------------------------------------

	  tVector (tReal a[3])
	  {
	    x = a[0];
	    y = a[1];
	    z = a[2];
    }
	  //------------------------------------------------------------------------------

    tVector operator = (const tVector& C)
    {
      x = C.x;
      y = C.y;
      z = C.z;
      return *this;
    }
    //------------------------------------------------------------------------------

    bool operator == (const tVector& C) const
    {
      return (x == C.x && y == C.y && z == C.z);
    }
    //------------------------------------------------------------------------------

    bool operator != (const tVector& C) const
    {
      return !(*this == C);
    }
    //------------------------------------------------------------------------------

    tReal* operator [] (int i)
	  {
	    if (i%3 == 0)
	      return &x;
	    else if (i%3 == 1)
	      return &y;
	    else
	      return &z;
    }
	  //------------------------------------------------------------------------------

	  tVector operator + (const tVector& C) const
	  {
	    tVector result;
	    result.x = x + C.x;
	    result.y = y + C.y;
	    result.z = z + C.z;
	    return result;
    }
	  //------------------------------------------------------------------------------

	  tVector operator - (const tVector& C) const
	  {
	    tVector result;
	    result.x = x - C.x;
	    result.y = y - C.y;
	    result.z = z - C.z;
	    return result;
    }
	  //------------------------------------------------------------------------------

	  tVector operator * (double scalar) const
	  {
	    tVector result;
	    result.x = scalar*x;
	    result.y = scalar*y;
	    result.z = scalar*z;
	    return result;
    }
	  //------------------------------------------------------------------------------

	  double operator * (const tVector& C) const
	  {																	// Skalarprodukt
	    return (x*C.x+y*C.y+z*C.z);
	  }
	  //------------------------------------------------------------------------------

	  tVector operator % (const tVector& C) const
	  {																	// Kreuzprodukt;
	    tVector result;
	    result.x = y*C.z-z*C.y;
	    result.y = z*C.x-x*C.z;
	    result.z = x*C.y-y*C.x;
	    return result;
    }
	  //------------------------------------------------------------------------------

	  double length(void) const
		{											           // Laenge des Vektors
	    return sqrt(x*x+y*y+z*z);
    }
	  //------------------------------------------------------------------------------

	  double length_squared(void) const
	  {															   // Quadrat der Laenge
	    return x*x+y*y+z*z;
    }
	  //------------------------------------------------------------------------------

    tVector normalize(const double& l=1) const
    {                                // Normiert den Vector auf die Laenge l
      tVector result;
      double l0 = sqrt(x*x+y*y+z*z);
      result.x = x/l0*l;
      result.y = y/l0*l;
      result.z = z/l0*l;
      return result;
    }
    //------------------------------------------------------------------------------

	  void setZero(void)
	  {
	  	x = y = z = 0.;
    }
	  //------------------------------------------------------------------------------

	  tVector rotate(const tVector& x0,const tVector& Axis,tReal alpha) const
	  {
	    tVector A[3],pp,p,dx;
	    tReal r;
	    dx = *this-x0;
	    if (Axis.length_squared() > 0. && dx.length_squared() > 0. && (Axis%dx).length_squared() > 0. ){
	      A[0] = Axis*(1./Axis.length());
	      A[2] = A[0]%dx;
	      A[2] = A[2]*(1./A[2].length());
	      A[1] = A[2]%A[0];
	      // Transponierung in lokales Koos.
	      pp=dx;
	      p.x = A[0]*(pp);
	      p.y = A[1]*(pp);
	      p.z = A[2]*(pp);
	      // genauer Rotationsanteil
	      r = p.y;
	      p.y = r*cos(alpha);
	      p.z = r*sin(alpha);
	      // Transponierung in glob. Koos.
	      pp.x = x0.x+  A[0].x*p.x+A[1].x*p.y+A[2].x*p.z;
	      pp.y = x0.y+  A[0].y*p.x+A[1].y*p.y+A[2].y*p.z;
	      pp.z = x0.z+  A[0].z*p.x+A[1].z*p.y+A[2].z*p.z;
	      return pp;
	    } else {
	      return *this;
	    }
    }
	  //------------------------------------------------------------------------------

    tVector rotate(const tVector& Axis,tReal alpha) const
    {
      tVector A[3],p,pp;
      tReal r;
      if (Axis.length_squared()>0. && (Axis%(*this)).length_squared()>0.){
        A[0] = Axis*(1./Axis.length());
        A[2] = A[0]%(*this);
        A[2] = A[2]*(1./A[2].length());
        A[1] = A[2]%A[0];
    // Transponierung in lokales Koos.
        p.x = A[0]*(*this);
        p.y = A[1]*(*this);
        p.z = A[2]*(*this);
    // genauer Rotationsanteil
        r = p.y;
        p.y = r*cos(alpha);
        p.z = r*sin(alpha);
    // Transponierung in glob. Koos.
        pp.x = A[0].x*p.x+A[1].x*p.y+A[2].x*p.z;
        pp.y = A[0].y*p.x+A[1].y*p.y+A[2].y*p.z;
        pp.z = A[0].z*p.x+A[1].z*p.y+A[2].z*p.z;
        return pp;
      } else {
        return *this;
      }
    }
	  //------------------------------------------------------------------------------

		tVector mirror(const tVector& center, tVector normal) const
		{
			tVector pp;
			normal = normal*(1./normal.length());
			pp = *this-center;
			return *this-normal*(normal*pp*2.);
    }
	  //------------------------------------------------------------------------------

    tVector toCylCOS(const tVector& Center, tVector xDir, tVector phi0, tReal minAngle=-M_PI) const
    {
      // gibt einen Vektor im Zylinderkoordinatensystem zurueck (x, r, phi)
      tVector p,P,phi90;
      tReal x,y,l;

      P = *this;
      l = xDir.length();
      if (l>0){
        xDir = xDir*(1./l);
        p.x = (P-Center)*xDir;
        P = P-(Center+xDir*p.x);
        p.y = P.length();
        phi0 = (xDir%phi0)%xDir;
        phi0 = phi0*(1./phi0.length());
        phi90 = xDir%phi0;
        y = P*phi90;
        x = P*phi0;
        p.z = atan2(y,x);

        while (p.z< minAngle){
          p.z += M_PI *2.;
        }
        while (p.z > minAngle+M_PI*2.){
          p.z -= M_PI *2.;
        }

      } else {
        p.setZero();
      }

      return p;
    }
    //------------------------------------------------------------------------------
    tVector toKarthesianCOS(const tVector& Center, tVector xDir, tVector phi0) const
    {
      // gibt einen Vektor im Zylinderkoordinatensystem zurueck (x, r, phi)
      tVector p,phi90;
      tReal l;

      l = xDir.length();
      if (l>0){
        xDir = xDir*(1./l);
        phi0 = (xDir%phi0)%xDir;
        phi0 = phi0*(1./phi0.length());
        phi90 = xDir%phi0;

        p = Center + xDir*x + phi0*y*cos(z) + phi90*y*sin(z);
      } else {
        p.setZero();
      }
      return p;
    }
    //------------------------------------------------------------------------------
};

#endif /*TVECTOR_H_*/
