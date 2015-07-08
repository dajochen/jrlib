#include "tAvailableTypesViewer.h"
#include "ui_tAvailableTypesViewer.h"

tAvailableTypesViewer::tAvailableTypesViewer(void* theOwner, QWidget *parent, tModel *m) :
    QWidget(parent),
    tModelView(theOwner),
    ui(new Ui::tAvailableTypesViewer)
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
  isValid = false;
  connect(ui->typeWidget,  SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SIGNAL(availableTypeChanged()));

  setModel(m);
}

tAvailableTypesViewer::~tAvailableTypesViewer()
{
    delete ui;
}

bool tAvailableTypesViewer::isCheckedType(tElement *el)
{
  tElement::update();
  for (int i=0; i<ui->typeWidget->topLevelItemCount(); i++){
      QTreeWidgetItem *item = ui->typeWidget->topLevelItem(i);
      if (item->checkState(0)==Qt::Checked
          && el->intrface()->isOfType(item->text(0))){
        return true;
      }
  }
  return false;
}

void tAvailableTypesViewer::setTypeFilter(QStringList typeList)
{
  ftypeFilter = typeList;
  invalidate(this);
}

void tAvailableTypesViewer::invalidate(tElement *sender)
{
  tElement::invalidate(sender);
  QWidget::update();
}

void tAvailableTypesViewer::refresh()

{
  QStringList types;
  for( int i=0; fmodel && i<fmodel->nElements(); i++){
    processElement(fmodel->element(i), types);
  }

  int i;
  for (i=0; i<types.count(); i++){
    QString type = types[i];
    if (i >= ui->typeWidget->topLevelItemCount()
        || type != ui->typeWidget->topLevelItem(i)->text(0)){
      QTreeWidgetItem* item = new QTreeWidgetItem(types[i].split("|"));
      item->setCheckState(0,Qt::Checked);
      ui->typeWidget->insertTopLevelItem(i,item);
    }
  }
  while (i < ui->typeWidget->topLevelItemCount()){
    //int counter = ui->typeWidget->topLevelItemCount();
    ui->typeWidget->takeTopLevelItem(i);
  }
}

void tAvailableTypesViewer::paintEvent (QPaintEvent * event)
{
  tElement::update();
  QWidget::paintEvent(event);
}

void tAvailableTypesViewer::processElement(tElement *el, QStringList& types)
{
  QStringList typeList = el->intrface()->inheritedTypes();
  for (int i=0; i<typeList.count(); i++){
    if (!types.contains(typeList[i])){
      if (   ftypeFilter.isEmpty()
          || ftypeFilter.contains(typeList[i])){
        types.append(typeList[i]);
      }
    }
  }

  tLayer *layer = dynamic_cast<tLayer*>(el);
  for (int i=0; layer && i<layer->nElements(); i++){
    processElement(layer->element(i), types);
  }
}



