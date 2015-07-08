#include "element/curve/tCurve.h"

#include "classes/utils.h"

tCurve::tCurve(void *theOwner): tPaintableElement(theOwner)
{
	tRes = 8;
  ftCache = NULL;
  validCache = false;
  arrowhead = 0.;
  flineWidth = 1.;
  isProportionalToLength = false;
  dlength = NULL;
}
//-----------------------------------------------------------------------------
tCurve::~tCurve()
{
	if (ftCache){
		free(ftCache);
	}
}
//-----------------------------------------------------------------------------

void tCurve::update(void)
{
  if (!isValid){
    refreshCurve();
  }
  tElement::update();
}

//-----------------------------------------------------------------------------

void tCurve::invalidate(tElement *sender)
{

  if (validCache && !blockInvalidateList.contains(sender)){//!!!! ToDo: Streng genommen sollte nicht nur sender verfolgt werden, sondern alle Elemente die von diesem abhaengen
    validCache = false;
  }
  tElement::invalidate(sender);//hier stand mal "this", machte aber keinen Sinn, oder?
}
//-----------------------------------------------------------------------------



void tCurve::paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector &defaultN, const bool& isSelected){
    tVector *x;
    tReal pos = arrowheadPos();
    int tRes = tResolution();
    glNormal3f(defaultN.x,defaultN.y,defaultN.z);
    //iCurve* intrface;
    //intrface = dynamic_cast<iCurve*>(c->intrface());
    x = tCache();
    if (isSelected) {
      glLineWidth(lineWidth()*3);
    } else {
      glLineWidth(lineWidth());
    }
    glBegin(GL_LINE_STRIP);
      for (int t=0;t<=tRes;t++) {
        glVertex3d (x->x,x->y,x->z);
        x++;
      }
    glEnd();
    glLineWidth(1);
    if (pos != 0.) {
     // paintCone(c->vectorAt(fabs(pos)),c->gradientAt(fabs(pos))*(pos/fabs(pos))*0.5,c->length()*0.1,10);
    }
}


void tCurve::refreshCurve(void)
{
  // Falls der Laufparameter t proportional zur Lauflaenge sein sollte, muss zwischen dem Parameter s und t eine
  // Transformation statt finden. Hierzu werden ein paar WErte benoetigt, die nicht immer wieder neu berechnet werden
  // sollten.
  int i;
  if (isProportionalToLength){
    updateCache();
    dlength = (tReal*)realloc(dlength,(tRes+1)*sizeof(tReal));
    dlength[0] = 0.;
    for (i=0;i<tRes;i++){
      dlength[i+1] = dlength[i] + (ftCache[i]-ftCache[i+1]).length();
    }
    for (i=1;i<=tRes;i++){
      dlength[i] = dlength[i]/dlength[tRes];
    }
  } else {
    if (dlength){
      free(dlength);
      dlength = NULL;
    }
  }
}
//-----------------------------------------------------------------------------

void tCurve::updateCache(void)
{
  setElementLocked;
  int t;

  if (!validCache){
    ftCache = (tVector*)realloc(ftCache,(tRes+1)*sizeof(tVector));
		for (t=0;t<=tRes;t++){
			ftCache[t] = vectorAt((tReal)t/(tReal)tRes);
		}
    validCache = true;
  }
}
//-----------------------------------------------------------------------------

void tCurve::setTResolution (int res)
{
  tRes = res;
  setElementLocked
  invalidate(this);
}
//-----------------------------------------------------------------------------

//tVector tCurve::vectorAtArcLength(tReal s)
//{
//  setElementLocked
//	return vectorAt(getTFromS(s));
//}
////-----------------------------------------------------------------------------

tVector tCurve::xMin(void)
{
  setElementLocked
	tVector x,x1;
	int t;

	update();

	x = vectorAt(0.);
	for (t=1;t<=tRes;t++){
		x1 = vectorAt((tReal)t/(tReal)tRes);
		x.x = min(x.x,x1.x);
		x.y = min(x.y,x1.y);
		x.z = min(x.z,x1.z);
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tCurve::xMax(void)
{
  setElementLocked
	tVector x,x1;
	int t;

	update();

	x = vectorAt(0.);
	for (t=1;t<=tRes;t++){
		x1 = vectorAt((tReal)t/(tReal)tRes);
		x.x = max(x.x,x1.x);
		x.y = max(x.y,x1.y);
		x.z = max(x.z,x1.z);
	}
    return x;
}

//-----------------------------------------------------------------------------

tVector tCurve::vectorAt(tReal t)
{
  update();
  if (isProportionalToLength){
    return tVector(0,0,0);
  } else {
    return vectorAtAccurate(t);
  }
}
//-----------------------------------------------------------------------------

tVector tCurve::gradientAt(tReal t)
{
  setElementLocked
	tVector x0,x1,g;
	tReal dt;
  dt = (tReal)tRes;
//    dt = (tReal)(iface->getPropertyInt("t Resolution"));
	if (dt > 0){
		dt = 1./dt/10;
	} else {
		dt = 1./100.;
	}
	x0 = vectorAt(t-dt);
	x1 = vectorAt(t+dt);
	g = (x1-x0)*(1./2./dt);
	return g;
}
//-----------------------------------------------------------------------------

tVector tCurve::curvatureAt(tReal t)
{
  setElementLocked
	tVector x,x0,x1,c;
	tReal dt;
  dt = (tReal)tRes;
	if (dt > 0){
		dt = 1./dt/10;
	} else {
		dt = 1./100.;
	}
	x = vectorAt(t);
	x0 = vectorAt(t-dt);
	x1 = vectorAt(t+dt);
	c = (x1-x*2.+x0)*(1./dt/dt);
	return c;
}
//-----------------------------------------------------------------------------

tReal tCurve::length(void)
{
  setElementLocked
	tVector x0,x;
	tReal l;
	int i,n;

	update();

  n = tRes*10;

	l = 0.;
	x0 = vectorAt(0.);
	for  (i=0;i<n;i+=1){
		x = vectorAt(((tReal)i+1.)/(tReal)n);
		l += (x-x0).length();
		x0 = x;
	}
	return l;
}
//-----------------------------------------------------------------------------

//tReal tCurve::getSFromT(tReal t)
//{
//  setElementLocked
//	tVector x0,x;
//	int i,n,n1;
//	tReal l,l1,dt;
//	tList<tReal> ll;
//
//	update();
//	if (t>1. || t < 0.){
//		return t;
//	} else {
//		n = tRes*10;
//		dt = 1./(tReal)n;
//		x0 = vectorAt(0.);
//
//		l = 0.;
//		for  (i=0;i<n;i+=1){
//			x = vectorAt(((tReal)i+1.)/(tReal)n);
//			ll.append((x-x0).length());
//			x0 = x;
//			l += ll.last();
//		}
//
//		n1 = (int)(floor)(t/dt);
//		l1 = 0.;
//		for (i=0;i<n1;i++){
//			l1 += ll.at(i);
//		}
//		return l1/l+(t/dt-(tReal)n1)*ll.at(n1-1)/l;
//	}
//}
////-----------------------------------------------------------------------------
//
//tReal tCurve::getTFromS(tReal s)
//{
//  setElementLocked
//	tVector x0,x;
//	int i,n;
//	tReal l,l1,dt;
//	tList<tReal> ll;
//
//	update();
//	if (s > 1. || s < 0.){
//		return s;
//	} else {
//
//		n= tRes*10;
//		dt = 1./(tReal)n;
//		l = 0.;
//		x0 = vectorAt(0.);
//		for  (i=0;i<n;i+=1){
//			x = vectorAt(((tReal)i+1.)/(tReal)n);
//			ll.append((x-x0).length());
//			x0 = x;
//			l += ll.last();
//		}
//		l1 = s*l;
//		for (i=0;l1-ll.at(i) > 0 && i<n;i++){
//			l1 -= ll.at(i);
//		}
//		return (tReal)i/(tReal)n+l1/ll.at(i-1)*dt;
//	}
//}
