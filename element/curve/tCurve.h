#ifndef TCURVE_H_
#define TCURVE_H_

#include "classes/tVector.h"
#include "element/tPaintableElement.h"

#include "iCurve.h"

class tCurve : public tPaintableElement
{
private:
  void refreshCurve(void);

protected:
  int tRes;  // Anzahl der Kurvenabschnitte, mit denen die Kurve bei der Bildschirmdarstellung approximiert wird
  tVector *ftCache;  // (tResoultion+1) zwischengespeicherte Punkte auf der Kurve
  bool validCache,
  isProportionalToLength; // Gibt an, ob die Laufvariable proportional zur Laenge sein soll.
  tReal *dlength;
  tReal arrowhead,             // 0: kein Pfeil, sonst an der entsprechenden Position. positiv: zeigt in Richtung aufsteigender t-Werte
  flineWidth;             // Linienstaerke


public:
  tCurve(void *theOwner);
  virtual ~tCurve();

  virtual void update(void);
  virtual void invalidate(tElement *sender);

  int tResolution(void) {return tRes;}
  void setTResolution(int res);
  void updateCache(void);
  tVector *tCache(void) { updateCache(); return ftCache; }

  virtual tVector vectorAt(tReal t);
  virtual tVector vectorAtAccurate(tReal t)=0;

  //virtual tVector vectorAtArcLength(tReal s);

  virtual tVector gradientAt(tReal t);
  virtual tVector curvatureAt(tReal t);
  virtual tReal length(void);
  //		virtual tReal getSFromT(tReal t);
  //		virtual tReal getTFromS(tReal s);

  virtual tVector xMin(void);
  virtual tVector xMax(void);

  virtual tReal arrowheadPos(void){return arrowhead;}
  virtual void setArrowheadPos(tReal t){arrowhead = t; invalidate(this);}
  virtual tReal lineWidth(void){return flineWidth;}
  virtual void setLineWidth(tReal w){flineWidth = w; invalidate(this);}

  virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector& defaultN, const bool& isSelected);
};

/*I!
length Real read:length
t-Resolution Int read:tResolution write:setTResolution
arrowheadPosition Real read:arrowheadPos write:setArrowheadPos
lineWidth Real read:lineWidth write:setLineWidth
*/

#endif /*TCURVE_H_*/
