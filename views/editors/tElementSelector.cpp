#include "tElementSelector.h"
#include "ui_tElementSelector.h"


/* A construtor of single selection*/
tElementSelector::tElementSelector(void *theOwner,
                                   QString property,
                                   tModel* model,
                                   tElement *element,
                                   QWidget *parent) :
    QWidget(parent),
    tElement(theOwner),
    ui(new Ui::tElementSelector)
{
    ui->setupUi(this);
    ui->property->setText(property);

    propertyValue = new tSelectionSet(this, false, 1);
    propertyValue->append(element);
    propertyValue->addDependent(this);

    summary = new tSelectionSummary(this, ui->selectionSummaryWidget);
    summary->setSelectionSet(propertyValue, this);

    preSelection = new tSelectionSet(this, false, 1);
    preSelection->addDependent(this);


    preSelectionView = new tTableModelView(this, ui->tableViewWidget);
    preSelectionView->setModel(model);
    addModelView(preSelectionView);

   // connect(ui->applyButton, SIGNAL(clicked()), this, SIGNAL(addSelectedItems()));

}

/* A construtor to selectmore than one element*/
tElementSelector::tElementSelector(void *theOwner,
                                   QString property,
                                   tModel* model,
                                   tList<tElement *> elList,
                                   QWidget *parent):
    QWidget(parent),
    tElement(theOwner),
    ui(new Ui::tElementSelector)
{
    ui->setupUi(this);
    ui->property->setText(property);


    propertyValue = new tSelectionSet(this, true, -1);
    propertyValue->setElements(elList);
    propertyValue->addDependent(this);

    summary = new tSelectionSummary(this, ui->selectionSummaryWidget);
    summary->setSelectionSet(propertyValue, this);

    preSelection = new tSelectionSet(this, true, 1);
    preSelection->addDependent(this);


    preSelectionView = new tTableModelView(this, ui->tableViewWidget);
    preSelectionView->setModel(model);
    addModelView(preSelectionView);

}

tElementSelector::~tElementSelector()
{
    preSelectionView->releaseOwner(this);

    removeModelViews();

    summary->releaseOwner(this);

    preSelection->removeDependent(this);
    preSelection->releaseOwner(this);

    propertyValue->removeDependent(this);
    propertyValue->releaseOwner(this);

    delete ui;
}

tElement *tElementSelector::selectedElement()
{
    return propertyValue->element(0);
}

tList<tElement *> tElementSelector::selectedElements()
{
    return propertyValue->elements();
}

void tElementSelector::addModelView(tModelView *modelView)
{
    if (modelView && !originalKeys.contains(modelView)) {
        void* origKey = modelView->activeKey();
        originalKeys[modelView] = origKey;

        modelView->addOwner(this);
        modelView->setSelectionSet(preSelection,this);
        modelView->activateSelectionSet(this);
    }
}

void tElementSelector::addModelViews(QList<tModelView *> modelViews)
{
    tModelView *modelView;
    foreach (modelView, modelViews) {
        addModelView(modelView);
    }
}

void tElementSelector::removeModelViews()
{
    QList<tModelView*> views = originalKeys.keys();
    for (int i=0; i<views.count(); i++){
        tModelView* view = views[i];
        view->setSelectionSet(NULL, this);
        view->activateSelectionSet(originalKeys[view]);
        view->releaseOwner(this);
    }
    originalKeys.clear();
}

/*
void tElementSelector::removeModelView(tModelView *modelView)
{
    if (modelView){
        void* originalKey = originalKeys[modelView];
        originalKeys.remove(modelView);
        modelView->activateSelectionSet(originalKey);
        modelView->setSelectionSet(NULL, this);
        modelView->releaseOwner(this);
    }
}*/



void tElementSelector::invalidate(tElement* sender)
{
    if (sender == preSelection) {
        if (isValid) {
            tElement::invalidate(sender);

            tList<tElement*> pre = preSelection->elements();
            preSelection->clear();
            for (int i=0; i<pre.count(); i++) {
                propertyValue->append(pre.at(i));
            }
            tElement::update();
        }

    } else if (sender == propertyValue) {
        tElement::invalidate(sender);
        emit valueChanged();
    }


}

void tElementSelector::addSelectedItems()
{
}
