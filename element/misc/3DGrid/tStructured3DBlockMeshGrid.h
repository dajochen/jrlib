#ifndef TSTRUCTURED3DBLOCKMESHGRID_H_
#define TSTRUCTURED3DBLOCKMESHGRID_H_

#include "element/misc/3DGrid/tStructured3DGrid.h"
#include "element/point/tDot.h"
#include "element/curve/tCurve.h"
#include "element/surface/tSurface.h"
#include "classes/tList.h"

#include "iStructured3DBlockMeshGrid.h"

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

class tStructured3DBlockMeshGrid : public tStructured3DGrid
{
private:
//  tList<tDot*> dots;
  tDot* corners_[8];
  tCurve* edges_[12];
  tSurface* faces_[6];
//  int ni_, nj_, nk_;
  int niSoll_, njSoll_, nkSoll_;

//  tList<QString> faceNames_; //Namen zu Zuordnung der Randbedingungen

//  void setDot(int i, int j, int k, tVector value);
//  int ijk(int i, int j, int k) {return  k*ni_*nj_+j*ni_+i;};

  //void clearDots(void);
  tVector faceCorrection(int i, int j, int k, tVector* vs);
  tVector volumeCorrection(int i, int j, int k, tVector* vs);
  //tVector edgeAt(int edge,int index);

public:
	tStructured3DBlockMeshGrid(void *theowner);
	virtual ~tStructured3DBlockMeshGrid();

	virtual iElement* intrface(void);
  virtual void refresh(void);

  virtual void setNi(int n) {niSoll_ = n; invalidate(this);};
  virtual void setNj(int n) {njSoll_ = n; invalidate(this);};
  virtual void setNk(int n) {nkSoll_ = n; invalidate(this);};
//  virtual int ni(void);
//  virtual int nj(void);
//  virtual int nk(void);
//  virtual int nIJK(int ijk){if (ijk%3==0) return ni(); else if (ijk%3==1) return nj(); else return nk();};

//  virtual tDot* gridAt(int i, int j, int k);

  virtual void setCorner(int c, tElement* el);
  virtual void setCorners(tList<tElement*> list);
  virtual tDot* corner(int index);
  virtual tList<tElement*> corners(void);
  virtual tList<tElement*> edges(void);
  virtual void setEdge(int e, tElement* el);
  virtual void setEdges(tList<tElement*>list);
  virtual tList<tElement*> faces(void);
  virtual void setFace(int f, tElement* el);
  virtual void setFaces(tList<tElement*> list);

//  virtual void setFaceNames(tList<QString> names);
//  virtual tList<QString> faceNames(void);
};

/*I!
ni Int read:ni write:setNi
nj Int read:nj write:setNj
nk Int read:nk write:setNk
corners DotList read:corners write:setCorners
edges CurveList read:edges write:setEdges
faces SurfaceList read:faces write:setFaces
*/
#endif /*TSTRUCTURED3DBLOCKMESHGRID_H_*/
