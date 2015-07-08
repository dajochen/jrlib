#include "tPropertyEditor.h"
#include "ui_tPropertyEditor.h"

#include "views/editors/tStringEditor.h"
#include "views/editors/tIntEditor.h"
#include "views/editors/tRealEditor.h"
#include "views/editors/tBoolEditor.h"
#include "views/editors/tVectorEditor.h"
#include "views/editors/tElementSelector.h"

#include "views/editors/tActionLauncher.h"


tPropertyEditor::tPropertyEditor(void* theOwner, QWidget *parent) :
    QWidget(parent),
    tElement(theOwner),
    ui(new Ui::tPropertyEditor)
{
    ui->setupUi(this);

    if (parent){
      QHBoxLayout *mainLayout = new QHBoxLayout;
      parent->setLayout(mainLayout);
      mainLayout->addWidget(this);
      mainLayout->setContentsMargins(0,0,0,0);
    } else {
      setWindowModality(Qt::ApplicationModal);
    }


    layout = new QVBoxLayout;
    layout->setSpacing(3);
    layout->setContentsMargins(0,2,0,2);
    this->setLayout(layout);

    editor = NULL;
    propertiesView = NULL;

    //refresh();
    invalidate(this);
}

tPropertyEditor::~tPropertyEditor()
{
    removeModelViews();

    setPropertiesView(NULL);

    delete ui;
}

void tPropertyEditor::setPropertiesView(tPropertiesView *view)
{
    if (propertiesView){
        propertiesView->removeDependent(this);
    }
    propertiesView = view;

    if (propertiesView){
        propertiesView->addDependent(this);
    }
}

void tPropertyEditor::addModelView(tModelView *modelView)
{
    if (modelView){
        modelView->addOwner(this);
        additionalModelViews.append(modelView);
    }
}

void tPropertyEditor::removeModelViews()
{
    foreach(tModelView* modelView, additionalModelViews){
        modelView->releaseOwner(this);
    }
    additionalModelViews.clear();
}

void tPropertyEditor::invalidate(tElement *sender)
{
    tElement::invalidate(sender);
    QWidget::update();
}

void tPropertyEditor::paintEvent(QPaintEvent *event)
{
    tElement::update();
    QWidget::paintEvent(event);
}


void tPropertyEditor::refresh()
{

    if (editor) {
        layout->removeWidget(editor);
        tElementSelector *elSelector = dynamic_cast<tElementSelector*>(editor);
        if (elSelector) {
            elSelector->releaseOwner(this);
        } else {
            delete editor;
        }
        editor = NULL;
    }

    if (propertiesView && propertiesView->activeSelectionSet()) {
        QString property            = propertiesView->selectedProperty();
        QString propertyType        = propertiesView->selectedPropertyType();
        tList<tElement*> selection  = propertiesView->activeSelectionSet()->elements();

        if (selection.count() > 0) {
            tElement *el = selection.at(0);
            int pIndex   = el->intrface()->getPropertyIndex(property);

            if (!el->intrface()->isReadOnly(pIndex)) {
                if (propertyType == "String") {
                    QString value;
                    el->intrface()->getPropertyValue(pIndex, propertyType, &value);
                    editor = new tStringEditor(property + " [" + propertyType + "]", value);
                } else if (propertyType == "Int") {
                    int value;
                    el->intrface()->getPropertyValue(pIndex, propertyType, &value);
                    editor = new tIntEditor(property + " [" + propertyType + "]", value);
                } else if (propertyType == "Real") {
                    double value;
                    el->intrface()->getPropertyValue(pIndex, propertyType, &value);
                    editor = new tRealEditor(property + " [" + propertyType + "]", value);
                } else if (propertyType == "Bool") {
                    bool value;
                    el->intrface()->getPropertyValue(pIndex, propertyType, &value);
                    editor = new tBoolEditor(property + " [" + propertyType + "]", value);
                } else if (propertyType == "Vector") {
                    tVector value;
                    el->intrface()->getPropertyValue(pIndex, propertyType, &value);
                    editor = new tVectorEditor(property + " [" + propertyType + "]", value);
                } else if (propertyType.endsWith("List")) {
                    QStringList nonElementTypes = QString("Int,Real,String,Vector,Bool,RGB").split(',');
                    if (nonElementTypes.contains(propertyType)) {
                        //!!!!! toBeImplemented
                    } else {
                        tList<tElement*> elList;
                        bool ok = el->intrface()->getPropertyValue(pIndex, propertyType, &elList);
                        if (ok) {
                            tElementSelector* selector = new tElementSelector(this, property + " [" + propertyType + "]", propertiesView->model(), elList);
                            selector->addModelViews(additionalModelViews);
                            editor = selector;
                        }
                    }
                } else {
                    tElement* selection = NULL;

                    bool ok = el->intrface()->getPropertyValue(pIndex, "Element", &selection);
                    if (ok) {
                        tElementSelector* selector = new tElementSelector(this, property + " [" + propertyType + "]", propertiesView->model(), selection);
                        selector->addModelViews(additionalModelViews);
                        editor = selector;
                    }
                }

                if (editor) {
                    connect (editor, SIGNAL( valueChanged() ), this, SLOT( setPropertyValue() ));
                }

            } else if (propertyType == "Action") {
                editor = new tActionLauncher(property);
                connect (editor, SIGNAL( actionTriggered() ), this, SLOT( executeAction() ));
            }
        }
    }

    if (editor) {
        layout->addWidget(editor);
    }
}

void tPropertyEditor::setPropertyValue()
{
    if (propertiesView && propertiesView->activeSelectionSet()) {
        QString property = propertiesView->selectedProperty();
        tList<tElement*> selection = propertiesView->activeSelectionSet()->elements();

        if (selection.count() > 0) {

            tStringEditor *stringEditor = dynamic_cast<tStringEditor*>(editor);
            tIntEditor *intEditor = dynamic_cast<tIntEditor*>(editor);
            tRealEditor *realEditor = dynamic_cast<tRealEditor*>(editor);
            tBoolEditor *boolEditor = dynamic_cast<tBoolEditor*>(editor);
            tVectorEditor *vectorEditor = dynamic_cast<tVectorEditor*>(editor);
            tElementSelector *elementSelector = dynamic_cast<tElementSelector*>(editor);

            if (stringEditor) {
                QString value = stringEditor->value();
                for (int i=0; i<selection.count(); i++) {
                    tElement *el = selection.at(i);
                    int pIndex  = el->intrface()->getPropertyIndex(property);
                    el->intrface()->setPropertyValue(pIndex,"String", &value);
                }
            } else if (intEditor) {
                int value = intEditor->value();
                for (int i=0; i<selection.count(); i++) {
                    tElement *el = selection.at(i);
                    int pIndex  = el->intrface()->getPropertyIndex(property);
                    el->intrface()->setPropertyValue(pIndex,"Int", &value);
                }
            } else if (realEditor) {
                double value = realEditor->value();
                for (int i=0; i<selection.count(); i++) {
                    tElement *el = selection.at(i);
                    int pIndex  = el->intrface()->getPropertyIndex(property);
                    el->intrface()->setPropertyValue(pIndex,"Real", &value);
                }
            } else if (boolEditor) {
                bool value = boolEditor->value();
                for (int i=0; i<selection.count(); i++) {
                    tElement *el = selection.at(i);
                    int pIndex  = el->intrface()->getPropertyIndex(property);
                    el->intrface()->setPropertyValue(pIndex,"Bool", &value);
                }
            } else if (vectorEditor) {
                tVector value = vectorEditor->value();
                for (int i=0; i<selection.count(); i++) {
                    tElement *el = selection.at(i);
                    int pIndex  = el->intrface()->getPropertyIndex(property);
                    el->intrface()->setPropertyValue(pIndex,"Vector", &value);
                }
            } else if (elementSelector) {
                if (elementSelector->maxSelectableItems() == 1) {
                    tElement *selectedElement = elementSelector->selectedElement();
                    for (int i=0; i<selection.count(); i++) {
                        tElement *el = selection.at(i);
                        int pIndex  = el->intrface()->getPropertyIndex(property);
                        QString propType = el->intrface()->getPropertyType(pIndex);
                        el->intrface()->setPropertyValue(pIndex, propType, selectedElement);
                    }
                } else {
                    tList<tElement*> selected = elementSelector->selectedElements();
                    for (int i=0; i<selection.count(); i++) {
                        tElement *el = selection.at(i);
                        int pIndex  = el->intrface()->getPropertyIndex(property);
                        QString propType = el->intrface()->getPropertyType(pIndex);
                        el->intrface()->setPropertyValue(pIndex, propType, &selected);
                    }
                }

            }
        }
    }

}

void tPropertyEditor::executeAction()
{
    if (propertiesView && propertiesView->activeSelectionSet()) {
        QString actionName = propertiesView->selectedProperty();
        tList<tElement*> selection = propertiesView->activeSelectionSet()->elements();

        for (int i=0; i<selection.count(); i++) {
            tElement *el = selection.at(i);
            el->intrface()->runAction(el->intrface()->getActionIndex(actionName));
        }
    }
}

