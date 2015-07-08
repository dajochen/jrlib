#ifndef TAVAILABLETYPESVIEWER_H
#define TAVAILABLETYPESVIEWER_H

#include "tModelView.h"

namespace Ui {
class tAvailableTypesViewer;
}

class tAvailableTypesViewer : public QWidget, public tModelView
{
    Q_OBJECT
    
public:
    explicit tAvailableTypesViewer(void* theOwner, QWidget *parent=0, tModel* m=NULL );
    ~tAvailableTypesViewer();
    /** return true, if the Elementtype type is checked*/
    virtual bool isCheckedType(tElement *el);
    /** only types in typeFilter are displayed */
    void setTypeFilter(QStringList typeList);



//  void invalidate(void);
//
//signals:
//  void availableTypeChanged(void);

protected:
  virtual void invalidate(tElement *sender);
  virtual void refresh(void);
//    virtual void updateData(void);
  virtual void paintEvent(QPaintEvent* event);

private:
  Ui::tAvailableTypesViewer *ui;
  QStringList ftypeFilter;
  void processElement(tElement *el, QStringList &types);

};

#endif // TAVAILABLETYPESVIEWER_H
