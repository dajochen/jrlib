#ifndef TPROPSURF_H_
#define TPROPSURF_H_

#include <QtCore>

#include "element/surface/tCLoft.h"
#include "element/point/tPoint.h"
#include "element/curve/tCSpline.h"
#include "element/surface/tSurface.h"
#include "element/variable/tVariableNameSpace.h"
#include "element/variable/tRealVariable.h"
#include "model/tLayer.h"

#include "iPropSurface.h"

class tLayer;
class tPropSurface : public tSurface
{
protected:
  tReal fDiameter, fhubDiameter, fScale;
  int fZ;
  bool frotationDirection;// Drehrichtung
  bool fRoundedTip; // true = abgrundete Blattspitze, false ="abgesaegte" Blattspitze
                    // Diese Option ist nicht ganz konsistent, das das Ergebnis nur korrekt ist, wenn die chordCurve symmetrisch ist.
                    // Die Option wird beim oeffnen einer pff-Datei korrekt beruecksichtigt.
  bool fautoRoundTE; // Geht die Dickenverteilung an der Hinterkante an einem Radius nicht auf Null zurück, ist es für pot.th. Rechnungen sinnvoll,
                     // wenn die Hinterkante ausgerundet wird. Ob diese Funktion aufgerufen werden soll, kann durch diesen Schalter festgelegt
                     // werden.  (Standard: true)
  bool fautoRoundTip; //Das gleiche fuer die Blattspitze.

  tCurve *pitchCurve, *chordCurve,
           *rakeCurve, *skewCurve, *maxThickCurve;
  tSurface *thickSurf, *camberSurf;

  tVariableNameSpace *ns;
  tRealVariable *radialVar, *peripherVar,     // Functions, describing the refinement of the surface
                *radial0Var, *peripher0Var;   // Internal functions

  QString fpffFileName;
  bool fisInReadingMode;

  tReal getValueAtCurve(tCurve *c, tReal rR);
  tReal getValueAtSurface(tSurface *s, tReal rR, tReal t);

  virtual tReal thicknessAt(tReal rR, tReal t);
  virtual tReal camberAt(tReal rR, tReal t);


public:
	tPropSurface(void *theOwner);
	virtual ~tPropSurface();

  void clear(void);

  bool openPff(QString fileName, tLayer* hostingLayer=NULL);
  bool savePff(QString fileName);

  QString propellerFileName(void){return fpffFileName;}
  void importExportPropeller(QString);

  virtual void refresh(void);
  virtual tVector vectorAtAccurate(tReal u, tReal v);
  virtual iElement* intrface(void);
  virtual tVector camberLineAt(tReal u, tReal v);

  tCurve* pitch(void){setElementLocked return pitchCurve;}
  tCurve* chord(void){setElementLocked return chordCurve;}
  tCurve* rake(void){setElementLocked return rakeCurve;}
  tCurve* skew(void){setElementLocked return skewCurve;}
  tCurve* maxThick(void){setElementLocked return maxThickCurve;}
  tSurface* thickness(void){setElementLocked return thickSurf;}
  tSurface* camber(void) {setElementLocked return camberSurf;}
  void setPitch(tElement *el);
  void setChord(tElement *el);
  void setRake(tElement *el);
  void setSkew(tElement *el);
  void setMaxThick(tElement *el);
  void setThickness(tElement *el);
  void setCamber(tElement *el);

  tReal diameter(void){setElementLocked return fDiameter;}
  void setDiameter(tReal d){setElementLocked if (fDiameter<=0) fDiameter=1.; else fDiameter = d; invalidate(this);}

  tReal hubDiameter(void){setElementLocked return fhubDiameter;}
  void setHubDiameter(tReal d){setElementLocked if (fhubDiameter<=0) fhubDiameter=1.; else fhubDiameter = d; invalidate(this);}

  tReal scale(void){setElementLocked return fScale;}
  void setScale(tReal s){setElementLocked if (fScale <= 0.){fScale = 1.;} else {fScale = s;} invalidate(this);}

  int bladeNumber(void){setElementLocked return fZ;}
  void setBladeNumber(int z){setElementLocked if (fZ<=0) fZ=1; else fZ = z;invalidate(this);}

  bool rotationDirection(void){setElementLocked return frotationDirection;}
  void setRotationDirection(bool o){setElementLocked frotationDirection = o; invalidate(this);}

  bool roundedTip(void){setElementLocked return fRoundedTip;}
  void setRoundedTip(bool type){setElementLocked fRoundedTip=type; invalidate(this);}

  bool autoRoundTE(void){setElementLocked return fautoRoundTE;}
  void setAutoRoundTE(bool type){setElementLocked fautoRoundTE=type; invalidate(this);}

  bool autoRoundTip(void){setElementLocked return fautoRoundTip;}
  void setAutoRoundTip(bool type){setElementLocked fautoRoundTip=type; invalidate(this);}

  QString radialRefinement(void);
  void setRadialRefinement(QString refFunc);

  QString peripherRefinement(void);
  void setPeripherRefinement(QString refFunc);

  virtual tReal pitchAt(tReal rR){return getValueAtCurve(pitchCurve, rR);}
  virtual tReal chordAt(tReal rR){return getValueAtCurve(chordCurve, rR);}
  virtual tReal rakeAt(tReal rR){return getValueAtCurve(rakeCurve, rR);}
  virtual tReal skewAt(tReal rR){return getValueAtCurve(skewCurve, rR);}
  virtual tReal maxThicknessAt(tReal rR){return getValueAtCurve(maxThickCurve, rR);}


  virtual tReal hubRadiusAt(tReal x);

  bool isInReadingMode(void){return fisInReadingMode;}
  void setReadWriteMode(bool mode){setElementLocked fisInReadingMode = mode; invalidate(this);}
};

/*I!
diameter Real read:diameter write:setDiameter
scale Real read:scale write:setScale
bladeNumber Int read:bladeNumber write:setBladeNumber
rotationDirection Bool read:rotationDirection write:setRotationDirection
roundedTipChord Bool read:roundedTip write:setRoundedTip
autoRoundTrailingEdge Bool read:autoRoundTE write:setAutoRoundTE
autoRoundTipThickness Bool read:autoRoundTip write:setAutoRoundTip
radialRefinement String read:radialRefinement write:setRadialRefinement
peripherRefinement String read:peripherRefinement write:setPeripherRefinement
pitch Curve read:pitch write:setPitch
chord Curve read:chord write:setChord
rake Curve read:rake write:setRake
skew Curve read:skew write:setSkew
maxThickness Curve read:maxThick write:setMaxThick
thickness Surface read:thickness write:setThickness
camber Surface read:camber write:setCamber
optional isInReadingMode Bool read:isInReadingMode write:setReadWriteMode
optional propellerFileName String read:propellerFileName write:importExportPropeller
*/

#endif /*TPROPSURF_H_*/
