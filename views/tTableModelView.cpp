#include "tTableModelView.h"
#include "ui_tTableModelView.h"

tTableModelView::tTableModelView(void *theOwner, QWidget *parent) :
    QWidget(parent),
    tModelView(theOwner),
    ui(new Ui::tTableModelView)
{
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(updateSelectionSet()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

    if (parent){
      QHBoxLayout *mainLayout = new QHBoxLayout;
      parent->setLayout(mainLayout);
      mainLayout->addWidget(this);
      mainLayout->setContentsMargins(0,0,0,0);
    } else {
      setWindowModality(Qt::ApplicationModal);
    }


}

tTableModelView::~tTableModelView()
{
    delete ui;
}

void tTableModelView::invalidate(tElement *sender)
{
    tElement::invalidate(sender);
    QWidget::update();
}

void tTableModelView::paintEvent (QPaintEvent * event)
{
  tElement::update();
  QWidget::paintEvent(event);
}


void tTableModelView::refresh(void)
{
    ui->treeWidget->blockSignals(true);

    if (activeSelectionSet()){
        if (activeSelectionSet()->allowDublicates()) {
           ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        } else {
           ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        }
    } else {
        ui->treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
    }

    processLayerContent(model(), ui->treeWidget->invisibleRootItem());

    ui->treeWidget->blockSignals(false);
}

void tTableModelView::processLayerContent( tLayer *l, QTreeWidgetItem *parent)
{
    if (l && parent) {

        for (int i=0; i<l->nElements(); i++) {
            tElement *el = l->element(i);
            tTmvWidgetItem *item = NULL;
            if (parent->childCount() > i){
                item = dynamic_cast<tTmvWidgetItem*>(parent->child(i));
            } else {
                item = NULL;
            }

            if (item && el == item->reference()) {
                // check if name has changed
                if (item->text(0) != el->intrface()->name()){
                    item->setText(0, el->intrface()->name());
                }
                //item is ok,
            } else {

                QStringList data;
                data.append(el->intrface()->name());
                data.append(el->intrface()->type());

                if (i == 0 /*|| parent->childCount() > i*/) {
                    QList<QTreeWidgetItem*> items = parent->takeChildren();// the structure is modified, so remove all items, so that new items can be inserted at the top.
                    while (items.count()){
                        delete ( items.takeAt(0) );
                    }

                    item = new tTmvWidgetItem(parent, data, el);
                } else {
                    item = new tTmvWidgetItem(parent, parent->child(i-1), data, el);
                }
                if (dynamic_cast<tLayer*>(el)){
                    item->setExpanded(false);
                }
            }

            if (activeSelectionSet() && activeSelectionSet()->contains(el)){
                item->setSelected(true);
                if (activeSelectionSet()->last()==el){
                    ui->treeWidget->scrollToItem(item);
                }
            } else {
                item->setSelected(false);
            }



            tLayer *ll = dynamic_cast<tLayer*>(el);
            if (ll) {
                if (ll == model()->currentLayer()){
                    QFont font = item->font(0);
                    font.setBold(true);
                    item->setFont(0,font);
                   // item->setText(0, "!" + el->intrface()->name());
                } else {
                    QFont font = item->font(0);
                    font.setBold(false);
                    item->setFont(0,font);
                    item->setText(0, el->intrface()->name());
                }
                processLayerContent(ll, item);
            }
        }

        // All elements processed. remove those entries which are not needed any longer.
        while (l->nElements() < parent->childCount()){
            delete  parent->takeChild(parent->childCount()-1);
        }

    }

}

void tTableModelView::updateSelectionSet()
{
    QList<QTreeWidgetItem*> selItems = ui->treeWidget->selectedItems();
    tList<tElement*> selSet;

    for (int i=0; i<selItems.count(); i++) {
        tTmvWidgetItem* tmvItem = dynamic_cast<tTmvWidgetItem*>(selItems[i]);
        selSet.append(tmvItem->reference());
    }
    if (activeSelectionSet()) {
        activeSelectionSet()->setElements(selSet);
    }
}

void tTableModelView::itemDoubleClicked(QTreeWidgetItem *item, int)
{
    tTmvWidgetItem* tmvItem = dynamic_cast<tTmvWidgetItem*>(item);
    tLayer *l = dynamic_cast<tLayer*> (tmvItem->reference());
    if (l){
        model()->setCurrentLayer(l);
        item->setExpanded(!item->isExpanded());
    }

}

