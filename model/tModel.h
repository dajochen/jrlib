#ifndef TMODEL_H_
#define TMODEL_H_

#include "element/variable/tVariableNameSpace.h"
#include "model/tLayer.h"
#include "model/iModel.h"

/* A model is a layer which which is used as a primary layer for all Elements in a jr-Cad-project.
 * - In addition to a layer it offers a VariableNameSpace.
 * - It has an active layer which can be accessed through currentLayer()
 *
 *
 **/

class tModel : public tLayer
{
private:
  void addSupportingPoints(tElement* el,tList<tPoint*>&pList,tList<tRelPoint*>&rpList);
protected:
  tLayer* fCurrentLayer;
  //tList<tElement*> fSelection;
  //tGroup *fSelectable;
  //void *fSelectableController; //only the controller is allowed to change the selectable items.

  tVariableNameSpace *variables;

  virtual void refresh(void);

public:
  tModel(void *theOwner);
  virtual ~tModel();

  virtual iElement* intrface(void);
  tLayer* currentLayer(void);
  void setCurrentLayer(tLayer *layer);

  /** Elements within fModel, which can be selected. */
  //tGroup* selectables(void){setElementLocked update(); return fSelectable;}
  //void setSelectables(tGroup* group);

  /*
   * Edit the selection group.
  */
  /*
   *tList<tElement*> selection(void){setElementLocked update(); return fSelection;}

  void clearSelection(void){setElementLocked fSelection.clear(); invalidate(this);}
  void addToSelection(tElement *el){setElementLocked fSelection.append(el); invalidate(this);}
  void removeFromSelection(tElement *el){setElementLocked fSelection.removeAll(el); invalidate(this);}
  void setSelection(tElement *el);
  void setSelection(const tList<tElement *>el);
*/
  /**
    Modify selected items
  */
  /*
  void shiftSelection(const tVector& dx);
  void rotateSelection(const tVector& origin, const tVector& domega);
  void flipSelection(const tVector& origin, const tVector& flipAxis);
  void doublicateFirstSelectedElement(void);
*/
  void deleteElements(tList<tElement*> toBeDeleted);
  QString name(void){return intrface()->name();}
  void setName(QString name){intrface()->setName(name);}

  // Importfunktionen
  //void importMultiSurf (QString &filename);

  virtual tVector xMin(void);
  virtual tVector xMax(void);

};

/*I!
 */

#endif /*TMODEL_H_*/
