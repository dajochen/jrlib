#ifndef TELEMENTSELECTOR_H
#define TELEMENTSELECTOR_H

#include <QWidget>
#include <model/tSelectionSet.h>
#include <views/tModelView.h>
#include <views/tSelectionSummary.h>
#include <views/tTableModelView.h>

namespace Ui {
class tElementSelector;
}

class tElementSelector : public QWidget, public tElement
{
    Q_OBJECT

public:
    explicit tElementSelector(void *theOwner, QString property, tModel *model, tElement* element, QWidget *parent = 0);
    explicit tElementSelector(void* theOwner, QString property, tModel *model, tList<tElement*> elList, QWidget *parent = 0);
    virtual ~tElementSelector();

    virtual tElement* selectedElement(void);
    virtual tList<tElement*> selectedElements(void);
    virtual int maxSelectableItems(void) {return propertyValue->maxSelectableItems();}
    virtual void addModelView(tModelView* modelView); //Adds a tModelView which is used for selection.
    virtual void addModelViews(QList<tModelView*> modelViews); //Adds a tModelView which is used for selection.
    virtual void removeModelViews(); //and removes them (beginning with the last one.

signals:
    void valueChanged(void);

protected:
    tSelectionSet* preSelection;
    tSelectionSet* propertyValue;
    tSelectionSummary* summary;
    tTableModelView* preSelectionView;
    //void* originalKey;
    //QList<tModelView*> modelViews;
    QHash<tModelView*, void*> originalKeys;

    virtual void invalidate(tElement *sender);
    virtual void refresh(void) {}

protected slots:
    virtual void addSelectedItems(void);

private:
    Ui::tElementSelector *ui;
};

#endif // TELEMENTSELECTOR_H
