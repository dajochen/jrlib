#ifndef TPROPERTYEDITOR_H
#define TPROPERTYEDITOR_H

#include <QWidget>

#include <element/tElement.h>
#include <views/tPropertiesView.h>
#include <views/tTableModelView.h>

namespace Ui {
class tPropertyEditor;
}

class tPropertyEditor : public QWidget, protected tElement
{
    Q_OBJECT

public:
    explicit tPropertyEditor(void* theOwner, QWidget *parent /*= 0*/);
    ~tPropertyEditor();

    void setPropertiesView( tPropertiesView *view);
    void addModelView(tModelView* modelView);
    void removeModelViews(void);

    virtual bool releaseOwner(void *theOwner) { return tElement::releaseOwner(theOwner);}
protected:
    virtual void invalidate(tElement *sender);
    virtual void refresh(void);
    virtual void paintEvent(QPaintEvent * event);


    tPropertiesView *propertiesView;
    QList<tModelView*> additionalModelViews;         // Optional modelViews, which can be used for selection
                                                          // see: addModelView
    QLayout *layout;
    QWidget* editor;

protected slots:
    void setPropertyValue (void);
    void executeAction(void);
private:
    Ui::tPropertyEditor *ui;
};

#endif // TPROPERTYEDITOR_H
