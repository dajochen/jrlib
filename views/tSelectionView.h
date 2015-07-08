#ifndef TSELECTIONVIEW_H_
#define TSELECTIONVIEW_H_

#include <QTableWidget>

#include "model/tSelectionSet.h"
#include "views/tModelView.h"
#include "tPropertyDelegate.h"
#include "classes/tList.h"



class tSelectionView: public QTableWidget, private tElement
{
  Q_OBJECT
private:
  QTableWidget* widget;

protected:

  tSelectionSet* selectionSet;

  tPropertyDelegate delegate;
  QStringList propertyType;
  tList<int> propertyIndex;

  virtual void invalidate(tElement *sender);
  virtual void refresh(void);
  virtual void clear(void);

public:
  tSelectionView(QWidget *parent=NULL/*, tModel* model=NULL*/, tSelectionSet* set=NULL);
  virtual ~tSelectionView();

  virtual void addElementSelector(tModelView *modelView);
  virtual void setSelectionSet(tSelectionSet* set);
  virtual void paintEvent(QPaintEvent *event);
public slots:
  void editProperty(int tableIndex);
  //void currentlySelectedChanged(const QModelIndex &current, const QModelIndex &previous);
};

#endif /*TSELECTIONVIEW_H_*/
