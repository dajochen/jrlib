#include "element/curve/tCSpline.h"
#include "classes/tSolve.h"

#include "classes/utils.h"

tCSpline::tCSpline(void *theOwner): tCurve(theOwner)
{
  initialize();
}
tCSpline::tCSpline(void *theOwner, tList<tElement*> *l) : tCurve(theOwner)
{
  initialize();
  insertList(0, l);
}

//-----------------------------------------------------------------------------
tCSpline::~tCSpline()
{
  clear();
  if (A)
	  free(A);
  if (B)
	  free(B);
  if (C)
	  free(C);
  if (D)
	  free(D);
}
//-----------------------------------------------------------------------------

void tCSpline::initialize(void)
{
  A = B = C = D = NULL;
  theCSplineType = jrCSVortexBased;
  fDegree = 3;
}
//-----------------------------------------------------------------------------

bool tCSpline::addVortex(tDot *P)
{
  setElementLocked
  if (P->addDependent(this)){
    vertex.append(P);
    invalidate(this);
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------

bool tCSpline::insertVortex(int i, tElement *el)
{
  setElementLocked
  tDot *d;
  d = dynamic_cast<tDot*>(el);
  if (d && d->addDependent(this)){
    vertex.insert(i,d);
    invalidate(this);
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------

void tCSpline::insertList(int index, tList<tElement*> *l)
{
  setElementLocked
  int i,I;
  if (l){
    I = 0;
    for (i=0;i<l->count();i++){
      if (insertVortex(index+I,l->at(i))){
        I++;
      }
    }
  }
}
//-----------------------------------------------------------------------------

void tCSpline::addVertices(tGroup *Group)
// Die Elemente der Gruppe werden dem Spline hinzugef�gt. �ndert sich die Gruppe hat dies keine Auswirkungen auf den Spline.
{
  setElementLocked
  tDot* P;
  tGroup *G;
  int i;
  for (i=0;i<Group->nElements();i++){
    P = dynamic_cast<tDot*>(Group->element(i));
    G = dynamic_cast<tGroup*>(Group->element(i));
    if (P){
      if (P->addDependent(this)){
        vertex.append(P);
      }
    } else if (G){
      addVertices(G);
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tCSpline::addVertices(tList<tElement*> *List)
{
  setElementLocked
  tDot* P;
  tGroup *G;
  int i;
  for (i=0;i<List->count();i++){
    P = dynamic_cast<tDot*>(List->at(i));
    G = dynamic_cast<tGroup*>(List->at(i));
    if (P){
      if (P->addDependent(this)){
        vertex.append(P);
      }
    } else if (G){
      addVertices(G);
    }
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------
tList<tElement*> tCSpline::vertices(void)
{
  setElementLocked
  int i;
  tList<tElement*> l;
  for (i=0;i<vertex.count();i++){
    l.append(vertex.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tCSpline::setVertices(tList<tElement*> List)
{
  setElementLocked
  clear();
  addVertices(&List);
}
//-----------------------------------------------------------------------------

tDot* tCSpline::getVortex(int index)
{
  setElementLocked
	if (index>=0 && index < vertex.count()){
		return vertex.at(index);
	} else {
		return NULL;
	}
}
//-----------------------------------------------------------------------------

tReal tCSpline::tAtVortex(int index)
{
  setElementLocked
  update();
  if (index < 0){
    return -1.;
  } else if (index >= dt.count()){
    return 2.;
  } else {
    return dt.at(index);
  }

}
//-----------------------------------------------------------------------------

void tCSpline::clear(void)
{
  setElementLocked
	int i,ni;
	ni = vertex.count();
  for (i=0;i<ni;i++){
    vertex.at(i)->removeDependent(this);
  }
  vertex.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

iElement* tCSpline::intrface(void)
{
	if (iface == NULL) {
		iface = new iCSpline(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tCSplineType tCSpline::CSplineType(void)
{
  setElementLocked
	return theCSplineType;
}
//-----------------------------------------------------------------------------

void tCSpline::setCSplineType(int t){
  setElementLocked
  t = t%2;
  if (t==jrCSVortexBased){
    theCSplineType = jrCSVortexBased;
  } else if (t==jrCSLengthBased) {
    theCSplineType = jrCSLengthBased;
  }
	invalidate(this);
}
//-----------------------------------------------------------------------------

int tCSpline::degree(void)
{
	setElementLocked
	return fDegree;
}
//-----------------------------------------------------------------------------

void tCSpline::setDegree(int deg)
{
	setElementLocked
	fDegree = deg;
	invalidate(this);
}
//-----------------------------------------------------------------------------

tVector tCSpline::vectorAtAccurate(tReal t)
{
  setElementLocked
	int i;
	tReal tt;
	tVector x;

  update();
	if (getSectionFromT(t, &i, &tt)){
		x = A[i]*tt*tt*tt+B[i]*tt*tt+C[i]*tt+D[i];
	} else {
		if (vertex.count() == 1){
			x = vertex.at(0)->vector();
		} else {
			x.setZero();
		}
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tCSpline::gradientAt(tReal t)
{
  setElementLocked
	int i;
	tReal tt;
	tVector x;

  update();
	if (getSectionFromT(t, &i, &tt)){
		x = A[i]*3.*tt*tt+B[i]*2.*tt+C[i];
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tCSpline::curvatureAt(tReal t){
  setElementLocked
	int i;
	tReal tt;
	tVector x;

  update();
	if (getSectionFromT(t, &i, &tt)){
		x = A[i]*6.*tt+B[i]*2.;
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

bool tCSpline::getSectionFromT(float t, int *section, tReal *fraction)
{
  // Wandelt die Laufvariable t in den Abschnitt(section) und den darin verbleibenden t-Wert(fraction) um.
  // im Falle einer erfolgreichen Umwandlung wird true zur�ckgegeben.
  int i;
  update();
  if (section && fraction && vertex.count()>1){
    if (t < 0.){
      i = 0;
    } else if (t>=1){
      t -= dt.at(dt.count()-2);
      i = dt.count()-2;
    } else {
      for (i=0;i<dt.count() && t >= dt.at(i) ;i++);
      i--;
      t -= dt.at(i);
    }
    *section = i;
    *fraction = t;
    return true;
  } else {
    return false;
  }
}
//-----------------------------------------------------------------------------

//tVector tCSpline::vectorAtSection(int section, tReal fraction)
//{
//	tReal t;
//	tVector x;
//
//	update();
//	if (vortex.count()){
//		section = min(section,vortex.count()-1);
//		section = max(section,0);
//		t = fraction*(dt.at(section+1)-dt.at(section));
//		x = A[section]*t*t*t+B[section]*t*t+C[section]*t+D[section];
//	} else {
//		x.setZero();
//	}
//	return x;
//}
////-----------------------------------------------------------------------------

void tCSpline::refresh(void)
{
  // Aus den Stuetzpunkten werden die Koeffizienten fuer den Spline neu berechnet
  int i,k,n;
  tReal l,dt1,dt2;
  tJSolve *Coeffs;
  tVector x1,x2;
  tList<tVector> dX;
  tList<tReal> dl;

  n = vertex.count();

  l = 0.;
  dt.clear();
  dl.clear();

  for (i=1;i<n;i++){
    dX.append(vertex.at(i)->vector()-(tVector)*vertex.at(i-1));
  }

  if (theCSplineType == jrCSVortexBased){
    for (i=0;i<=n-1;i++){
      dt.append((tReal)i/(tReal)(n-1));
    }
  } else if (theCSplineType == jrCSLengthBased){
    if (vertex.count() > 1){
      x1 = *vertex.at(0);
      dl.append(0.);
      for (i=1;i<vertex.count();i++){
        x2 = *vertex.at(i);
        l += (x2-x1).length();
        dl.append(l);
        x1 = x2;
      }
      for (i=0;i<dl.count();i++){
        dt.append(dl.at(i)/l);
      }
    }
  }

  if (A)
    free(A);
  if (B)
    free(B);
  if (C)
    free(C);
  if (D)
    free(D);

  if (n > 1){
    A = (tVector*)calloc((n-1),sizeof(tVector));
    B = (tVector*)calloc((n-1),sizeof(tVector));
    C = (tVector*)calloc((n-1),sizeof(tVector));
    D = (tVector*)calloc((n-1),sizeof(tVector));

    if (fDegree == 1){
      for (i=0;i<n-1;i++){
        dt1 = dt.at(i+1)-dt.at(i);
        A[i] = tVector(0,0,0);;
        B[i] = tVector(0,0,0);
        C[i] = (vertex.at(i+1)->vector()-vertex.at(i)->vector())*(1./dt1);
        D[i] = vertex.at(i)->vector();
      }
    } else if (fDegree ==3){
      Coeffs = new tJSolve(n);
      Coeffs->MATRIX[0][0] = 1.;
      for (i=1; i<n-1; i++){
        dt1 = dt.at(i)-dt.at(i-1);
        dt2 = dt.at(i+1)-dt.at(i);
        Coeffs->MATRIX[i][i-1]= dt1;
        Coeffs->MATRIX[i][i]= 2.*(dt1+dt2);
        Coeffs->MATRIX[i][i+1]= dt2;
      }
      Coeffs->MATRIX[n-1][n-1] = 1.;

      for (k=0;k<3;k++){
        Coeffs->RHS[0] = 0.; // Kruemmung am Anfang
        for (i=1;i<n-1;i++){
          dt1 = dt.at(i)-dt.at(i-1);
          dt2 = dt.at(i+1)-dt.at(i);
          Coeffs->RHS[i] = 6.*(*(dX.at(i)[k])/dt2-*dX.at(i-1)[k]/dt1);
        }
        Coeffs->RHS[n-1] = 0.; // Kruemmung am Ende
        Coeffs->solve();
        for (i=0;i<n-1;i++){
          dt1 = dt.at(i+1)-dt.at(i);
          *D[i][k] = *((tVector)*vertex.at(i))[k];
          *C[i][k] = *dX.at(i)[k]/dt1-1./6.*dt1*(Coeffs->x[i+1]+2.*Coeffs->x[i]);
          *B[i][k] = 0.5*Coeffs->x[i];
          *A[i][k] = 1./6./dt1*(Coeffs->x[i+1]-Coeffs->x[i]);
        }
      }
      delete Coeffs;
    } else { // Sonst halt auch was lineares...
      for (i=0;i<n-1;i++){
        dt1 = dt.at(i+1)-dt.at(i);
        A[i] = tVector(0,0,0);;
        B[i] = tVector(0,0,0);
        C[i] = (vertex.at(i+1)->vector()-vertex.at(i)->vector())*(1./dt1);
        D[i] = vertex.at(i)->vector();
      }
    }
  } else {
    A = B = C = D = NULL;
  }
  dl.clear();
}
//-----------------------------------------------------------------------------
