/*
 * tKaSeries.cpp
 *
 *  Created on: 14.07.2010
 *      Author: Jochen
 */

#include "element/surface/tKaSeries.h"

tKaSeries::tKaSeries(void *theOwner, tLayer *hostingLayer) : tPropSurface(theOwner)
{
  fPD = 1.0;
  fAEA0 = 0.4;
  fZ = 4;

  int i,j;
  tReal rR[] =      {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1},
        xPos[][15] = {{0.00000, 0.00500, 0.13004, 0.26008, 0.39012, 0.52016, 0.65020, 0.72016, 0.79012, 0.86008, 0.93004, 0.96502, 0.98251, 0.99500, 1.00000},
                      {0.00000, 0.00563, 0.12048, 0.24096, 0.36144, 0.48192, 0.60240, 0.68192, 0.76144, 0.84096, 0.92048, 0.96024, 0.98012, 0.99500, 1.00000},
                      {0.00000, 0.00625, 0.10796, 0.21592, 0.32388, 0.43184, 0.53980, 0.63184, 0.72388, 0.81592, 0.90796, 0.95398, 0.97699, 0.99500, 1.00000},
                      {0.00000, 0.00688, 0.10174, 0.20348, 0.30522, 0.40696, 0.50870, 0.60696, 0.70522, 0.80348, 0.90174, 0.95087, 0.97544, 0.99500, 1.00000},
                      {0.00000, 0.00750, 0.10004, 0.20008, 0.30012, 0.40016, 0.50020, 0.60016, 0.70012, 0.80008, 0.90004, 0.95002, 0.97501, 0.99500, 1.00000},
                      {0.00000, 0.00813, 0.10000, 0.20000, 0.30000, 0.40000, 0.50000, 0.60000, 0.70000, 0.80000, 0.90000, 0.95000, 0.97500, 0.99500, 1.00000},
                      {0.00000, 0.00875, 0.10000, 0.20000, 0.30000, 0.40000, 0.50000, 0.60000, 0.70000, 0.80000, 0.90000, 0.95000, 0.97500, 0.99500, 1.00000},
                      {0.00000, 0.00938, 0.10000, 0.20000, 0.30000, 0.40000, 0.50000, 0.60000, 0.70000, 0.80000, 0.90000, 0.95000, 0.97500, 0.99500, 1.00000},
                      {0.00000, 0.01000, 0.10000, 0.20000, 0.30000, 0.40000, 0.50000, 0.60000, 0.70000, 0.80000, 0.90000, 0.95000, 0.97500, 0.99500, 1.00000}},

        // Dickenverteilung
        Vthick[][15] = {{0.0000, 0.0470, 0.3094, 0.6188, 0.8230, 0.9500, 1.0000, 0.9771, 0.8937, 0.7282, 0.4448, 0.2720, 0.1800, 0.0950, 0.0000},
                        {0.0000, 0.0653, 0.3443, 0.6556, 0.8414, 0.9586, 1.0000, 0.9751, 0.8923, 0.7290, 0.4687, 0.2959, 0.1970, 0.1051, 0.0000},
                        {0.0000, 0.0835, 0.3820, 0.6638, 0.8569, 0.9625, 1.0000, 0.9722, 0.8847, 0.7222, 0.4708, 0.3083, 0.2139, 0.1153, 0.0000},
                        {0.0000, 0.1018, 0.4109, 0.6842, 0.8642, 0.9660, 1.0000, 0.9677, 0.8693, 0.6995, 0.4482, 0.2886, 0.2071, 0.1140, 0.0000},
                        {0.0000, 0.1200, 0.4358, 0.6826, 0.8589, 0.9647, 1.0000, 0.9647, 0.8589, 0.6826, 0.4358, 0.2859, 0.2044, 0.1355, 0.0000},
                        {0.0000, 0.1383, 0.4531, 0.6924, 0.8633, 0.9658, 1.0000, 0.9658, 0.8633, 0.6924, 0.4531, 0.3079, 0.2288, 0.1390, 0.0000},
                        {0.0000, 0.1565, 0.4816, 0.7084, 0.8704, 0.9676, 1.0000, 0.9676, 0.8704, 0.7084, 0.4816, 0.3439, 0.2690, 0.1558, 0.0000},
                        {0.0000, 0.1748, 0.5175, 0.7294, 0.8809, 0.9717, 1.0000, 0.9717, 0.8809, 0.7294, 0.5175, 0.3887, 0.3187, 0.1800, 0.0000},
                        {0.0000, 0.1930, 0.5200, 0.7300, 0.8800, 0.9700, 1.0000, 0.9700, 0.8800, 0.7300, 0.5200, 0.3925, 0.3231, 0.1940, 0.0000}},
        // PNA V1+ 0.5*V2
        Vcamber[][15]= {{0.24000, 0.25000, 0.45520, 0.65420, 0.82500, 0.95000, 1.00000, 0.98130, 0.92290, 0.81560, 0.65520, 0.54790, 0.48020, 0.42600, 0.40000},
                        {0.20000, 0.21320, 0.43670, 0.67700, 0.84140, 0.95860, 1.00000, 0.97750, 0.90890, 0.78340, 0.59170, 0.46150, 0.37870, 0.31800, 0.30000},
                        {0.18340, 0.20000, 0.42920, 0.67500, 0.85690, 0.96250, 1.00000, 0.97220, 0.89310, 0.75000, 0.52920, 0.38610, 0.30270, 0.24000, 0.23000},
                        {0.13240, 0.15240, 0.42450, 0.68760, 0.86420, 0.96600, 1.00000, 0.96770, 0.87270, 0.70970, 0.46860, 0.31580, 0.23770, 0.17400, 0.15620},
                        {0.12000, 0.14600, 0.43580, 0.68260, 0.85890, 0.96470, 1.00000, 0.96470, 0.85890, 0.68260, 0.43580, 0.28590, 0.20440, 0.14000, 0.12000},
                        {0.14000, 0.16540, 0.45310, 0.69240, 0.86330, 0.96580, 1.00000, 0.96580, 0.86330, 0.69240, 0.45310, 0.30790, 0.22880, 0.16000, 0.14000},
                        {0.16000, 0.19020, 0.48160, 0.70840, 0.87040, 0.96760, 1.00000, 0.96760, 0.87040, 0.70840, 0.48160, 0.34390, 0.26900, 0.20200, 0.18000},
                        {0.17000, 0.20300, 0.51750, 0.72940, 0.88090, 0.97170, 1.00000, 0.97170, 0.88090, 0.72940, 0.51750, 0.38870, 0.31870, 0.25400, 0.24000},
                        {0.18000, 0.21880, 0.52000, 0.73000, 0.88000, 0.97000, 1.00000, 0.97000, 0.88000, 0.73000, 0.52000, 0.39250, 0.32310, 0.26000, 0.24000}},

        t, maxThickness;
  tVector xx;

  tCSpline *cspl;
  tList<tElement*> thickL,camberL, thickCurveL, camberCurveL;
  //Dickenverteilung erzeugen:

  for (i=0;i<9;i++){
    thickL.clear();
    camberL.clear();

    maxThickness = maxThicknessAt(rR[i]);


    for (j=14;j>=0;j--){
      t = 1.-xPos[i][j];
      thickL.append(new tPoint(NULL,tVector(rR[i],t,Vthick[i][j])));
      camberL.append(new tPoint(NULL,tVector(rR[i],t,Vcamber[i][j]*maxThickness/2.)));
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

    thickS->intrface()->setName("Ka-Series.thickness");
    camberS->intrface()->setName("Ka-Series.camber");

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
  thickS->setURes(15);
  setThickness(thickS);

  camberS->insertList(0,&camberCurveL);
  camberS->setUDiv(camberCurveL.count());
  camberS->setURes(15);
  setCamber(camberS);

}
//-----------------------------------------------------------------------------

tKaSeries::~tKaSeries()
{
}
//-----------------------------------------------------------------------------

void tKaSeries::refresh(void)
{
  tPropSurface::refresh();
  fhubDiameter = 0.167;
}
//-----------------------------------------------------------------------------

tReal tKaSeries::pitchAt(tReal /*rR*/)
{
  return fPD;
}
//-----------------------------------------------------------------------------

tReal tKaSeries::chordAt(tReal rR)
{
  return (-0.34878*pow(rR,4.) + 0.40365*pow(rR,3.) - 0.54075*pow(rR,2.) + 1.1551*rR + 0.45959)*1.969*fAEA0/(double)fZ;
}
//-----------------------------------------------------------------------------

tReal tKaSeries::rakeAt(tReal /*rR*/)
{
  return 0.;
}
//-----------------------------------------------------------------------------

tReal tKaSeries::skewAt(tReal rR)
{
  tReal dist;
  dist = chordAt(rR)/2. -(-0.083042*pow(rR,4.) + 0.089621*pow(rR,3.) - 0.37659*pow(rR,2.) + 0.77235*rR + 0.16212)*1.969*fAEA0/(double)fZ;
  return -dist * (float)fZ*cos(atan(pitchAt(rR)/M_PI))/(M_PI*rR);
}
//-----------------------------------------------------------------------------

tReal tKaSeries::maxThicknessAt(tReal rR)
{
  tReal tMax;

  tMax = 0.053*rR*rR*rR*rR - 0.0596*rR*rR*rR + 0.0061*rR*rR - 0.0434*rR + 0.0488;
  return tMax;
}
//-----------------------------------------------------------------------------

iElement* tKaSeries::intrface(void)
{
  if (iface == NULL){
    iface = new iKaSeries(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
