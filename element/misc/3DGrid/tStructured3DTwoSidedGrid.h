#ifndef TSTRUCTURED3DTWOSIDEDGRID_H_
#define TSTRUCTURED3DTWOSIDEDGRID_H_

#include "element/misc/3DGrid/tStructured3DGrid.h"
#include "element/point/tDot.h"
#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"
#include "classes/tList.h"

#include "iStructured3DTwoSidedGrid.h"

/**
 * Klasse für ein Volumengitter. Zählung der Eckpunkte/Kanten erfolgt analog zu dem Blockaufbau in BlockMesh.
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
 *
 *
 */

class tStructured3DTwoSidedGrid : public tStructured3DGrid
{
private:
  tSurface* faces_[2];
  double fMergeNodeTolerance;

public:
	tStructured3DTwoSidedGrid(void *theowner);
	virtual ~tStructured3DTwoSidedGrid();

	virtual iElement* intrface(void);
  virtual void refresh(void);

  virtual void setNi(int n) {ni_ = n; invalidate(this);};
  virtual void setNj(int n) {nj_ = n; invalidate(this);};
  virtual void setNk(int n) {nk_ = n; invalidate(this);};

  virtual tList<tElement*> faces(void);
  virtual void setFace(int f, tElement* el);
  virtual void setFaces(tList<tElement*> list);

};

/*I!
ni Int read:ni write:setNi
nj Int read:nj write:setNj
nk Int read:nk write:setNk
faces SurfaceList read:faces write:setFaces
*/
#endif /*TSTRUCTURED3DTWOSIDEDGRID_H_*/
