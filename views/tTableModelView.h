#ifndef TTABLEMODELVIEW_H
#define TTABLEMODELVIEW_H

#include "views/tModelView.h"

#include <QWidget>
#include <QTreeWidgetItem>


namespace Ui {
class tTableModelView;
}

class tTmvWidgetItem : public QTreeWidgetItem
{
private:
    tElement* fReference;
public:
    tTmvWidgetItem(QTreeWidgetItem *parent, const QStringList &strings, tElement *el):
        QTreeWidgetItem(parent, strings),
        fReference(el)        { if (fReference) {fReference->addOwner(this); }    }
    tTmvWidgetItem(QTreeWidgetItem *parent, QTreeWidgetItem *preceding, const QStringList &strings, tElement *el):
        QTreeWidgetItem(parent, preceding),
        fReference(el)        { if (fReference) {fReference->addOwner(this); }
        for (int i=0; i<strings.count(); i++) {
            setText(i, strings[i]);
        }
    }
    virtual ~tTmvWidgetItem() { if (fReference) { fReference->releaseOwner(this); } }
    tElement* reference(void) { return fReference; }
};

class tTableModelView : public QWidget, public tModelView
{
    Q_OBJECT

public:
    explicit tTableModelView(void* theOwner, QWidget *parent /*= 0*/);
    ~tTableModelView();

protected:
    virtual void invalidate(tElement *sender);
    virtual void refresh(void);
    virtual void paintEvent(QPaintEvent * event);

    virtual void processLayerContent( tLayer *l, QTreeWidgetItem *parent);

protected slots:
    virtual void updateSelectionSet(void);
    virtual void itemDoubleClicked(QTreeWidgetItem * item, int);


private:
    Ui::tTableModelView *ui;


};

#endif // TTABLEMODELVIEW_H
