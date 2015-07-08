#include "tSelectionSummary.h"
#include "ui_tSelectionSummary.h"

tSelectionSummary::tSelectionSummary(void *theOwner, QWidget *parent) :
    QWidget(parent),
    tModelView(theOwner),
    ui(new Ui::tSelectionSummary)
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
}

tSelectionSummary::~tSelectionSummary()
{
    delete ui;
}

void tSelectionSummary::invalidate(tElement *sender)
{
    tElement::invalidate(sender);
    QWidget::update();
}

void tSelectionSummary::refresh()
{
    QListWidgetItem* selItem = ui->listWidget->currentItem();
    const tElement* selElement = itemHash[selItem];
    selItem = NULL;

    itemHash.clear();
    ui->listWidget->clear();

    if (activeSelectionSet()) {
        ui->positionSpinBox->setMinimum(0);
        ui->positionSpinBox->setMaximum(activeSelectionSet()->nElements()-1);
        for (int i=0; i<activeSelectionSet()->nElements(); i++) {
            tElement *el = activeSelectionSet()->element(i);
            QListWidgetItem *item = new QListWidgetItem(el->intrface()->name());
            if (el == selElement){
                selItem = item;
            }
            ui->listWidget->addItem(item);
            itemHash[item] = el;
        }
        if (selItem) {
            selItem->setSelected(true);
            ui->listWidget->setCurrentItem(selItem);
        }
    } else {
        ui->positionSpinBox->setMinimum(0);
        ui->positionSpinBox->setMaximum(0);
    }
}

void tSelectionSummary::paintEvent(QPaintEvent *event)
{
    tElement::update();
    QWidget::paintEvent(event);
}

void tSelectionSummary::on_removeButton_clicked()
{
    int row = ui->listWidget->currentRow();
    if (row >= 0 && activeSelectionSet()){
        activeSelectionSet()->removeElement(row);
    }
}

void tSelectionSummary::on_clearButton_clicked()
{
    if (activeSelectionSet()) {
        activeSelectionSet()->clear();
    }
}

void tSelectionSummary::on_reverseButton_clicked()
{
   if (activeSelectionSet()) {
       activeSelectionSet()->reverse();
   }
}

void tSelectionSummary::on_listWidget_currentRowChanged(int currentRow)
{
    if (currentRow >= 0){
        disconnect(ui->positionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(positionSpinBox_valueChanged(int)));
        ui->positionSpinBox->setValue( currentRow );
        connect(ui->positionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(positionSpinBox_valueChanged(int)));
        ui->positionSpinBox->setEnabled(true);
    } else {
        ui->positionSpinBox->setEnabled(false);
    }
}

void tSelectionSummary::positionSpinBox_valueChanged(int i)
{
    int currentRow = ui->listWidget->currentRow();
    if (activeSelectionSet()){
        activeSelectionSet()->moveElement(currentRow, i);
    }

}

