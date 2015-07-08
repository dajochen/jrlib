/*
 * tDuct19A.cpp
 *
 *  Created on: 30.01.2011
 *      Author: Jochen
 */

#include "element/surface/tDuct19A.h"

#include "classes/utils.h"
//#include <iostream>
//using namespace::std;

tDuct19A::tDuct19A(void *theOwner) : tSurface(theOwner) {
  fprop = NULL;
  fAdaptToPropellerPitch = true;
  leTwist = new tCSpline(this);
  teTwist = new tCSpline(this);
  midTwist = new tCSpline(this);
  midAngle = 0.;
  vTE = 0.;
  vLE = 0.;
  xTE = 0.;
  xLE = 0.;
  int i;

  double xPos[] =  {-0.25000, -0.24632, -0.24020, -0.22500, -0.20000, -0.15000, -0.10000, -0.05000, 0.00000, 0.05000, 0.10000, 0.12500, 0.15000, 0.17500, 0.20000, 0.21250, 0.22500, 0.23750, 0.24375, 0.25000, 0.24375, 0.23750, 0.22500, 0.21250, 0.20000, 0.17500, 0.15000, 0.12500, 0.10000, 0.05000, 0.00000, -0.05000, -0.10000, -0.15000, -0.20000, -0.22500, -0.24020, -0.24632, -0.25000},
//         thick[] = { 0.52180,  0.51471,  0.51180,  0.50930,  0.50725,  0.50410,  0.50145,  0.50000, 0.50000, 0.50000, 0.50240, 0.50550, 0.51085, 0.51935, 0.53170, 0.54000, 0.55035, 0.56400, 0.57330, 0.59125, 0.60360, 0.60535, 0.60400, 0.60210, 0.60020, 0.59640, 0.59260, 0.58880, 0.58500, 0.57740, 0.56980,  0.56220,  0.55460,  0.54700,  0.53940,  0.53560,  0.53180,  0.52868,  0.52180};
         thick[] = { 0.5218,  0.52088,  0.51935,  0.51555,  0.50725,  0.5041 ,  0.50145,  0.5,  0.5,  0.5,  0.5024 ,  0.5055 ,  0.51085,  0.51935,  0.5317 ,  0.54 ,  0.55035,  0.564,  0.5733 ,  0.59125,  0.6036 ,  0.60535,  0.604,  0.6021 ,  0.6002 ,  0.5964 ,  0.5926 ,  0.5888 ,  0.585,  0.5774 ,  0.5698 ,  0.5622 ,  0.5546 ,  0.547,  0.5394 ,  0.5306 ,  0.5252496,  0.52309536 ,  0.5218};

  //Parametrisierung der Kontur
  uTEinner=0.125, uTEouter=0.875,  uLE=0.5,  uLEinner=0.375, uLEouter=0.625;
  tTEinner=0.25,  tTEouter=0.75,   tLE=0.48, tLEinner=0.25,  tLEouter=0.75, dtduLE=0.6;

  vlgs = new tJSolve(4);

  innerLGS = new tJSolve(4);
  leLGS = new tJSolve(4);
  outerLGS = new tJSolve(5);

  tList<tElement*> thickL;

  for (i=0;i<39;i++){
    thickL.append(new tPoint(NULL,tVector(xPos[i],0.,thick[i])));
  }
  contur = new tCSpline(NULL,&thickL);
  contur->setTResolution(180);
  contur->setCSplineType(jrCSLengthBased);
  contur->addDependent(this);

}
//-------------------------------------------------------------------------------

tDuct19A::~tDuct19A() {
  if (fprop){
    fprop->removeDependent(this);
  }
  contur->removeDependent(this);
  leTwist->releaseOwner(this);
  teTwist->releaseOwner(this);
  midTwist->releaseOwner(this);
  delete innerLGS;
  delete leLGS;
  delete outerLGS;

  delete vlgs;
}
//-------------------------------------------------------------------------------

void tDuct19A::refresh(void)
{
  setElementLocked;
  leTwist->clear();
  teTwist->clear();
  midTwist->clear();
  tList<tElement*> leList, teList, midList;

  if (fprop){
  // Koordinaten t1, t2 ermitteln an der contur(t).x den Wert  xTE annimmt
    tePos = fprop->camberLineAt(1,0);
    lePos = fprop->camberLineAt(1,1);
    midPos = fprop->camberLineAt(1,0.5);
    xTE = tePos.x;
    xLE = lePos.x;
    tePos.x = 0;
    lePos.x = 0.;
    midPos.x = 0.;
    double tipAngle = asin((tePos-lePos).length()/fprop->diameter())*2.;
    vTE = (1.-tipAngle/(2.*M_PI/fprop->bladeNumber()))/2.;
    vLE = 1.-vTE;
    midAngle = -atan2(midPos.y,midPos.z);

    vTE = 0.25;
    vLE = 0.75;

    int l, k=0;
    for (l=0;l<vlgs->N;l++){ vlgs->MATRIX[k][l]=pow(0,(double)l);}    vlgs->RHS[k]=midAngle-M_PI/fprop->bladeNumber(); k++;
    for (l=0;l<vlgs->N;l++){ vlgs->MATRIX[k][l]=pow(vTE,(double)l);}  vlgs->RHS[k]=-atan2(tePos.y, tePos.z); k++;
    for (l=0;l<vlgs->N;l++){ vlgs->MATRIX[k][l]=pow(vLE,(double)l);}  vlgs->RHS[k]=-atan2(lePos.y, lePos.z); k++;
    for (l=0;l<vlgs->N;l++){ vlgs->MATRIX[k][l]=pow(1.0,(double)l);}  vlgs->RHS[k]=midAngle+M_PI/fprop->bladeNumber(); k++;
    //Ableitung
//    for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(uLE,(double)(l-1))*l;} lgs->RHS[k]=(tLEouter-tLEinner)/(uLEouter-uLEinner)*0.4; k++;
//    for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(1,(double)(l-1))*l;} lgs->RHS[k]=0.4; k++;
    vlgs->solve();



    tTEinner=0.25,  tTEouter=0.75,  tLEinner=0.25,  tLEouter=0.75;
    double dt=0.125;
    for (int i=0;i<30;i++){
      if (contur->vectorAt(tTEinner).x > xTE){ tTEinner -= dt;} else {tTEinner += dt;}
      if (contur->vectorAt(tLEinner).x > xLE){ tLEinner -= dt;} else {tLEinner += dt;}
      if (contur->vectorAt(tTEouter).x < xTE){ tTEouter -= dt;} else {tTEouter += dt;}
      if (contur->vectorAt(tLEouter).x < xLE){ tLEouter -= dt;} else {tLEouter += dt;}
      dt *= 0.5;
    }

    // Verdichtungsfunktionen für die Auflösung der Bereiche an EK und AK
    k=0;
    for (l=0;l<innerLGS->N;l++){ innerLGS->MATRIX[k][l]=pow(0.0,(double)l);} innerLGS->RHS[k]=0.; k++;
    for (l=0;l<innerLGS->N;l++){ innerLGS->MATRIX[k][l]=pow(uTEinner,(double)l);} innerLGS->RHS[k]=tTEinner; k++;
    //Ableitung
    for (l=0;l<innerLGS->N;l++){ innerLGS->MATRIX[k][l]=pow(0.0,max((double)(l-1),0.))*l;} innerLGS->RHS[k]=0.4; k++;
    for (l=0;l<innerLGS->N;l++){ innerLGS->MATRIX[k][l]=pow(uTEinner,(double)(l-1))*l;} innerLGS->RHS[k]=1.; k++;
    innerLGS->solve();

    k=0;
    for (l=0;l<leLGS->N;l++){ leLGS->MATRIX[k][l]=pow(uLEinner,(double)l);} leLGS->RHS[k]=tLEinner; k++;
    for (l=0;l<leLGS->N;l++){ leLGS->MATRIX[k][l]=pow(uLE,(double)l);} leLGS->RHS[k]=tLE; k++;
    //Ableitung
    for (l=0;l<leLGS->N;l++){ leLGS->MATRIX[k][l]=pow(uLEinner,(double)(l-1))*l;} leLGS->RHS[k]=(tLEouter-tLEinner)/(uLEouter-uLEinner)*0.4; k++;
    for (l=0;l<leLGS->N;l++){ leLGS->MATRIX[k][l]=pow(uLE,(double)(l-1))*l;} leLGS->RHS[k]=(tLEouter-tLEinner)/(uLEouter-uLEinner)*0.4; k++;
    leLGS->solve();

    k=0;
    for (l=0;l<outerLGS->N;l++){ outerLGS->MATRIX[k][l]=pow(uLE,(double)l);} outerLGS->RHS[k]=tLE; k++;
    for (l=0;l<outerLGS->N;l++){ outerLGS->MATRIX[k][l]=pow(uTEouter,(double)l);} outerLGS->RHS[k]=tTEouter; k++;
    for (l=0;l<outerLGS->N;l++){ outerLGS->MATRIX[k][l]=pow(1,(double)l);} outerLGS->RHS[k]=1; k++;
    //Ableitung
    for (l=0;l<outerLGS->N;l++){ outerLGS->MATRIX[k][l]=pow(uLE,(double)(l-1))*l;} outerLGS->RHS[k]=(tLEouter-tLEinner)/(uLEouter-uLEinner)*0.4; k++;
    for (l=0;l<outerLGS->N;l++){ outerLGS->MATRIX[k][l]=pow(1,(double)(l-1))*l;} outerLGS->RHS[k]=0.4; k++;
    outerLGS->solve();


    //Kurven fuer die Verdrillung der Duese aufstellen
    int np = uDiv()*uRes();
    if (fAdaptToPropellerPitch){
      for (int i=0;i<np;i++){
        double t = (double)i/(double)(np-1);
        midList.append(new tPoint(NULL, fprop->camberLineAt(1,t)));
        leList.append(new tPoint(NULL, fprop->camberLineAt(1,1.+t)));
        double J=0.4;
        tVector x;
        x = fprop->camberLineAt(1,-1+t);
        x.x = (x.x+xTE+(t-1.)*J*0.5*fprop->diameter())*0.5;
        teList.append(new tPoint(NULL, x));
      }
    } else {
      tVector centerDir;
      centerDir = fprop->camberLineAt(1, 0.5);
      centerDir.x = 0.;
      centerDir = centerDir*(1./centerDir.length());

      for (int i=0;i<np;i++){
        tVector midPoint, lePoint, tePoint;
        double t = (double)i/(double)(np-1);

        midPoint = fprop->camberLineAt(1,t);
        midPoint = tVector(midPoint.x,0.,0.) + centerDir*sqrt(midPoint.y*midPoint.y+midPoint.z*midPoint.z);

        lePoint = fprop->camberLineAt(1,1.+t);
        lePoint = tVector(lePoint.x,0.,0.) + centerDir*sqrt(lePoint.y*lePoint.y+lePoint.z*lePoint.z);

        tePoint = fprop->camberLineAt(1,-1+t);
        tePoint = tVector(tePoint.x,0.,0.) + centerDir*sqrt(tePoint.y*tePoint.y+tePoint.z*tePoint.z);

        midList.append(new tPoint(NULL, midPoint));
        leList.append(new tPoint(NULL, lePoint));

        //double J=0.4;
        //tVector x;
        //x = fprop->camberLineAt(1,-1+t);
        //x.x = (x.x+xTE+(t-1.)*J*0.5*fprop->diameter())*0.5;
        teList.append(new tPoint(NULL, tePoint));
      }

    }

    leTwist->setVertices(leList);
    teTwist->setVertices(teList);
    midTwist->setVertices(midList);
  } else {
    xTE = 0.;
    xLE = 0.;
  }

}
//-------------------------------------------------------------------------------

iElement* tDuct19A::intrface(void)
{
  if (iface == NULL){
    iface = new iDuct19A(this);
  }
  return iface;
}
//-------------------------------------------------------------------------------

tVector tDuct19A::vectorAtAccurate(tReal u, tReal v)
{
  double diameter;
//  double propV,dPropV;
//  int i;
  tVector x,xReturn;
  tVector tipPos;
  update();


  if (fprop){
    double tipAngle;
//    diameter = fprop->diameter();
//    Z = fprop->bladeNumber();

    double tipLocation;
    if (v>=vTE && v<=vLE){
      tipPos = fprop->camberLineAt(1., (v-vTE)/(vLE-vTE));
      tipLocation = tipPos.x;
      tipPos.x = 0.;
      if (v<(vTE+vLE)*0.5){
        tipAngle= midAngle - asin((tipPos-midPos).length()/fprop->diameter())*2.;
      } else {
        tipAngle= midAngle + asin((tipPos-midPos).length()/fprop->diameter())*2.;
      }
    } else {
      double frac = max(v/vTE, 0.);
      if (v <= vTE) {
        frac = max(v/vTE, 0.);
        tipLocation = fprop->camberLineAt(1., 0.5).x*(1.-frac)+ xTE*frac;
      } else {
        frac = min((v-vLE)/(1.-vLE), 1.);
        tipLocation = fprop->camberLineAt(1., 0.5).x*(frac)+ xLE*(1.-frac);
      }
      //tipAngle = midAngle + 2.*M_PI/fprop->bladeNumber()*(v-0.5);
      tipAngle =0.;
      for (int l=0;l<vlgs->N;l++){
        tipAngle += vlgs->x[l]*pow(v, (double)l);
      }
    }
    double tTip=0.25, dt=0.125;
    for (int i=0;i<30;i++){
      if (contur->vectorAt(tTip).x > tipLocation){ tTip -= dt;} else {tTip += dt;}
      dt *= 0.5;
    }

    double ductLEPos = 0.47;
    tJSolve *lgs;
    if (u<0.5){
      lgs = new tJSolve(5);
      int l, k=0;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0,(double)l);} lgs->RHS[k]=0; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.25,(double)l);} lgs->RHS[k]=tTip; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.5,(double)l);} lgs->RHS[k]=ductLEPos; k++;
      //Ableitung
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0,max((double)(l-1),0.))*l;} lgs->RHS[k]=0.2; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.5,max((double)(l-1),0.))*l;} lgs->RHS[k]=0.5; k++;
    } else {
      lgs = new tJSolve(6);
      int l, k=0;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.5,(double)l);} lgs->RHS[k]=ductLEPos; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.65,(double)l);} lgs->RHS[k]=0.53; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(1.0,(double)l);} lgs->RHS[k]=1.0; k++;
      //Ableitung
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.5,max((double)(l-1),0.))*l;} lgs->RHS[k]=0.5; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(0.65,max((double)(l-1),0.))*l;} lgs->RHS[k]=0.6; k++;
      for (l=0;l<lgs->N;l++){ lgs->MATRIX[k][l]=pow(1,max((double)(l-1),0.))*l;} lgs->RHS[k]=0.2; k++;
    }
    lgs->solve();

    double t=0., uu = min(max(u, 0.), 1.);
    for (int l=0;l<lgs->N;l++){
      t += lgs->x[l]*pow(uu,(double)l);
    }
    delete lgs;
    x = contur->vectorAt(t);
    x = x.rotate(tVector(0.,0.,0.), tVector(1.,0.,0.), tipAngle);

    if (u<0 || u>1){
      if (u >=1.){
        u = 1.-u;
      }
      x.x = x.x + 0.5*u;
    }

    return x;
/*
    if ( u>=uTEinner && u<=uLEinner) {
      propCamberLine = midTwist->vectorAt((u-uTEinner)/(uLEinner-uTEinner));
      u = (uTEinner + uLEinner)*0.5;
      double du = (uLEinner-uTEinner)/4.;
      for (i=0;i<30;i++){
        x = contur->vectorAt(u);
        if (x.x > propCamberLine.x){
          u -= du;
        } else {
          u += du;
        }
        du *= 0.5;
      }
    } else {
      if (u>1 || u<0){
        if (u>1.){
          u = 1.-u;
        }
        x = contur->vectorAt(0.);
        x.x = x.x + 0.5*u;
      } else {
        double t=0;
        if (u<uTEinner){
          for (int k=0;k<innerLGS->N;k++){
            t += innerLGS->x[k]*pow(u,(double)k);
          }
          u=t;
        } else if (u>uLEinner && u<=uLE){
          for (int k=0;k<leLGS->N;k++){
            t += leLGS->x[k]*pow(u,(double)k);
          }
          u=t;
        } else {
          for (int k=0;k<lgs->N;k++){
            t += lgs->x[k]*pow(u,(double)k);
          }
        }
        x = contur->vectorAt(t);
      }
      propV = 0.5;
      dPropV = 0.25;
      tCurve* c;
      if (x.x < xTE){
        c = teTwist;
      } else if (x.x<= xLE){
        c = midTwist;
      } else {
        c = leTwist;
      }

      if (fprop){
        for (i=0;i<30;i++){
          propCamberLine = c->vectorAt(propV);
          if (propCamberLine.x > x.x){
            propV -= dPropV;
          } else {
            propV += dPropV;
          }
          dPropV *= 0.5;
        }
      }
    }
    double phi = atan2(propCamberLine.y,propCamberLine.z);
    xReturn = x.rotate(tVector(0.,0.,0.),tVector(1.,0.,0.),-phi+(v-0.5)*2.*M_PI/Z);*/
  } else {
    xReturn.setZero();
  }

  return xReturn;
}
//-------------------------------------------------------------------------------

void tDuct19A::setPropeller(tElement *p)
{
  setElementLocked
  tKaSeries *ka;

  if (fprop){
    fprop->removeDependent(this);
  }
  ka = dynamic_cast<tKaSeries*>(p);
  if (ka && ka->addDependent(this)){
    fprop = ka;
  }
  invalidate(this);
}
//-------------------------------------------------------------------------------
