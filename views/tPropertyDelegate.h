#ifndef TPROPERTYDELEGATE_H_
#define TPROPERTYDELEGATE_H_

#include <QObject>
#include <QItemDelegate>
#include <QModelIndex>
#include <QSize>
#include <QSpinBox>
#include <QColorDialog>

#include "model/tModel.h"
#include "views/tModelView.h"

class tPropertyDelegate : public QItemDelegate, private tElement
{
Q_OBJECT
private:
  tModel *fGeometryModel;
  tGroup* selection;
  tList<tModelView*> fElementSelector;
  int currentIndex;

  void lockSelection(void) const;
  void unlockSelection(void) const;

private:
  virtual void refresh(void);

public:
	tPropertyDelegate(QObject *parent=0);
	virtual ~tPropertyDelegate();

    virtual void setSelection(tGroup *sel);
    void setReferenceModel(tModel *m);
    virtual void addElementSelector(tModelView *modelView);
    virtual void removeElementSelectors(void);
  void setCurrentProperty(int index){currentIndex = index;}

  QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif /*TPROPERTYDELEGATE_H_*/
