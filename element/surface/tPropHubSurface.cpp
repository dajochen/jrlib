/*
 * tPropHubSurface.cpp
 *
 *  Created on: 22.07.2010
 *      Author: Jochen
 */

#include "element/surface/tPropHubSurface.h"
#include "classes/utils.h"
#define iterations 30

tPropHubSurface::tPropHubSurface(void *theowner) : tSurface(theowner) {
  prop = NULL;
  fhubContour = NULL;
  fleadingPartition = 0.5;
  ftrailingPartition = 0.5;
  fleadingAlpha = M_PI*0.10;
  ftrailingAlpha = M_PI*0.10;
}
//---------------------------------------------------------------------------------------

tPropHubSurface::~tPropHubSurface() {
  clear();
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::refresh(void)
{
  if (prop){
    tVector x;
    x = prop->vectorAt(0.,0.5);
    xLE = x.x;
    if (fleadingAlpha<0){
      tReal alpha;
      int n;
      alpha = atan2(x.y,x.z);
      alpha = alpha - fleadingAlpha;
      n = floor(alpha/(2.*M_PI));
      alphaMaxLE = alpha - n*2.*M_PI;
    } else {
      alphaMaxLE = fleadingAlpha;
    }
    x = prop->vectorAt(0.,0.);
    xTE = x.x;
    if (ftrailingAlpha<0){
      tReal alpha;
      int n;
      alpha = atan2(x.y,x.z);
      alpha = ftrailingAlpha - alpha;
      n = floor(alpha/(2.*M_PI));
      alphaMaxTE = alpha - n*2.*M_PI;
    } else {
      alphaMaxTE = ftrailingAlpha;
    }
  } else {
    xLE = 0.;
    xTE = 0.;
  }
}
//---------------------------------------------------------------------------------------

iElement* tPropHubSurface::intrface(void)
{
  if (iface == NULL){
    iface = new iPropHubSurface(this);
  }
  return iface;
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::radiusAt(tReal x)
{
  setElementLocked
  update();
  tReal r;
  if (prop){
    if (!fhubContour){
      r = prop->hubRadiusAt(x);
      if (x < xTE-0.2*ftrailingPartition*prop->diameter()){
        x = ((xTE-0.2*ftrailingPartition*prop->diameter())-x)/(0.8*ftrailingPartition*prop->diameter());
        x = min(x,1.);
        x = max(x,0.);
        return sqrt(1-x)*r;
      } else if (x > xLE+0.2*fleadingPartition*prop->diameter()){
        x = max((x-(xLE+0.2*fleadingPartition*prop->diameter()))/(0.8*fleadingPartition*prop->diameter()), 0.);
        x = min(x,1.);
        x = max(x,0.);
        return sqrt(1-x)*r;
      } else {
        return r;
      }
    } else {
      // falls es eine Konturlinie gibt, wird der Radius an dem Ort bestimmt
      return getValueAtCurve(fhubContour,x);
    }
  } else {
    return 1.;
  }
}
//---------------------------------------------------------------------------------------

tVector tPropHubSurface::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked
  update();
  tVector xPS, xSS, xx, x0;
  tReal r, r0, q,
        alpha, // Steigungswinkel an der Nabe
//        phiMalR,
        beta1, beta2,
        tau1, tau2,
        a, b, c;

  if (prop){

    if (u<0.25){
//      tReal alphaMax = M_PI*0.25,
      tReal /*alphaMax,*/ t;
      // trailing End of hub
      q = u /0.25;

      x0 = xx = vectorAtAccurate(0.25, v);

      if (!fhubContour){
        xx.x = xx.x * q + (xTE-ftrailingPartition*prop->diameter()) * (1.-q);
      } else {
        xx.x = xx.x * q + fhubContour->vectorAt(ftrailingPartition).x * (1.-q);
      }
      t = 2.*M_PI*(x0.x-xx.x)/(prop->pitchAt(2.*radiusAt(xx.x)/prop->diameter())*prop->diameter());

      if (t/alphaMaxTE < M_PI*0.5){
        alpha = alphaMaxTE*sin(t/alphaMaxTE);
      } else {
        alpha = alphaMaxTE;
      }
      if (prop->rotationDirection()){
        xx = xx.rotate(tVector(0,0,0), tVector(1,0,0), -alpha);
      } else {
        xx = xx.rotate(tVector(0,0,0), tVector(1,0,0), alpha);
      }
      r = radiusAt(xx.x)/sqrt(xx.y*xx.y+xx.z*xx.z);
      xx.y = xx.y * r;
      xx.z = xx.z * r;

    } else if (u>0.75){
//      tReal alphaMax = M_PI*0.25,
//      tReal alphaMax = M_PI*0.1,
        tReal t;
      // Tip of the hub
      q = (u-0.75) /0.25;
      x0 = xx = vectorAtAccurate(0.75, v);

//      xx.x = xx.x * (1.-q) + (xLE+fleadingPartition*prop->diameter()) * q;
      if (!fhubContour){
        xx.x = xx.x * (1.-q) + (xLE+fleadingPartition*prop->diameter()) * q;
      } else {
        xx.x = xx.x * (1.-q) + fhubContour->vectorAt(fleadingPartition).x * q;
      }

      t =2.* M_PI*(xx.x-x0.x)/(prop->pitchAt(2.*radiusAt(xx.x)/prop->diameter())*prop->diameter());

      if (t/alphaMaxLE < M_PI*0.5){
        alpha = alphaMaxLE*sin(t/alphaMaxLE);
      } else {
        alpha = alphaMaxLE;
      }
      if (prop->rotationDirection()){
        xx = xx.rotate(tVector(0,0,0), tVector(1,0,0), alpha);
      } else {
        xx = xx.rotate(tVector(0,0,0), tVector(1,0,0), -alpha);
      }
      r = radiusAt(xx.x)/sqrt(xx.y*xx.y+xx.z*xx.z);
      xx.y = xx.y * r;
      xx.z = xx.z * r;
    } else {
      u = (u-0.25)*2.;

      xPS = prop->vectorAt(0.,u*0.5);
      xSS = prop->vectorAt(0.,1.-u*0.5);

//      tReal alphaDiff;
//      alphaDiff = fabs(xSS.toCylCOS(tVector(0,0,0),tVector(1,0,0),xPS,-M_PI).z);
//
//      if (prop->rotationDirection()){
//        xx = xPS.rotate(tVector(0,0,0), tVector(1,0,0),  (2.*M_PI/(tReal)(prop->bladeNumber())-alphaDiff)*v);
//      } else {
//        xx = xPS.rotate(tVector(0,0,0), tVector(1,0,0), -(2.*M_PI/(tReal)(prop->bladeNumber())-alphaDiff)*v);
//      }

      if (prop->rotationDirection()){
        xSS = xSS.rotate(tVector(1,0,0),2.*M_PI/(tReal)(prop->bladeNumber()));
      } else {
        xSS = xSS.rotate(tVector(1,0,0),-2.*M_PI/(tReal)(prop->bladeNumber()));
      }


      tVector XSS, XPS; // im zylinder Coosys
      XSS = xSS.toCylCOS(tVector(0,0,0),tVector(1,0,0),xPS,-M_PI);
      XPS = xPS.toCylCOS(tVector(0,0,0),tVector(1,0,0),xPS,-M_PI);
//
      tReal vv;
      vv = 0.1*(v*v*v-2*v*v+v)+0.1*(v*v*v-v*v)-2*v*v*v+3*v*v;
      xx = XPS * (1.-vv) + XSS * vv;
      xx = xx.toKarthesianCOS(tVector(0,0,0),tVector(1,0,0),xPS);

//      xx = XPS.toKarthesianCOS(tVector(0,0,0),tVector(1,0,0),xPS) * (1.-v) + XSS.toKarthesianCOS(tVector(0,0,0),tVector(1,0,0),xPS) * v;
//      xx = xPS * (1.-v) + xSS* v;

      r0 = radiusAt(xx.x);

      alpha = atan(2.*M_PI*r0/(prop->pitchAt(2.*r0/prop->diameter())*prop->diameter()));


      //phiMalR = xx.toCylCOS(tVector(0,0,0),tVector(1,0,0),xPS,-2.*M_PI/(tReal)(prop->bladeNumber()*10)).z * r0;
      //q = -phiMalR * tan(alpha);

//      beta1 = (110./180.*M_PI) * (u)+ (M_PI/2.-alpha)* (1.-u);
//      beta2 = (90./180.*M_PI);// * (u)+ (M_PI/2.+alpha)* (1.-u);
      beta1 = (60./180.*M_PI) * (u)+ (90./180.*M_PI)* (1.-u);
      beta2 = (80./180.*M_PI) * (u)+ (90./180.*M_PI)* (1.-u);

      tau1 = M_PI/2.-alpha-beta1;
      tau2 = M_PI/2.+alpha-beta2;

//      tau1 = 0.;
//      tau2 = 0.;

      a = tan(tau1) - tan(tau2);
      c = tan(tau1);
      b = -c -a;

      q = 0.2*(a*v*v*v + b*v*v + c* v)*2.*M_PI/(tReal)(prop->bladeNumber())*r0;
      //q = 0.;
      xx.x = xx.x + q;
      r = radiusAt(xx.x)/sqrt(xx.y*xx.y+xx.z*xx.z);
      xx.y = xx.y * r;
      xx.z = xx.z * r;
    }
  } else {
    xx.setZero();
  }
// Radius anpassen

  x0 = xx;
  return x0;
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::clear(void)
{
  if (prop){
    prop->removeDependent(this);
  }
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setPropellerSurface(tElement* p)
{
  setElementLocked
  tPropSurface *ps;

  if (prop){
    prop->removeDependent(this);
  }
  ps = dynamic_cast<tPropSurface*>(p);
  if (ps && ps->addDependent(this)){
    prop = ps;
  }
  invalidate(this);
}
//---------------------------------------------------------------------------------------

tPropSurface* tPropHubSurface::propellerSurface(void)
{
  return prop;
}
//---------------------------------------------------------------------------------------

tCurve* tPropHubSurface::hubContour(void)
{
  return fhubContour;
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setHubContour(tElement *h)
{
  setElementLocked
  tCurve *c;

  if (fhubContour){
    fhubContour->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(h);
  if (c && c->addDependent(this)){
    fhubContour = c;
  }
  invalidate(this);
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setLeadingPartition(tReal frac)
{
  if (frac >=0){
    fleadingPartition = frac;
    invalidate(this);
  }
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::leadingPartition(void)
{
  return fleadingPartition;
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setTrailingPartition(tReal frac)
{
  if (frac >=0){
    ftrailingPartition = frac;
    invalidate(this);
  }
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::trailingPartition(void)
{
  return ftrailingPartition;
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setLeadingAlpha(tReal a)
{
  // If alpha is smaller than 0 the angle is an absolute angle, otherwise the angle is
  // relative to the location of the leading edge
  fleadingAlpha = a;
  invalidate(this);
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::leadingAlpha(void)
{
  return fleadingAlpha;
}
//---------------------------------------------------------------------------------------

void tPropHubSurface::setTrailingAlpha(tReal a)
{
  // If alpha is smaller than 0 the angle is an absolute angle, otherwise the angle is
  // relative to the location of the leading edge
  ftrailingAlpha = a;
  invalidate(this);
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::trailingAlpha(void)
{
  return ftrailingAlpha;
}
//---------------------------------------------------------------------------------------

tReal tPropHubSurface::getValueAtCurve(tCurve *c, tReal xx)
{
  int j;
  tReal dT,posT;
  tVector x;

  posT = 0.5;
  dT = 0.25;

  if (c){
    for (j=0;j<iterations;j++){
      x = c->vectorAt(posT);
      if (x.x > xx){
        posT -= dT;
      } else {
        posT += dT;
      }
      dT /= 2.;
    }
    return (sqrt(x.y*x.y+x.z*x.z));
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------
