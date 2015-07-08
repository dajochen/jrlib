#ifndef TNET_H_
#define TNET_H_

#include "element/tElement.h"
#include "element/point/tDot.h"
#include "element/curve/tLine.h"
#include "classes/tList.h"

#include "iNet.h" 

class tNetNode{
  public: 
    tElement *netPoint; //Merker für das abhaengige Element
    tDot *refPoint;     //Eigenschaften und Startwert des Netzpunktes (Point, AbsBead, AbsMagnet) 
    tDot *knot;         //Kopie von refPoint, die von tNet veraendert wird.
};

class tSpring {
  public:
    tNetNode *start, *end;
    tLine *spring;
    tReal stiffness, l0;
};

class tNet : public tElement
{
private:
  tList<tNetNode*> bKnot;  // Knoten am Rand 
  tList<tNetNode*> nKnot;  // bewegliche Knoten im Netz
  tList<tSpring*> spring; 
  tList<tNetNode*> linkList; // Liste, die den Ort der netPoints speichert und deren Referenzpunte speichert. 
  int calcDepth(void);
  int iterations, knotDepth;
  tReal maxStiffness;
  
  tNetNode* getNetNode(tElement *netPoint);
  
public:
  tNet(void *theowner);
  virtual ~tNet();

  virtual void refresh(void);
  virtual iElement* intrface(void);
  virtual tVector xMin(void){tVector x; x.setZero(); return x;};
  virtual tVector xMax(void){tVector x; x.setZero(); return x;};

  tVector getVector(tElement *netPoint);
  tDot* getRefPoint(tElement *netPoint);
  void setRefPoint(tElement* netPoint, tElement *refPoint); 

  void setBorderKnot(tElement *netPoint); // Knoten, die nicht verschoben werden.
  void addSpring(tElement *a, tElement *b, tReal c = 1., tReal l0=0.); // Einspannpunkte und Steifigkeit c

  int nSprings(void) ;
  tLine* springLine(int index);      
  
  void setNetIterations(int i){iterations = i; invalidate(this);};
  int netIterations(void){return iterations;};
  void clear(void);
  
  void setColor(tRGB color);
};

/*I!
 */

#endif /*TNET_H_*/
