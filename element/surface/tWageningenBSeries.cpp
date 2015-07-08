/*
 * tWageningenBSeries.cpp
 *
 *  Created on: 14.07.2010
 *      Author: Jochen
 */

#include "element/surface/tWageningenBSeries.h"

tWageningenBSeries::tWageningenBSeries(void *theOwner, tLayer *hostingLayer) : tPropSurface(theOwner)
{
  fPD = 1.0;
  fAEA0 = 0.4;
  fZ = 4;

  int i,j;
  tReal rR[] =      {0.15, 0.2, 0.25 , 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.85 , 0.9, 1},
        xPos[] =    {-1,    -0.95,  -0.9,   -0.8,   -0.7,   -0.6,   -0.5,   -0.4,   -0.2,    0,     0.2,     0.4,    0.5,    0.6,    0.7,    0.8,    0.85,   0.9,    0.95,   1},
        V2[][20] = {{0.0000, 0.0540, 0.1350, 0.2870, 0.4280, 0.5585, 0.6770, 0.7804, 0.9360, 1.0000, 0.9760, 0.8825, 0.8055, 0.7105, 0.5995, 0.4520, 0.3665, 0.2600, 0.1300, 0.0000},
                    {0.0000, 0.0640, 0.1455, 0.3060, 0.4535, 0.5842, 0.6995, 0.7984, 0.9446, 1.0000, 0.9750, 0.8875, 0.8170, 0.7277, 0.6190, 0.4777, 0.3905, 0.2840, 0.1560, 0.0000},
                    {0.0000, 0.0725, 0.1560, 0.3228, 0.4740, 0.6050, 0.7184, 0.8139, 0.9519, 1.0000, 0.9751, 0.8899, 0.8259, 0.7415, 0.6359, 0.4982, 0.4108, 0.3042, 0.1753, 0.0000},
                    {0.0000, 0.0800, 0.1670, 0.3360, 0.4885, 0.6195, 0.7335, 0.8265, 0.9583, 1.0000, 0.9750, 0.8920, 0.8315, 0.7520, 0.6505, 0.5130, 0.4265, 0.3197, 0.1890, 0.0000},
                    {0.0000, 0.0905, 0.1810, 0.3500, 0.5040, 0.6353, 0.7525, 0.8415, 0.9645, 1.0000, 0.9725, 0.8933, 0.8345, 0.7593, 0.6590, 0.5220, 0.4335, 0.3235, 0.1935, 0.0000},
                    {0.0000, 0.0950, 0.1865, 0.3569, 0.5140, 0.6439, 0.7580, 0.8456, 0.9639, 1.0000, 0.9710, 0.8880, 0.8275, 0.7478, 0.6430, 0.5039, 0.4135, 0.3056, 0.1750, 0.0000},
                    {0.0000, 0.0965, 0.1885, 0.3585, 0.5110, 0.6415, 0.7530, 0.8426, 0.9613, 1.0000, 0.9690, 0.8790, 0.8090, 0.7200, 0.6060, 0.4620, 0.3775, 0.2720, 0.1485, 0.0000},
                    {0.0000, 0.0975, 0.1900, 0.3600, 0.5100, 0.6400, 0.7500, 0.8400, 0.9600, 1.0000, 0.9675, 0.8660, 0.7850, 0.6840, 0.5615, 0.4140, 0.3300, 0.2337, 0.1240, 0.0000},
                    {0.0000, 0.0975, 0.1900, 0.3600, 0.5100, 0.6400, 0.7500, 0.8400, 0.9600, 1.0000, 0.9635, 0.8520, 0.7635, 0.6545, 0.5265, 0.3765, 0.2925, 0.2028, 0.1050, 0.0000},
                    {0.0000, 0.0975, 0.1900, 0.3600, 0.5100, 0.6400, 0.7500, 0.8400, 0.9600, 1.0000, 0.9615, 0.8450, 0.7550, 0.6455, 0.5160, 0.3660, 0.2830, 0.1950, 0.1000, 0.0000},
                    {0.0000, 0.0975, 0.1900, 0.3600, 0.5100, 0.6400, 0.7500, 0.8400, 0.9600, 1.0000, 0.9600, 0.8400, 0.7500, 0.6400, 0.5100, 0.3600, 0.2775, 0.1990, 0.0975, 0.0000},
                    {0.0000, 0.0975, 0.1900, 0.3600, 0.5100, 0.6400, 0.7500, 0.8400, 0.9600, 1.0000, 0.9600, 0.8400, 0.7500, 0.6400, 0.5100, 0.3600, 0.2775, 0.1990, 0.0975, 0.0000}},
        // PNA V1+ 0.5*V2
        V12[][20]= {{0.30000, 0.30940, 0.33250, 0.37350, 0.40900, 0.44025, 0.46650, 0.48570, 0.50450, 0.50000, 0.49760, 0.47965, 0.46425, 0.44725, 0.43175, 0.41300, 0.40625, 0.39420, 0.38000, 0.38600},
                    {0.28260, 0.29500, 0.31275, 0.34970, 0.38375, 0.41280, 0.43775, 0.45840, 0.48950, 0.50000, 0.49240, 0.47415, 0.46050, 0.44425, 0.42750, 0.40735, 0.39525, 0.37730, 0.36010, 0.35600},
                    {0.25980, 0.27345, 0.28950, 0.32650, 0.36160, 0.39240, 0.41710, 0.44195, 0.48435, 0.50000, 0.49065, 0.46735, 0.45465, 0.43765, 0.41875, 0.39560, 0.38010, 0.35890, 0.33895, 0.32560},
                    {0.23060, 0.24400, 0.26250, 0.30130, 0.33855, 0.37205, 0.40435, 0.43345, 0.48245, 0.50000, 0.49020, 0.46080, 0.44575, 0.42630, 0.40425, 0.37560, 0.35775, 0.33585, 0.31310, 0.29230},
                    {0.14670, 0.16525, 0.18770, 0.23800, 0.29150, 0.33865, 0.38785, 0.42515, 0.48225, 0.50000, 0.48625, 0.44995, 0.42625, 0.39855, 0.36520, 0.32470, 0.30005, 0.27055, 0.24345, 0.21810},
                    {0.05220, 0.08950, 0.12625, 0.19745, 0.26700, 0.32595, 0.38020, 0.42280, 0.48195, 0.50000, 0.48550, 0.44400, 0.41455, 0.37730, 0.33000, 0.27305, 0.23955, 0.20280, 0.16530, 0.12780},
                    {0.00000, 0.04825, 0.09425, 0.17925, 0.25550, 0.32075, 0.37650, 0.42130, 0.48065, 0.50000, 0.48450, 0.43950, 0.40450, 0.36000, 0.30300, 0.23160, 0.19095, 0.14270, 0.09115, 0.03820},
                    {0.00000, 0.04875, 0.09500, 0.18000, 0.25500, 0.32000, 0.37500, 0.42000, 0.48000, 0.50000, 0.48375, 0.43300, 0.39250, 0.34200, 0.28075, 0.20700, 0.16500, 0.11685, 0.06200, 0.00000},
                    {0.00000, 0.04875, 0.09500, 0.18000, 0.25500, 0.32000, 0.37500, 0.42000, 0.48000, 0.50000, 0.48175, 0.42600, 0.38175, 0.32725, 0.26325, 0.18825, 0.14625, 0.10140, 0.05250, 0.00000},
                    {0.00000, 0.04875, 0.09500, 0.18000, 0.25500, 0.32000, 0.37500, 0.42000, 0.48000, 0.50000, 0.48075, 0.42250, 0.37750, 0.32275, 0.25800, 0.18300, 0.14150, 0.09750, 0.05000, 0.00000},
                    {0.00000, 0.04875, 0.09500, 0.18000, 0.25500, 0.32000, 0.37500, 0.42000, 0.48000, 0.50000, 0.48000, 0.42000, 0.37500, 0.32000, 0.25500, 0.18000, 0.13875, 0.09950, 0.04875, 0.00000},
                    {0.00000, 0.04875, 0.09500, 0.18000, 0.25500, 0.32000, 0.37500, 0.42000, 0.48000, 0.50000, 0.48000, 0.42000, 0.37500, 0.32000, 0.25500, 0.18000, 0.13875, 0.09950, 0.04875, 0.00000}},

        t, tMaxThick, maxThickness;
  tVector xx;

  tCSpline *cspl;
  tList<tElement*> thickL,camberL, thickCurveL, camberCurveL;
  //Dickenverteilung erzeugen:
  // V2-Funktion in PNA:

  for (i=0;i<12;i++){
    thickL.clear();
    camberL.clear();

    maxThickness = maxThicknessAt(rR[i]);

    if (rR[i] < 0.5){
      tMaxThick = 0.65;
    } else if (rR[i] > 0.9){
      tMaxThick = 0.5;
    } else {
      tMaxThick = 1-(0.425-(cos(M_PI*pow((rR[i]-0.5)/0.4,0.8)))*0.075);
    }

    for (j=0;j<20;j++){
      if (xPos[19-j]<0){
        t = tMaxThick * (xPos[19-j]+1.);
      } else {
        t = tMaxThick + (1-tMaxThick) * xPos[19-j];
      }
      thickL.append(new tPoint(NULL,tVector(rR[i],1-t,V2[i][19-j])));
      camberL.append(new tPoint(NULL,tVector(rR[i],1-t,V12[i][19-j]*maxThickness)));
    }
    thickL.reverse();
    for (j=thickL.count()-2;j>=0;j--){
      xx = ((tPoint*)(thickL.at(j)))->vector();
      xx.z *= -1;
      thickL.append(new tPoint(this, xx));
    }
    thickL.reverse();
    cspl = new tCSpline(NULL,&thickL);
    cspl->setTResolution(180);
    cspl->setCSplineType(jrCSLengthBased);
    thickCurveL.append(cspl);

    cspl = new tCSpline(NULL,&camberL);
    cspl->setTResolution(180);
    cspl->setCSplineType(jrCSLengthBased);
    camberCurveL.append(cspl);

  }

  tCLoft *thickS, *camberS;

  if (hostingLayer){
    thickS = hostingLayer->addCLoft();
    camberS = hostingLayer->addCLoft();

    thickS->intrface()->setName("WageningenB-Series.thickness");
    camberS->intrface()->setName("WageningenB-Series.camber");

    thickS->intrface()->setVisibility(false);
    camberS->intrface()->setVisibility(false);
  } else {
    thickS = new tCLoft(this);
    camberS = new tCLoft(this);
  }

  thickS->addDependent(this);
  camberS->addDependent(this);

  thickS->insertList(0,&thickCurveL);
  thickS->setUDiv(thickCurveL.count());
  thickS->setURes(20);
  setThickness(thickS);

  camberS->insertList(0,&camberCurveL);
  camberS->setUDiv(camberCurveL.count());
  camberS->setURes(20);
  setCamber(camberS);

}
//-----------------------------------------------------------------------------

tWageningenBSeries::~tWageningenBSeries()
{
}
//-----------------------------------------------------------------------------

void tWageningenBSeries::refresh(void)
{
  tPropSurface::refresh();
  fhubDiameter = 0.167;
}
//-----------------------------------------------------------------------------

tReal tWageningenBSeries::pitchAt(tReal rR)
{
  if (rR < 0.55){
    tReal h;
    h = (rR-0.167)/(0.55-0.167);
    return ((0.8+0.2*h)*(1-h*h)+h*h)*fPD;
  } else {
    return fPD;
  }
}
//-----------------------------------------------------------------------------

tReal tWageningenBSeries::chordAt(tReal rR)
{
  return fAEA0/fZ* (2.8157*rR*rR*rR - 3.1631*rR*rR + 5.0694*rR + 0.9446)*sqrt(1-rR);
}
//-----------------------------------------------------------------------------

tReal tWageningenBSeries::rakeAt(tReal rR)
{
  return tan(15./180.*M_PI)*rR*0.5;
}
//-----------------------------------------------------------------------------

tReal tWageningenBSeries::skewAt(tReal rR)
{
  tReal dist;

  dist = fAEA0/fZ*(1.4662*rR*rR*rR - 0.8558*rR*rR + 0.0731*rR - 0.1909);
  return dist * (float)fZ*cos(atan(pitchAt(rR)/M_PI))/(M_PI*rR);
}
//-----------------------------------------------------------------------------

tReal tWageningenBSeries::maxThicknessAt(tReal rR)
{
  tReal Sr;

  Sr = (-0.062*rR+0.065 - (0.005-0.005*rR)*fZ)*(1.-pow(rR,50.));
  return Sr;
}
//-----------------------------------------------------------------------------

iElement* tWageningenBSeries::intrface(void)
{
  if (iface == NULL){
    iface = new iWageningenBSeries(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
