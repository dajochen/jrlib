#ifndef TPROPERTIESVIEW_H
#define TPROPERTIESVIEW_H

#include <QWidget>
#include <QTableWidget>
#include <views/tModelView.h>

namespace Ui {
class tPropertiesView;
}

class tPropertiesView : public QWidget, public tModelView
{
    Q_OBJECT

public:
    explicit tPropertiesView(void *theOwner, QWidget *parent /*= 0*/);
    virtual ~tPropertiesView();

    virtual QString selectedProperty(void);
    virtual QString selectedPropertyType(void);


protected:
    virtual void invalidate(tElement *sender);
    virtual void refresh(void);
    virtual void paintEvent(QPaintEvent * event);

    bool keepPropertyTable;

protected slots:
    virtual void selectedItemChanged(QTableWidgetItem * current, QTableWidgetItem * previous);


private:
    Ui::tPropertiesView *ui;
};

#endif // TPROPERTIESVIEW_H
