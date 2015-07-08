#ifndef TSTRUCTURED3DGRID_H_
#define TSTRUCTURED3DGRID_H_

#include "element/misc/tStructuredAbstractGrid.h"
#include "element/point/tDot.h"
#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"
#include "classes/tList.h"

#include "iStructured3DGrid.h"

/**
 * Klasse für ein Volumengitter. Zählung der Eckpunkte/Kanten erfolgt analog zu dem Blockaufbau in .
 *
 *        7----------2---------6
 *       /             _ _    /|
 *      / |           |_5_|  / |
 *     7        _ _         6  |
 *    /   11   /_2_/       /   |
 *   /                    /    |
 *  /     |              /     10
 * 4---------3----------5 _ _  |
 * | _ _                | _1_  |
 * | _3_  |             |      |
 * |      3- -  -  1-  -| -  - 2     nk
 * |     /              |     /      |     nj
 * 8    4               9    /       |    /
 * |   /      _ _       |   5        |   /
 * |         /_0_/      |  /         |  /
 * | / _ _              | /          | /
 * |  |_4_|             |/           |/
 * 0----------0---------1            -------------ni
 *
 */

class tStructured3DGrid : public tStructuredAbstractGrid
{
private:
protected:
  tList<tDot*> dots;
  int ni_, nj_, nk_;

  int ijk(int i, int j, int k) {return  k*ni_*nj_+j*ni_+i;};
  void setDot(int i, int j, int k, tVector value);

  void clearDots(void);

  tList<QString> faceNames_; //Namen zu Zuordnung der Randbedingungen

public:
	tStructured3DGrid(void *theowner);
	virtual ~tStructured3DGrid();

	virtual iElement* intrface(void);
  virtual void setFaceNames(tList<QString> names);
  virtual tList<QString> faceNames(void);

  virtual int ni(void);
  virtual int nj(void);
  virtual int nk(void);
  virtual int nIJK(int ijk){if (ijk%3==0) return ni(); else if (ijk%3==1) return nj(); else return nk();};

  virtual tDot* gridAt(int i, int j, int k);

};

/*sip! isAbstract */
/*I!
ni Int read:ni
nj Int read:nj
nk Int read:nk
faceNames StringList read:faceNames write:setFaceNames
*/
#endif /*TSTRUCTURED3DGRID_H_*/
