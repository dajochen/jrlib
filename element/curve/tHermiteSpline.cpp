#include "element/curve/tHermiteSpline.h"

#include "classes/utils.h"

tHermiteSpline::tHermiteSpline(void *theOwner): tAbstractSpline(theOwner)
{
  fc = 0.;
  fb = 0.;
  ft = 0.;
}
//-----------------------------------------------------------------------------
tHermiteSpline::~tHermiteSpline()
{
	removeAllVertices();
}
//-----------------------------------------------------------------------------

iElement* tHermiteSpline::intrface(void){
	if (iface == NULL){
		iface = new iHermiteSpline(this);
	}
	return iface;
}


tVector tHermiteSpline::vectorAtAccurate(tReal t)
{
  setElementLocked
  update();
  int i;
  tReal t3,t2;
  tVector x, m0, m1, p0, p1;

  if (vertices_.count() == 0){
    return tVector(0.,0.,0.);
  } else if (vertices_.count() == 1){
    return vertices_.at(0)->vector();
  } else {
    t = min(t,1.);
    t = max(t,0.);

    t2 = t*(vertices_.count()-1);
    i = (int)floor(t2);
    t = t2-i;
    t2 = t*t;
    t3 = t2*t;

    if (i==vertices_.count()-1){
      return vertices_.last()->vector();
    } else {
      p0 = vertices_.at(i)->vector();
      p1 = vertices_.at(i+1)->vector();

      m0 = (p1-p0)*(1-fc)*(1-fb);
      if (i>0){
        m0 = (m0 + (p0-vertices_.at(i-1)->vector())*(1+fc)*(1+fb))*0.5;
      }
      m0 = m0 * (1-ft);

      m1 = (p1-p0)*(1+fb)*(1-fc);
      if (i<vertices_.count()-2){
        m1 = (m1 + (vertices_.at(i+2)->vector()-p1)*(1+fc)*(1-fb))*0.5;
      }
/*      m1 = m1 * (1-ft);
      if (i==0){
        m0 = p1-p0;
      } else {
        m0 = (p1-vortex.at(i-1)->vector())*0.5;
      }
      if (i==vortex.count()-2){
        m1 = p1-p0;
      } else {
        m1 = (vortex.at(i+2)->vector() - p0)*0.5;
      }
      m1 = p1-p0;
      if (i<vortex.count()-2){
        m1 = (m1 + (vortex.at(i+2)->vector()-p1))*0.5;
      }*/

//      return p0*(1-frac)+p1*frac;
      x = p0*(2*t3-3*t2+1)
            +m0*(t3-2*t2+t)
            +p1*(-2*t3+3*t2)
            +m1*(t3-t2);
      return x;
    }
  }
}

//-----------------------------------------------------------------------------

void tHermiteSpline::refresh(void)
{
  // es gibt derzeit noch nichts zu tun.
  // Vielleicht Gruppen als support in vortexe umwandeln
}
//-----------------------------------------------------------------------------

