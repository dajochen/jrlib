#include "element/surface/tSurface.h"

#include "classes/utils.h"


tSurface::tSurface(void *theOwner): tElement(theOwner)
{
  isAccurate = true;
  fOrientation = true;
  fuDiv = 8;
  fvDiv = 8;
  fuRes = 4;
  fvRes = 4;
  fuvCache = NULL;
  validCache = false;
}
//-----------------------------------------------------------------------------

tSurface::~tSurface()
{
	if (fuvCache){
		free(fuvCache);
	}
}
//-----------------------------------------------------------------------------

void tSurface::invalidate(tElement *sender)
{
  validCache = false;
  tElement::invalidate(sender);// hier stand mal "this"???
}
//-----------------------------------------------------------------------------

void tSurface::updateCache(void)
{
  setElementLocked
  int u,v,nu,nv;

  if (!validCache){
    nu = fuDiv*fuRes;
    nv = fvDiv*fvRes;
    fuvCache = (tVector*)realloc(fuvCache,(nu+1)*(nv+1)*sizeof(tVector));
    for (v=0;v<=nv;v++){
    	for (u=0;u<=nu;u++){
        fuvCache[v*(nu+1)+u] = vectorAtAccurate((tReal)u/(tReal)nu,(tReal)v/(tReal)nv);
      }
    }
    validCache = true;
  }
}

//-----------------------------------------------------------------------------
tVector tSurface::xMin(void)
{
  setElementLocked
	tVector x,x1;
	int i,j;

	update();


	x1 = vectorAt(0.,0.);
	for (i=0;i<=fuRes;i++){
		for (j=0;j<=fvRes;j++){
			x1 = vectorAt((tReal)i/(tReal)fuRes,(tReal)j/(tReal)fvRes);
			x.x = min(x.x,x1.x);
			x.y = min(x.y,x1.y);
			x.z = min(x.z,x1.z);
		}
	}
	return x;
}
//-----------------------------------------------------------------------------

tVector tSurface::vectorAt(tReal u, tReal v){
  setElementLocked
  update();
  if (isAccurate || u<0. || u>1. || v<0. || v>1. ){
    return vectorAtAccurate(u,v);
  } else {
    tVector x;
    int i, j, ni,nj;
    tReal U, V, uu, vv;

    updateCache();

    ni = fuDiv*fuRes;
    nj = fvDiv*fvRes;
    U = u*ni;
    V = v*nj;
    i = (int)floor(U);
    j = (int)floor(V);
    uu = U-(tReal)i;
    vv = V-(tReal)j;
    if (j==nj){
    	j--;
    	vv += 1.;
    }
    if (i==ni){
    	i--;
    	uu += 1.;
    }
    x = (fuvCache[j*(ni+1)+i]*(1-uu)+fuvCache[j*(ni+1)+i+1]*uu)*(1-vv)
       +(fuvCache[(j+1)*(ni+1)+i]*(1-uu)+fuvCache[(j+1)*(ni+1)+i+1]*uu)*vv;
    return x;
  }
}
//-----------------------------------------------------------------------------

tVector tSurface::normalVectorAt(tReal u, tReal v){
  setElementLocked
  tVector n,x,x1,x2;
//  tReal RES;
  x = vectorAt(u,v);
/*  if (iface){
    RES = (tReal)max(((iSurface*)iface)->UResolution()*((iSurface*)iface)->UDivisions(),
                         ((iSurface*)iface)->VResolution()*((iSurface*)iface)->VDivisions());
  } else {
    RES = 20.;
  }*/
  x1 = vectorAt(u+1./(tReal)(fuRes*fuDiv),v)-x;
  x2 = vectorAt(u,v+1./(tReal)(fvRes*fvDiv))-x;
  n = x1%x2;
  n = n*(1./n.length());
  return n;
}

//-----------------------------------------------------------------------------

tVector tSurface::xMax(void)
{
  setElementLocked
	tVector x,x1;
	int i,j;

	update();

	x1 = vectorAt(0.,0.);
	for (i=0;i<=fuRes;i++){
		for (j=0;j<=fvRes;j++){
			x1 = vectorAt((tReal)i/(tReal)fuRes,(tReal)j/(tReal)fvRes);
			x.x = max(x.x,x1.x);
			x.y = max(x.y,x1.y);
			x.z = max(x.z,x1.z);
		}
	}
	return x;
}
//-----------------------------------------------------------------------------

void tSurface::setUDiv(int UDIV)
{
  setElementLocked
  fuDiv = UDIV;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tSurface::setURes(int URES)
{
  setElementLocked
  fuRes = URES;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tSurface::setVDiv(int VDIV)
{
  setElementLocked
  fvDiv = VDIV;
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tSurface::setVRes(int VRES)
{
  setElementLocked
  fvRes = VRES;
  invalidate(this);
}
//-----------------------------------------------------------------------------


