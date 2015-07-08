#include "element/surface/tPropSurface.h"

#include "classes/utils.h"

#define iterations 30

/**
 * Flaeche zur Beschreibung eines Propellers.
 *
 * pitchCurve: Gibt den Steigungsverlauf des Propellers an. Sie speichert P/D-Werte
 * chordCurve: Profiltiefe, normiert auf den Durchmesser (C/D)
 * skewCurve:
 * thicknessCurve: maximale Dicke des Profils (bezogen auf Druchmesser).
 * camberCurve: maximale W�lbund des Profils (bezogen auf Druchmesser).
 */
tPropSurface::tPropSurface(void *theOwner) : tSurface (theOwner)
{
  pitchCurve = NULL;
  chordCurve = NULL;
  rakeCurve = NULL;
  skewCurve = NULL;
  maxThickCurve  = NULL;
  thickSurf = NULL;
  camberSurf = NULL;

  setAccurate(false);

  ns = new tVariableNameSpace(this);
  radial0Var = dynamic_cast<tRealVariable*>(ns->addRealVariable("r0=0."));
  peripher0Var = dynamic_cast<tRealVariable*>(ns->addRealVariable("t0=0."));

  radialVar = dynamic_cast<tRealVariable*>(ns->addRealVariable("r=r0"));
  peripherVar = dynamic_cast<tRealVariable*>(ns->addRealVariable("t=t0"));

  blockInvalidateList.append(radial0Var);
  blockInvalidateList.append(peripher0Var);
  blockInvalidateList.append(radialVar);
  blockInvalidateList.append(peripherVar);

  fpffFileName = "";
  fisInReadingMode = "true";
  clear();
}

//-----------------------------------------------------------------------------

tPropSurface::~tPropSurface()
{
  clear();

  radialVar->removeDependent(this);
  peripherVar->removeDependent(this);
  ns->releaseOwner(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::clear(void)
{
  setElementLocked

  setPitch(NULL);
  setChord(NULL);
  setSkew(NULL);
  setMaxThick(NULL);
  setRake(NULL);
  setThickness(NULL);
  setCamber(NULL);

  fDiameter = 1.;
  fhubDiameter = 0.2;
  fScale = 1.;
  fZ = 1;
  fRoundedTip = true;
  fautoRoundTE = true;
  frotationDirection = true;

  radialVar->setFullString("r=1*(r0^3-2*r0^2+r0)+0.05*(r0^3-r0^2)-2*r0^3+3*r0^2");
  peripherVar->setFullString("t=0.2*(t0^3-2*t0^2+t0)+0.05*(t0^3-t0^2)-2*t0^3+3*t0^2");

}
//-----------------------------------------------------------------------------

void tPropSurface::importExportPropeller(QString fileName)
{
  fpffFileName = fileName;
  if (fisInReadingMode){
    openPff(fpffFileName);
  } else {
    savePff(fpffFileName);
  }
}
//-----------------------------------------------------------------------------

bool tPropSurface::openPff(QString fileName, tLayer* hostingLayer)
{
  setElementLocked
  clear();
  int i;
  bool ok[3];
  tReal SIscale = 0.001;  // Konvertierung von mm in m
  tList<tElement*> sectionL, radialsL, radialsSS, radialsPS,
                   pitchL, skewL, rakeL, wakeL, chordL,
                   camberL, camberCurveL, thickL, thickCurveL, maxThickL,
                   pointL, shapeL;
  tReal rR, chord, pitch, distLE, rake, thickMax, thick, camber,
        t, xSS, xPS;
  tVector xx;
  tCSpline *pitchC, *chordC, *rakeC, *skewC, *maxThickC;
  tCLoft *thickS, *camberS;

  tPoint *point;
  tCSpline *cspl;

  QString line;
  QStringList Vector;
  QFile pff(fileName);
  QFileInfo pffInfo(pff);

  fpffFileName = fileName;

  if (!pff.open(QIODevice::ReadOnly | QIODevice::Text)) {
    invalidate(this);
    return false;
  } else {
// pff-Daten einlesen
    char dbg[500];
    strcpy(dbg,fileName.toLatin1().data());
    QTextStream in(&pff);
    do {
      line = in.readLine();
      strcpy(dbg,line.toLatin1().data());
    } while (!line.contains("PropDiameter", Qt::CaseInsensitive));

    Vector =  in.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);
    fScale = Vector[2].toFloat();
    if (fScale <= 0.){
      fScale = 1.;
    }
    fDiameter = fabs(Vector[0].toFloat()*SIscale);
    if (fDiameter == 0.){
      fDiameter = 1.;
    }
    fhubDiameter = fabs(Vector[1].toFloat()*SIscale)/fDiameter;
    for (i=0;i<3;i++){
      in.readLine();
    }
    Vector =  in.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);
    fZ = Vector[0].toInt();
    if (Vector[4].toInt() == 1){      //Drehsinn
      frotationDirection = true;  //rechts drehend
    } else {
      frotationDirection = false; //links drehend
    }
    line = in.readLine();
    sectionL.clear();
    while (line.contains("r/R")){
      Vector = in.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);
      rR = Vector[0].toFloat();
//      r = rR*fDiameter/2.;
//      r = Vector[1].toFloat()*fScale;
      chord = Vector[2].toFloat()*SIscale;
      in.readLine();
      Vector = in.readLine().split(QRegExp("\\s+"),QString::SkipEmptyParts);
      pitch = Vector[0].toFloat()*SIscale;
      distLE = Vector[1].toFloat()*SIscale;
      rake = Vector[4].toFloat()*SIscale;
      in.readLine();
      line = in.readLine();

      t = -1.;

      thickMax = 0.;
      thickL.clear();
      camberL.clear();
      while (!line.contains("*")){
        Vector = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (Vector.count() > 2 && Vector[0].toFloat()-t>1e-7){
          t = Vector[0].toFloat(ok);
          xSS = Vector[1].toFloat(ok+1)*SIscale;  //Punkt auf der Saugseite
          xPS = Vector[2].toFloat(ok+2)*SIscale;  //Punkt auf der Druckseite
          if (ok[0] && ok[1] && ok[2]){
            thick = fabs(xSS-xPS);
            thickMax = max(thick,thickMax);
            if (thickL.count() == 0){
              thickL.append(new tPoint(NULL,tVector(rR,t,0.))); // Die Eintrittskante soll eine Dicke von 0 haben.
            } else {
//              thickL.append(new tPoint(NULL,tVector(rR,t,0.)));
              thickL.append(new tPoint(NULL,tVector(rR,t,thick)));
            }
            camber = (xSS+xPS)*0.5;
//            camberL.append(new tPoint(NULL,tVector(rR,t,sin(t*M_PI)*0.01)));
//            camberL.append(new tPoint(NULL,tVector(rR,t,camber/fDiameter*10.)));
            camberL.append(new tPoint(NULL,tVector(rR,t,camber/fDiameter)));
          }
        }
        line = in.readLine();
      }
      thickL.reverse();
      for (i=thickL.count()-2;i>=0;i--){
        xx = ((tPoint*)(thickL.at(i)))->vector();
        xx.z *= -1;
        thickL.append(new tPoint(this, xx));
      }
      thickL.reverse();
      if (thickMax != 0){
        for (i=0;i<thickL.count();i++){
          point = dynamic_cast<tPoint*>(thickL.at(i));
          if (point){
            xx = point->vector();
            xx.z /= thickMax;
            point->setVector(xx);
          }
        }
      }

      if (thickMax > 0){
        cspl = new tCSpline(NULL,&thickL);
        cspl->setCSplineType(jrCSLengthBased);
        thickCurveL.append(cspl);
      } else {
        for (i=0;i<thickL.count();i++){
          thickL.at(i)->releaseOwner(this);
        }
      }

      cspl = new tCSpline(NULL,&camberL);
      cspl->setCSplineType(jrCSLengthBased);
      camberCurveL.append(cspl);

      pitchL.append(new tPoint(NULL, tVector(rR,pitch/fDiameter,0.)));
      chordL.append(new tPoint(NULL, tVector(rR,chord/fDiameter,0.)));
      rakeL.append(new tPoint(NULL, tVector(rR,rake/fDiameter,0.)));
      skewL.append(new tPoint(NULL, tVector(rR,
                                            cos(atan(pitch/fDiameter/M_PI))*(chord/2.-distLE)/(M_PI*rR*fDiameter)*(float)fZ,
                                            0.)));
      maxThickL.append(new tPoint(NULL, tVector(rR,thickMax/fDiameter,0.)));
    }
    // pff-Daten einlesen beendet.

    // Basiskurven erzeugen;

    if (hostingLayer){
      pitchC = hostingLayer->addCSpline();
      chordC = hostingLayer->addCSpline();
      skewC = hostingLayer->addCSpline();
      rakeC = hostingLayer->addCSpline();
      maxThickC = hostingLayer->addCSpline();
      thickS = hostingLayer->addCLoft();
      camberS = hostingLayer->addCLoft();

      pitchC->intrface()->setVisibility(false);
      chordC->intrface()->setVisibility(false);
      skewC->intrface()->setVisibility(false);
      maxThickC->intrface()->setVisibility(false);
      rakeC->intrface()->setVisibility(false);
      thickS->intrface()->setVisibility(false);
      camberS->intrface()->setVisibility(false);

    } else {
      pitchC = new tCSpline(NULL);
      chordC = new tCSpline(NULL);
      skewC = new tCSpline(NULL);
      maxThickC = new tCSpline(NULL);
      rakeC = new tCSpline(NULL);
      thickS = new tCLoft(NULL);
      camberS = new tCLoft(NULL);
    }

    pitchC->intrface()->setName(intrface()->name() + ".pitch");
    chordC->intrface()->setName(intrface()->name() + ".chord");
    skewC->intrface()->setName(intrface()->name() + ".skew");
    maxThickC->intrface()->setName(intrface()->name() + ".maximumThickness");
    rakeC->intrface()->setName(intrface()->name() + ".rake");
    thickS->intrface()->setName(intrface()->name() + ".thickness");
    camberS->intrface()->setName(intrface()->name() + ".camber");

    setPitch(pitchC);
    setChord(chordC);
    setSkew(skewC);
    setMaxThick(maxThickC);
    setRake(rakeC);
    setThickness(thickS);
    setCamber(camberS);

    // pitch ist nicht lengthbased
    chordC->setCSplineType(jrCSLengthBased);
    skewC->setCSplineType(jrCSLengthBased);
    maxThickC->setCSplineType(jrCSLengthBased);
    rakeC->setCSplineType(jrCSLengthBased);



//    chordC->insertList(0,&chordL);
    if (fRoundedTip){
      tList<tElement*> list;
      list = chordL;
      chordL.clear();
      for (i=list.count()-1; i>=0; i--){

        xx = ((tPoint*)list.at(i))->vector();
        chordL.prepend(new tPoint(NULL, xx));
        if (fRoundedTip == true){
          // chordSpiegeln:
          xx.y *= -1;
          chordL.append(new tPoint(NULL, xx));
        }
      }
    }
    chordC->insertList(0,&chordL);

    pitchC->insertList(0,&pitchL);
    rakeC->insertList(0,&rakeL);
    skewC->insertList(0,&skewL);
    maxThickC->insertList(0,&maxThickL);



    camberS->insertList(0,&camberCurveL);
    camberS->setUDiv(camberCurveL.count());
    camberS->setURes(20);

    thickS->insertList(0,&thickCurveL);
    thickS->setUDiv(thickCurveL.count());
    thickS->setURes(20);


    invalidate(this);
    return true;
  }
}
//-----------------------------------------------------------------------------

bool tPropSurface::savePff(QString fileName){


#define endl qSetFieldWidth(0)<<"\n"<<qSetFieldWidth(20)

  bool fileIsOpen;
  int nRadii = 25, i,
      nChord = 30;
  tReal rR, r;

  QFile file(fileName);

  fileIsOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);
  if (fileIsOpen){
    QTextStream store(&file);
    store << "*** PFF 2.2 ***\n";
    store.setFieldWidth(20);
    store.setFieldAlignment(QTextStream::AlignLeft);

    store << "*  PropDiameter /" << "HubDiameter /" << "Scale /"    << "ExpArRatio /"  << "BladeM" << endl
          << fDiameter           << fhubDiameter     << fScale       << 0 << 0                      << endl
          << "* MomentInert /"   << "ShaftPower /"                                                 << endl
          << 0                   << 0                                                              << endl
          << "* No.Blades /"     << "Material / "   << "No.Radii /" << "No.CordPart/ " << "Dir.of.Rot./ "     << "iProfil /" << endl
          << fZ                  << 0               << nRadii       << nChord          << frotationDirection  << 0           << endl;
    for(i=0;i<=nRadii;i++){
      rR = fhubDiameter + (1-fhubDiameter)*(tReal)i/(tReal)nRadii;
      r = fDiameter * rR;
      store << "*  r/R /"            << "r /"           << "CordLength /"         << "Aufdick /"  << "RueckLageF" << endl
            << rR                    << r               << chordAt(rR)*fDiameter  << 0            << 0            << endl
            << "*    Pitch /"         << "DistLeaEdge /" << "MaxCamber /"          << "MaxThick /" << "Rake"      << endl
            << pitchAt(rR)*fDiameter << "palim"         << "ping"                 << "pong"       << rakeAt(rR)*fDiameter << endl
            << "*    CS /"           << "Y-SS / "       << "Y-PS /"                                               << endl;

    }
    //        0 0 0
//        0.005 -0.6221 0.6459
//        0.0075  -0.7742 0.8074
//        0.0125  -0.9995 1.0499
//        0.025 -1.3869 1.4744
//        0.05  -1.9139 2.0633
//        0.1 -2.6169 2.8642
//        0.2 -3.5044 3.8897
//        0.3 -4.0561 4.5318
//        0.4 -4.3767 4.9065
//        0.5 -4.4804 5.0321
//        0.6 -4.3558 4.8951
//        0.7 -3.9315 4.4224
//        0.8 -3.1353 3.5225
//        0.9 -1.8939 2.0966
//        0.95  -1.1386 1.2395
//        1 -0.293  0.293
  }
  return fileIsOpen;
#undef endl
}
//-----------------------------------------------------------------------------

void tPropSurface::refresh(void)
{
  if (pitchCurve){
    fhubDiameter = pitchCurve->vectorAt(0).x;
  } else {
    fhubDiameter = 0.2;
  }

  //  int i;
  //  tVector xx;
//  tList<tElement*> list;
//  chordCurve->clear();
//  for (i=chordL.count()-1; i>=0; i--){
//    xx = ((tPoint*)chordL.at(i))->vector();
//    list.prepend(new tPoint(NULL, xx));
//    if (fRoundedTip == true){
//      // chordSpiegeln:
//      xx.y *= -1;
//      list.append(new tPoint(NULL, xx));
//    }
//  }
//  chordCurve->insertList(0,&list);
//  list.clear();
}
//-----------------------------------------------------------------------------

tReal tPropSurface::getValueAtCurve(tCurve *c, tReal rR)
{
  int j;
  tReal dT,posT;
  tVector x;

  if (c){
    if (c==chordCurve && fRoundedTip == true && (c->vectorAt(0.25).y + c->vectorAt(0.75).y)<0.001){
      posT = 0.25;
      dT = 0.125;
    } else {
      posT = 0.5;
      dT = 0.25;
    }

    for (j=0;j<iterations;j++){
      x = c->vectorAt(posT);
      if (x.x > rR){
        posT -= dT;
      } else {
        posT += dT;
      }
      dT /= 2.;
    }
    return x.y;
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------

tReal tPropSurface::getValueAtSurface(tSurface *s, tReal rR, tReal t)
{
  int j;
  tReal dU,dV, posU, posV;
  tVector x;
  posV = 0.5;
  dV = 0.25;
  posU = 0.5;
  dU = 0.25;

  if (s == thickSurf){
    posU = 0.75;
    dU = 0.125;
  } else {
    posU = 0.5;
    dU = 0.25;
  }
  if (s){
// erst Radius ermitteln,
    for (j=0;j<iterations;j++){
      x = s->vectorAt(posU,posV);
      if (x.x > rR){
        posV -= dV;
      } else {
        posV += dV;
      }
      dV /= 2.;
    }
    if (x.x - rR > 0.01){
      x.x = rR;
    }
// Dann den passenden Punkt auf dem Profilschnitt
    for (j=0;j<15;j++){
      x = s->vectorAt(posU,posV);
      if (x.y > t){
        posU -= dU;
      } else {
        posU += dU;
      }
      dU /= 2.;
    }
    if (x.x - rR > 0.001){
      x.x = rR;
    }
    return x.z;
  } else {
    return 0.;
  }
}
//-----------------------------------------------------------------------------

tReal tPropSurface::thicknessAt(tReal rR, tReal t)
{
  if (t<=0 || t>=1){
    return 0.;
  } else {
    double thick = max(getValueAtSurface(thickSurf, rR, 1.-t),0.);
    if (fautoRoundTE){
      // Stumpfe Hinterkanten ausrunden.
      double C = chordAt(rR),
             teThickness = max(getValueAtSurface(thickSurf, rR, 1.),0.)*maxThicknessAt(rR)*0.5;
      if ( t*C < teThickness){
        double frac = 1. - (t*C/teThickness);
        thick *= sqrt(1-frac*frac);
      }
    }
    if (fautoRoundTip){
      // Blattspitze ausrunden
      const double limit =0.99;
      if (rR>limit && maxThicknessAt(1.)>0){
        double frac = (rR-limit)/(1.-limit);
        thick *= sqrt(1.-frac*frac);
      }
    }

    return thick;
  }
}
//-----------------------------------------------------------------------------

tReal tPropSurface::camberAt(tReal rR, tReal t)
{
  return max(getValueAtSurface(camberSurf, rR, 1.-t),0.);
}
//-----------------------------------------------------------------------------

tReal tPropSurface::hubRadiusAt(tReal /*x*/)
{
  // Spaeter mal durch interpolation eines Splines ersetzen.
  // return hubDiameter*0.5*fDiameter*fScale;

  tVector X;
  X = vectorAt(0,0);
  X = X.toCylCOS(tVector(0,0,0),tVector(1,0,0),tVector(0,1,0));
  return X.y;
}
//-----------------------------------------------------------------------------

tVector tPropSurface::vectorAtAccurate(tReal u, tReal v)
{
  setElementLocked;
  tReal r,chord,PD,skew,rake, maxThick, thick, camber,
        distLE, chordwisePos, beta, phi, h,// l,alpha,
        t;
  tVector x;

	update();
  if (v>1 || v<0.){
    t = 10. ;
  }

  radial0Var->setValue(u);
  r = radialVar->value() + (1-radialVar->value())*fhubDiameter;
  r = max(r, 0.);
  r = min(r, 1.);

  PD = pitchAt(r);
  chord = chordAt(r);
  rake = rakeAt(r);
  skew = skewAt(r);
  maxThick = maxThicknessAt(r);
  distLE = chord/2.-(skew*M_PI*r/(tReal)fZ/cos(atan(PD/M_PI)));

  if (v > 0.5){
    t = (1-v)*2;
  } else {
    t = v*2.;
  }

  // Pitch angle
  beta = atan2(PD,M_PI*r);

  if (t>=0){
    peripher0Var->setValue(t);
    t = peripherVar->value();
    thick = thicknessAt(r,t)*0.5;
    camber = camberAt(r, t);
    chordwisePos = distLE-(1.-t)*chord;
    if (v > 0.5){
      h = camber + thick*maxThick;
    } else {
      h = camber - thick*maxThick;
    }
  } else {
    // Einen Punkt an der Hinterkante waehlen
    thick = 0.;
    camber = camberAt(r, 0.);
    chordwisePos = distLE-chord;
    h = camber;
  }

  phi = (cos(beta)*chordwisePos-sin(beta)*h)/(0.5*r);
  x.x = (sin(beta)*chordwisePos+cos(beta)*h)-rake;
  if (frotationDirection){
    x.y = -0.5*r*sin(phi);
  } else {
    x.y = 0.5*r*sin(phi);
  }
  x.z = 0.5*r*cos(phi);

  if (t<0) {
    // Den Punkt an der Hinterkante rotieren und in axialer Richtung den Pitch sowie
    // eine Korrektur fuer die Woelbung an der Hinterkante addieren.
    // Dabei entspricht ein t-Wert von -2 einer Umdrehung.
    if (frotationDirection){
      x = x.rotate(tVector(0,0,0),tVector(1,0,0),t*M_PI);
    } else {
      x = x.rotate(tVector(0,0,0),tVector(-1,0,0),t*M_PI);
    }
    tReal pitchCorrection = atan((camberAt(r,0.3)-h)/(0.3*chord));
    PD = tan(beta+pitchCorrection)*M_PI*r;

    x.x += PD *0.5*t;
  }

  x = x*fDiameter*fScale;

  return x;
}
//-----------------------------------------------------------------------------

tVector tPropSurface::camberLineAt(tReal u, tReal v)
{
  // aehnlich wie vectorAt(u,v) nur ohne Dickenverteilung. Ist nicht in Druck und Saugseite aufgeteilt (v lauft von Austrittskante zur Eintrittskante.
  setElementLocked;
  tReal r,chord,PD,skew,rake, //maxThick,
        camber,
        distLE, chordwisePos, beta, phi, h;
  tVector x;

  update();

  radial0Var->setValue(u);
  r = radialVar->value() + (1-radialVar->value())*fhubDiameter;
  r = max(r, 0.);
  r = min(r, 1.);

  PD = pitchAt(r);
  chord = chordAt(r);
  rake = rakeAt(r);
  skew = skewAt(r);
  //maxThick = maxThicknessAt(r);
  distLE = chord/2.-(skew*M_PI*r/(tReal)fZ/cos(atan(PD/M_PI)));

  // Pitch angle
  beta = atan2(PD,M_PI*r);

  if (v>=0){
    if (v<=1){
      peripher0Var->setValue(v);
      v = peripherVar->value();
      camber = camberAt(r, v);
      chordwisePos = distLE-(1.-v)*chord;
      h = camber;
    } else {
      // Einen Punkt an der Eintrittskante waehlen
      camber = camberAt(r, 1.);
      chordwisePos = distLE;
      h = camber;
    }
  } else {
    // Einen Punkt an der Hinterkante waehlen
    camber = camberAt(r, 0.);
    chordwisePos = distLE-chord;
    h = camber;
  }

  phi = (cos(beta)*chordwisePos-sin(beta)*h)/(0.5*r);
  x.x = (sin(beta)*chordwisePos+cos(beta)*h)-rake;
  if (frotationDirection){
    x.y = -0.5*r*sin(phi);
  } else {
    x.y = 0.5*r*sin(phi);
  }
  x.z = 0.5*r*cos(phi);

  if (v<0) {
    // Den Punkt an der Hinterkante rotieren und in axialer Richtung den Pitch sowie
    // eine Korrektur fuer die Woelbung an der Hinterkante addieren.
    // Dabei entspricht ein v-Wert von -2 einer Umdrehung.
    if (frotationDirection){
      x = x.rotate(tVector(0,0,0),tVector(1,0,0),v*M_PI);
    } else {
      x = x.rotate(tVector(0,0,0),tVector(-1,0,0),v*M_PI);
    }
    tReal pitchCorrection = atan((camberAt(r,0.3)-h)/(0.3*chord));
    PD = tan(beta+pitchCorrection)*M_PI*r;
    x.x += PD *0.5*v;
  }
  if (v>1) {
    // Den Punkt an der Eintrittskante rotieren und in axialer Richtung den Pitch sowie
    // eine Korrektur fuer die Woelbung an der Hinterkante addieren.
    // Dabei entspricht ein v-Wert von 2 einer Umdrehung.
    if (frotationDirection){
      x = x.rotate(tVector(0,0,0),tVector(1,0,0),(v-1.)*M_PI);
    } else {
      x = x.rotate(tVector(0,0,0),tVector(-1,0,0),(v-1.)*M_PI);
    }
    tReal pitchCorrection = atan(h-(camberAt(r,0.9))/(0.1*chord));
//    PD = tan(beta)*M_PI*r;
    x.x += tan(beta+pitchCorrection)*M_PI*0.5*r*(v-1.);
  }

  x = x*fDiameter*fScale;

  return x;
}
//-----------------------------------------------------------------------------

iElement* tPropSurface::intrface(void)
{
  if (iface == NULL){
    iface = new iPropSurface(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

QString tPropSurface::radialRefinement(void)
{
  return radialVar->RHS();
}
//-----------------------------------------------------------------------------

void tPropSurface::setRadialRefinement(QString refFunc)
{
  radialVar->setRHS(refFunc);
  invalidate(this);
}
//-----------------------------------------------------------------------------

QString tPropSurface::peripherRefinement(void)
{
  return peripherVar->RHS();
}
//-----------------------------------------------------------------------------

void tPropSurface::setPeripherRefinement(QString refFunc)
{
  peripherVar->setRHS(refFunc);
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setPitch(tElement *el){
  setElementLocked
  tCurve *c;
  if (pitchCurve){
    pitchCurve->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(el);
  if (c && c->addDependent(this)){
    pitchCurve = c;
  } else {
    pitchCurve = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setChord(tElement *el){
  setElementLocked
  tCurve *c;
  if (chordCurve){
    chordCurve->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(el);
  if (c && c->addDependent(this)){
    chordCurve = c;
  } else {
    chordCurve = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setRake(tElement *el){
  setElementLocked
  tCurve *c;
  if (rakeCurve){
    rakeCurve->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(el);
  if (c && c->addDependent(this)){
    rakeCurve = c;
  } else {
    rakeCurve = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setSkew(tElement *el){
  setElementLocked
  tCurve *c;
  if (skewCurve){
    skewCurve->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(el);
  if (c && c->addDependent(this)){
    skewCurve = c;
  } else {
    skewCurve = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setMaxThick(tElement *el){
  setElementLocked
  tCurve *c;
  if (maxThickCurve){
    maxThickCurve->removeDependent(this);
  }
  c = dynamic_cast<tCurve*>(el);
  if (c && c->addDependent(this)){
    maxThickCurve = c;
  } else {
    maxThickCurve = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setThickness(tElement *el){
  setElementLocked
  tSurface *s;
  if (thickSurf){
    thickSurf->removeDependent(this);
  }
  s = dynamic_cast<tSurface*>(el);
  if (s && s->addDependent(this)){
    thickSurf = s;
  } else {
    thickSurf = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tPropSurface::setCamber(tElement *el){
  setElementLocked
  tSurface *s;
  if (camberSurf){
    camberSurf->removeDependent(this);
  }
  s = dynamic_cast<tSurface*>(el);
  if (s && s->addDependent(this)){
    camberSurf= s;
  } else {
    camberSurf = NULL;
  }
  invalidate(this);
}
//-----------------------------------------------------------------------------


