#ifndef TMODELVIEW_H_
#define TMODELVIEW_H_

#include "model/tModel.h"
#include "model/tSelectionSet.h"

/**
 * @brief The tModelView class
 *
 * tModelView is a base class for a QObject-class, like gui-objects, which are at
 * the tail of the update mechanism. The main feature is, that the invalidate(sender)
 * calls of the model is transfered to an invalidate slot of the derived QObject class.
 *
 * See also: tTableModelView, tGLModelView, tSelectionView
 *
 * The tModelView object has the possibility to reference tElements within fSelectables.
 * Such a fSelectable can be registered in the Model via registerSelectables. If done so,
 * only those elements ocurring in fSelectables can be selected. Only one object may
 * controll the selectables of a model.
 */
class tModelView : public tElement
{
protected:
  tModel *fmodel;
  QHash<void*, tSelectionSet*> selectionSets;
  void *fActiveKey;

public:
  tModelView (void* theOwner);
  virtual ~tModelView();

  virtual tModel *model(void){return fmodel;}
  virtual void setModel(tModel *theModel);

  virtual tSelectionSet* selectionSet(void* key);
  virtual void setSelectionSet(tSelectionSet *newSet, void* key); //Several SelectionSets can be accessed.
                                    // Each can be accessed via a key. Typically the key is a pointer
                                    // of the object which added the selectionSet.
  virtual void removeSelectionSets(void);
  virtual void activateSelectionSet(void* key);
  virtual tSelectionSet* activeSelectionSet(void);
  virtual void* activeKey(void);

  virtual void repaintElement(tElement *sender);

};

#endif /*TMODELVIEW_H_*/
