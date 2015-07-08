#include "element/surface/tCLoft.h"

#include "classes/utils.h"

tCLoft::tCLoft(void *theOwner): tSurface(theOwner)
{
	A = NULL;
  fDegree = 3;
	//uDivisions = 8;
}
//-----------------------------------------------------------------------------

tCLoft::~tCLoft()
{
	clearMatrixA();
	int i,n;
	n = uCurves.count();
	for (i=0;i<n;i++){
		uCurves.at(i)->removeDependent(this);
	}
}
//-----------------------------------------------------------------------------

void tCLoft::clear(void)
{
  setElementLocked
  int i;
  tCurve *c;

  clearMatrixA();
  for (i=0; i<uCurves.count(); i++){
    c = uCurves.at(i);
    if(c){
      c->removeDependent(this);
    }
  }
  uCurves.clear();
}

//-----------------------------------------------------------------------------

void tCLoft::clearMatrixA()
{
  int i,j,k;
  int uPartitioning, vPartitioning;
  uPartitioning = fuDiv*fuRes;
  vPartitioning = uCurves.count()-1;
  if (A){
    for (i=0; i<uPartitioning; i++){
      for (j=0; j<vPartitioning; j++){
        for (k=0;k<4;k++){
          free(A[i][j][k]);
        }
        free(A[i][j]);
      }
      free(A[i]);
    }
    free (A);
    A = NULL;
  }
}
//-----------------------------------------------------------------------------

void tCLoft::setUDiv(int UDIV)
{
  setElementLocked
  clearMatrixA();
  tSurface::setUDiv(UDIV);
}
//-----------------------------------------------------------------------------

void tCLoft::setURes(int URES)
{
  setElementLocked
  clearMatrixA();
  tSurface::setURes(URES);
}
//-----------------------------------------------------------------------------

iElement* tCLoft::intrface(void)
{
	if (iface == NULL){
		iface = new iCLoft(this);
	}
	return iface;
}
//-----------------------------------------------------------------------------

tVector tCLoft::xMin(void)
{
  setElementLocked
	tVector x,x1;
	int i,n;

	n = uCurves.count();
	if (n > 0){
		x = uCurves.at(0)->xMin();
		for (i=1;i<n;i++){
			x1 = uCurves.at(i)->xMin();
			x.x = min(x.x,x1.x);
			x.y = min(x.y,x1.y);
			x.z = min(x.z,x1.z);
		}
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tCLoft::xMax(void)
{
  setElementLocked
	tVector x,x1;
	int i,n;

	n = uCurves.count();
	if (n > 0){
		x = uCurves.at(0)->xMax();
		for (i=1;i<n;i++){
			x1 = uCurves.at(i)->xMax();
			x.x = max(x.x,x1.x);
			x.y = max(x.y,x1.y);
			x.z = max(x.z,x1.z);
		}
	} else {
		x.setZero();
	}
	return x;
}
//-----------------------------------------------------------------------------

void tCLoft::transformUV(tReal u,tReal v,int *i, int *j, tReal *uEps, tReal *vEps)
{ // Wandelt einen u,v Paar in das aequivalente i-j-uEps-vEps-Quadrupel um.
	tReal du, dv;
  int uPartitioning, vPartitioning;
  uPartitioning = fuDiv*fuRes;
  vPartitioning = uCurves.count()-1;

  du = 1./uPartitioning;
  dv = 1./vPartitioning;
  *i = (int)floor(u*uPartitioning);
  *j = (int)floor(v*vPartitioning);
  *i = min(*i,uPartitioning-1);
  *j = min(*j,vPartitioning-1);
  *i = max(*i,0);
  *j = max(*j,0);
  *uEps = u-(*i)*du;
  *vEps = v-(*j)*dv;
}

//-----------------------------------------------------------------------------

tVector tCLoft::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked
  tVector x;
  int i,j,k1,k2;
  tReal uEps,vEps,uu,vv;

	update();
    if (A && uCurves.count()){
	  transformUV(u,v,&i,&j,&uEps,&vEps);

	// Das Polynom ausrechnen
	  x.setZero();
	  uu = 1;
	  for (k1=0;k1<4;k1++){
	    vv = 1;
	    for (k2=0;k2<4;k2++){
	      x = x+ A[i][j][k1][k2]*uu*vv;
	      vv *= vEps;
	    }
	    uu *=uEps;
	  }
	} else {
		x.setZero();
	}
  return x;
}
//-----------------------------------------------------------------------------

tVector tCLoft::normalVectorAt(tReal u, tReal v)
{
  setElementLocked
	tVector n,u_,v_; // Ableitung nach u und v.

  tVector x;
  int i,j,k1,k2;
  tReal uEps,vEps,uu,vv;

    if (uCurves.count()>1){
		update();
	  transformUV(u,v,&i,&j,&uEps,&vEps);

	  u_.setZero();
	  for (k1=1;k1<4;k1++){
	  	uu = pow(uEps,(k1-1))*k1;
	    vv = 1;
	    for (k2=0;k2<4;k2++){
	      u_ = u_ + A[i][j][k1][k2]*uu*vv;
	      vv *= vEps;
	    }
	  }

		v_.setZero();
	  for (k1=0;k1<4;k1++){
	  	uu = pow(uEps,k1);
	    for (k2=1;k2<4;k2++){
	    	vv = pow(vEps,(k2-1))*k2;
	      v_ = v_ + A[i][j][k1][k2]*uu*vv;
	    }
	  }

	  n = u_%v_;

	  uu = n.length();
	  if (uu > 0){
	  	n = n*(1./uu);
	  }
	} else {
		n.setZero();
	}
	return n;
}
//-----------------------------------------------------------------------------

void tCLoft::appendCurve(tCurve* c)
{
  setElementLocked
  clearMatrixA();
	if (c){
		uCurves.append(c);
		c->addDependent(this);
    invalidate(this);
	}
}
//-----------------------------------------------------------------------------

void tCLoft::insertCurve(int index, tCurve* c)
{
  setElementLocked
  clearMatrixA();
	if (c){
		uCurves.insert(index,c);
		c->addDependent(this);
		invalidate(this);
	}
}
//-----------------------------------------------------------------------------

void tCLoft::insertGroup(int index, tGroup *g)
{
  setElementLocked
	int i,n;
	tCurve *c;
	if (g){
		n = g->nElements();
		for (i=0;i<n;i++){
			c = dynamic_cast<tCurve*>(g->element(i));
			if (c){
				insertCurve(index,c);
				index++;
			}
		}
	}
}
//-----------------------------------------------------------------------------

void tCLoft::insertList(int index, tList<tElement*> *l)
{
  setElementLocked
	int i,n,j;
	tCurve *c;
	tGroup *g;
	if (l){
		n = l->count();
		for (i=0;i<n;i++){
			c = dynamic_cast<tCurve*>(l->at(i));
			if (c){
				insertCurve(index,c);
				index++;
			} else {
				g = dynamic_cast<tGroup*>(l->at(i));
				if (g){
					j = uCurves.count();
					insertGroup(index,g);
					index += uCurves.count()-j;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------

void tCLoft::setCurves(tList<tElement*> list)
{
  setElementLocked;
  removeAllCurves();
  insertList(0,&list);
}
//-----------------------------------------------------------------------------

tList<tElement*> tCLoft::curves(void)
{
  int i;
  tList<tElement*> l;
  for (i=0;i<uCurves.count();i++){
    l.append(uCurves.at(i));
  }
  return l;
}
//-----------------------------------------------------------------------------

void tCLoft::removeAllCurves(void)
{
  int i;
  for (i=0;i<uCurves.count();i++){
    uCurves.at(i)->removeDependent(this);
  }
  uCurves.clear();
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tCLoft::refresh(void)
{
	int i,j,k,k1,k2;
  tList<tElement*> List,Points; //in "List" sind die Stuetzpunkte der vSplines
                                //in "Points" sind die Stuetzpunkte der Ableitungen
  tList<tCSpline*> vCurves;
  tCSpline *S;
  tPoint ***O,       // Stuetzpunkt
         ***P,       // Gradient der uCurves an den Stuetzstellen
         ***Q,       // Gradient der vCurves an den Stuetzstellen
         ***R;       // Krümmung an den Stuetzstellen
  tVector C[4][4],D[4][4],x;
  tReal B[4][4],E[4][4],h;

  clearMatrixA();

  int uPartitioning, vPartitioning;
  uPartitioning = fuDiv*fuRes;
  vPartitioning = uCurves.count()-1;

//  vRes = uCurves.count()-1;
  if (uPartitioning > 0 && vPartitioning > 0){
// Die Monstermatrix fuer die Koeffizienten der bikubischen Flaechen
// Speicher reservieren und initialisieren
    if (A == NULL){
      A = (tVector****)malloc(uPartitioning*sizeof(tVector***));
      for (i=0;i<uPartitioning;i++){
        A[i] = (tVector***)malloc(vPartitioning*sizeof(tVector**));
        for (j=0;j<vPartitioning;j++){
          A[i][j] = (tVector**)malloc(4*sizeof(tVector*));
          for (k=0;k<4;k++){
            A[i][j][k] = (tVector*)malloc(4*sizeof(tVector));
          }
        }
      }
    }
    if (fDegree == 1){
    	tVector x00,x10,x01,x11;
			for (i=0;i<uPartitioning;i++){
				for (j=0;j<vPartitioning;j++){
					x00 = uCurves.at(j)->vectorAt((tReal)i/(tReal)uPartitioning);
					x01 = (uCurves.at(j+1)->vectorAt((tReal)i/(tReal)uPartitioning));
					x10 = (uCurves.at(j)->vectorAt((tReal)(i+1)/(tReal)uPartitioning));
					x11 = (uCurves.at(j+1)->vectorAt((tReal)(i+1)/(tReal)uPartitioning));
					for (k1=0;k1<4;k1++){
						for (k2=0;k2<4;k2++){
							if (k1==0 && k2 == 0){
								x = x00;
							} else if (k1==0 && k2 == 1){
								x = (x01-x00)*(tReal)vPartitioning;
							} else if (k1==1 && k2 == 0){
								x = (x10-x00)*(tReal)uPartitioning;
							} else if (k1==1 && k2 == 1){
//								x.setZero();
								x = (x11- (x10-x00) - (x01-x00) - x00)*(tReal)(uPartitioning*vPartitioning);
							} else {
								x.setZero();
							}
							A[i][j][k1][k2] = x;
						}
					}
				}
			}
    } else if (fDegree == 3){
			//Die  Ableitungen der Splines erstellen
			// Speicher allokieren und initialisieren
			O = (tPoint***) malloc((uPartitioning+1)*sizeof(tPoint**));
			P = (tPoint***) malloc((uPartitioning+1)*sizeof(tPoint**));
			Q = (tPoint***) malloc((uPartitioning+1)*sizeof(tPoint**));
			R = (tPoint***) malloc((uPartitioning+1)*sizeof(tPoint**));
			for (i=0;i<=uPartitioning;i++){
				O[i] = (tPoint**) calloc((vPartitioning+1),sizeof(tPoint*));
				P[i] = (tPoint**) calloc((vPartitioning+1),sizeof(tPoint*));
				Q[i] = (tPoint**) calloc((vPartitioning+1),sizeof(tPoint*));
				R[i] = (tPoint**) calloc((vPartitioning+1),sizeof(tPoint*));
			}

			// Werte der Ableitungen setzen
			for (i=0;i<=uPartitioning;i++){
				List.clear();
				for (j=0;j<=vPartitioning;j++){
					O[i][j] = new tPoint(this,uCurves.at(j)->vectorAt((tReal)i/(tReal)uPartitioning));
					List.append(O[i][j]);
				}
				S = new tCSpline(this);
				S->setCSplineType(jrCSVortexBased);
	//      S->setCSplineType(jrCSLengthBased);
				vCurves.append(S);
				S->addVertices(&List);
			}

			// Die Ableitungen in u und v
			for(i=0;i<=uPartitioning;i++){
				for (j=0;j<=vPartitioning;j++){
					P[i][j] = new tPoint(this,uCurves.at(j)->gradientAt((tReal)i/(tReal)uPartitioning));
					Q[i][j] = new tPoint(this,vCurves.at(i)->gradientAt((tReal)j/(tReal)vPartitioning));
				}
			}
			// Die Kruemmung in u und v-Richtung mitteln.
			for(i=0;i<=uPartitioning;i++){
				for (j=0;j<=vPartitioning;j++){
					tVector k1,k2;
					k2 = uCurves.at(j)->curvatureAt((tReal)i/(tReal)uPartitioning);
					k1 = vCurves.at(i)->curvatureAt((tReal)j/(tReal)vPartitioning);
					if (-k1.x < k2.x && k2.x <k1.x){
						k1.x = k2.x;
					}
					if (-k1.y < k2.y && k2.y <k1.y){
						k1.y = k2.y;
					}
					if (-k1.z < k2.z && k2.z <k1.z){
						k1.z = k2.z;
					}
					R[i][j] = new tPoint(this, k1);
	//        R[i][j] = new tPoint(this, vCurves.at(i)->curvatureAt((tReal)j/(tReal)vRes));
	//        R[i][j] = new tPoint(this, uCurves.at(j)->curvatureAt((tReal)i/(tReal)uDivisions));
	//        R[i][j] = new tPoint(this,( uCurves.at(j)->curvatureAt((tReal)i/(tReal)uDivisions)
	//                                  + vCurves.at(i)->curvatureAt((tReal)j/(tReal)vRes))*0.5);
				}
			}

			h = 1./(tReal)uPartitioning;
			B[0][0]=1.;       B[0][1]=0.;    B[0][2]=0.;        B[0][3]=0.;
			B[1][0]=0.;       B[1][1]=1.;    B[1][2]=0.;        B[1][3]=0.;
			B[2][0]=-3./h/h;  B[2][1]=-2./h; B[2][2]=3./h/h;    B[2][3]=-1./h;
			B[3][0]=2./h/h/h; B[3][1]=1./h/h;  B[3][2]=-2./h/h/h; B[3][3]=1./h/h;
			h = 1./(tReal)vPartitioning;
			E[0][0]=1.;       E[0][1]=0.;    E[0][2]=0.;        E[0][3]=0.;
			E[1][0]=0.;       E[1][1]=1.;    E[1][2]=0.;        E[1][3]=0.;
			E[2][0]=-3./h/h;  E[2][1]=-2./h; E[2][2]=3./h/h;    E[2][3]=-1./h;
			E[3][0]=2./h/h/h; E[3][1]=1./h/h;  E[3][2]=-2./h/h/h; E[3][3]=1./h/h;

				for (i=0;i<uPartitioning;i++){
				for (j=0;j<vPartitioning;j++){
					C[0][0] = *O[i][j];//*(uSpline[j]->getVector((tReal)i/(tReal)uRes);
					C[0][1] = *Q[i][j];
					C[0][2] = *O[i][j+1];//*(uSpline[j+1]->getVector((tReal)i/(tReal)uRes);
					C[0][3] = *Q[i][j+1];
					C[1][0] = *P[i][j];
					C[1][1] = *R[i][j];
					C[1][2] = *P[i][j+1];
					C[1][3] = *R[i][j+1];
					C[2][0] = *O[i+1][j];//*(uSpline[j]->getVector((tReal)(i+1)/(tReal)uRes);
					C[2][1] = *Q[i+1][j];
					C[2][2] = *O[i+1][j+1];//*(uSpline[j+1]->getVector((tReal)(i+1)/(tReal)uRes);
					C[2][3] = *Q[i+1][j+1];
					C[3][0] = *P[i+1][j];
					C[3][1] = *R[i+1][j];
					C[3][2] = *P[i+1][j+1];
					C[3][3] = *R[i+1][j+1];
		// Matrizenmultiplikation A = B*C*E in den drei Koordinaten

					for (k1=0;k1<4;k1++){
						for (k2=0;k2<4;k2++){
							 x.setZero();
							 for(k=0;k<4;k++){
								 x = x + C[k][k2]*B[k1][k];
							 }
							 D[k1][k2] = x;
						}
					}
					for (k1=0;k1<4;k1++){
						for (k2=0;k2<4;k2++){
							 x.setZero();
							 for(k=0;k<4;k++){
								 x = x + D[k1][k]*E[k2][k];
							 }
							 A[i][j][k1][k2] = x;
						}
					}
				}
			}

			for (i=0;i<vCurves.count();i++){
				vCurves.at(i)->releaseOwner(this);
			}
			vCurves.clear();

			for (i=0;i<=uPartitioning;i++){
				for (j=0;j<=vPartitioning;j++){
					O[i][j]->releaseOwner(this);
					P[i][j]->releaseOwner(this);
					Q[i][j]->releaseOwner(this);
					R[i][j]->releaseOwner(this);
				}
			}
			for (i=0;i<=uPartitioning;i++){
				free(O[i]);
				free(P[i]);
				free(Q[i]);
				free(R[i]);
			}
			free(O);
			free(P);
			free(Q);
			free(R);
    } else {
			for (i=0;i<uPartitioning;i++){
				for (j=0;j<vPartitioning;j++){
					for (k1=0;k1<4;k1++){
						for (k2=0;k2<4;k2++){
							if (k1==0 && k2 == 0){
								x = uCurves.at(j)->vectorAt((tReal)i/(tReal)uPartitioning);
							} else {
								x.setZero();
							}
							A[i][j][k1][k2] = x;
						}
					}
				}
			}
    }
  } else {
      A = NULL;
  }
}

//-----------------------------------------------------------------------------
