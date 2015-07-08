#include "tElementCreator.h"

#include <QMessageBox>

tElementCreator::tElementCreator(void *theOwner, QWidget *parent)
    : QWidget(parent),
      tModelView(theOwner)
{
    setupUi(this);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    if (parent){
        parent->setLayout(mainLayout);
        mainLayout->addWidget(this);
        mainLayout->setContentsMargins(0,0,0,0);
    } else {
        setWindowModality(Qt::ApplicationModal);
    }
    connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(createElement(QTreeWidgetItem*,int)));
}
//---------------------------------------------------------------------------

tElementCreator::~tElementCreator()
{

}
//---------------------------------------------------------------------------
/*
void tElementCreator::setModel(tModel* m)
{
  model = m;
}*/
//---------------------------------------------------------------------------

void tElementCreator::createElement(QTreeWidgetItem *item, int)
{
  tElement *el;
  tLayer *l;
  QString type;
  if (!model()){
    QMessageBox::warning(this,"jrCAD - Error Creating Element", "No active model available. Don't know where to create an element.");
  } else {
    if (item->childCount()==0){
      l = model()->currentLayer();
      if (l){
        type = item->text(0);
        el = l->addElement(type);
        if (el){
          int i=0;
          while (l->elementByName(type+"_"+QString::number(i))){
            i++;
          }
          el->intrface()->setName(type+"_"+QString::number(i));
          //model->setSelection(el);
          if (activeSelectionSet()) {
              activeSelectionSet()->clear();
              activeSelectionSet()->append(el);
          }
          model()->setCurrentLayer(dynamic_cast<tLayer*>(el));
        } else {
          QMessageBox::information(this,"jrCAD - Error Creating Element","Could not resolve Element name (" + type + ")! \nNo element created." );
        }
      } else {
        QMessageBox::information(this,"jrCAD - Error Creating Element","No active layer avialable." );
      }
    }
  }
}
//---------------------------------------------------------------------------
