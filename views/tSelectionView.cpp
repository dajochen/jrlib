#include "tSelectionView.h"
#include "classes/tVectorStringConverter.h"
#include <QHBoxLayout>

tSelectionView::tSelectionView(QWidget *parent, tSelectionSet *set)
  : QTableWidget(parent),
    tElement(NULL),
    selectionSet(NULL)
{

  //setModel(model);
  setSelectionSet(set);


  QHBoxLayout *mainLayout = new QHBoxLayout;
  if (parent){
    parent->setLayout(mainLayout);
    mainLayout->addWidget(this);
    mainLayout->setContentsMargins(0,0,0,0);
  } else {
    setWindowModality(Qt::ApplicationModal);
  }

  verticalHeader()->hide();
  setItemDelegate(&delegate);
  horizontalHeader()->setStretchLastSection(true);

  connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(editProperty(int)));
}
//-----------------------------------------------------------------------------

tSelectionView::~tSelectionView()
{
    //setModel(NULL);
    setSelectionSet(NULL);
}

void tSelectionView::addElementSelector(tModelView *modelView)
{
    delegate.addElementSelector(modelView);
}
//-----------------------------------------------------------------------------

void tSelectionView::setSelectionSet(tSelectionSet *set)
{
    if (selectionSet!=set){
      if (selectionSet){
        selectionSet->removeDependent(this);
      }
      selectionSet = set;
      if (selectionSet){
        selectionSet->addDependent(this);
      }
      invalidate(this);
    }
}
//-----------------------------------------------------------------------------
/*
void tSelectionView::setModel(tModel *m)
{
  if (m!=fmodel){
    if (fmodel){
      fmodel->releaseOwner(this);
    }
    fmodel = m;
    if (fmodel){
      fmodel->addOwner(this);
    }
    delegate.setReferenceModel(fmodel);
    invalidate(this);
  }
}*/
//-----------------------------------------------------------------------------

void tSelectionView::invalidate(tElement *sender)
{
    clear();
    tElement::invalidate(sender);
    QTableWidget::update();
}
//-----------------------------------------------------------------------------

void tSelectionView::paintEvent(QPaintEvent *event)
{
  tElement::update();
  QTableWidget::paintEvent(event);
}
//-----------------------------------------------------------------------------

/**
 * Empties the table and also resets the propertyIndex-list, which is connected to the table.
 */
void tSelectionView::clear(void)
{
  propertyIndex.clear();
  propertyType.clear();
  QTableWidget::clear();
  setHorizontalHeaderLabels(QString("Eigenschaft,Wert").split(","));
  setRowCount(propertyIndex.count());
  setColumnCount(2);
}
//-----------------------------------------------------------------------------

void tSelectionView::refresh(void)
{

	int i,j, index;
	QStringList propertyName;
	QString propertyValue;
	QString type;
	tElement *el;
	iElement *intrface;
  QTableWidgetItem *item;

  clear();


  if (selectionSet){
    selectionSet->lockElement();

    // collect properties
    for (i=0;i<selectionSet->nElements();i++){
      el = selectionSet->element(i);
      intrface = el->intrface();
      if (i==0){
        for (j=intrface->nProperties()-1;j>=0;j--){
          propertyIndex.prepend(j);
          propertyName.prepend(intrface->getPropertyName(j));
          propertyType.prepend(intrface->getPropertyType(j));
        }
      } else {
        for (j=0;j<propertyIndex.count();j++){
          index = propertyIndex.at(j);
          if (intrface->getPropertyName(index) != propertyName.at(j) ||
              intrface->getPropertyType(index) != propertyType.at(j)){
            propertyIndex.removeAt(j);
            propertyName.removeAt(j);
            propertyType.removeAt(j);
            j--;
          }
        }
      }
    }
    //read property values
    if (selectionSet->nElements()){
      el = selectionSet->last();
      setHorizontalHeaderLabels(QString("Eigenschaft,Wert").split(","));
      if (el){
        intrface = el->intrface();
        setRowCount(propertyIndex.count());
        setColumnCount(2);

        for (j=0;j<propertyIndex.count();j++){
          type = propertyType.at(j);
          index = propertyIndex.at(j);
          if (type == "String"){
            intrface->getPropertyValue(index, type, &propertyValue);
          } else if (type == "Int"){
            int value;
            intrface->getPropertyValue(index, type, &value);
            propertyValue = QString::number(value);
          } else if (type == "Real"){
            tReal value;
            intrface->getPropertyValue(index, type, &value);
            propertyValue = QString::number(value);
          } else if (type == "Bool"){
            bool value;
            intrface->getPropertyValue(index, type, &value);
            if (value){
              propertyValue = "true";
            } else {
              propertyValue = "false";
            }
          } else if (type == "Vector"){
            tVector value;
            intrface->getPropertyValue(index, type, &value);
            propertyValue = tVectorStringConverter::toString(value,";");
          } else if (type == "RGB"){
            tRGB value;
            intrface->getPropertyValue(index, type, &value);
            propertyValue = tVectorStringConverter::toString(value.toVector(),";");
          } else if (type.endsWith("List")){
            propertyValue = "";
            if (type.startsWith("Int")){
              tList<int> value;
              intrface->getPropertyValue(index, type, &value);
              if (value.count()>0){
                for (i=0;i<value.count();i++){
                  propertyValue.append(QString::number(value.at(i))+ ";");
                }
              }
            } else if (type.startsWith("Real")){
              tList<tReal> value;
              intrface->getPropertyValue(index, type, &value);
              if (value.count()>0){
                for (i=0;i<value.count();i++){
                  propertyValue.append(QString::number(value.at(i))+ ";");
                }
              }
            } else if (type.startsWith("String")){
              tList<QString> value;
              intrface->getPropertyValue(index, type, &value);
              if (value.count()>0){
                for (i=0;i<value.count();i++){
                  propertyValue.append(value.at(i)+ ";");
                }
              }
            } else if (type.startsWith("Bool")){
              tList<int> value;
              intrface->getPropertyValue(index, type, &value);
              if (value.count()>0){
                for (i=0;i<value.count();i++){
                  if (value.at(i)){
                    propertyValue.append("true;");
                  } else {
                    propertyValue.append("false;");
                  }
                }
              }
            } else {
              tList<tElement*> value;
              tElement *item;
              intrface->getPropertyValue(index, type, &value);
              if (value.count()>0){
                for (i=0;i<value.count();i++){
                  item = value.at(i);
                  if (item) {
                    propertyValue.append(item->intrface()->name()+";");
                  } else {
                    propertyValue.append(";");
                  }
                }
              }
            }
          } else {
            tElement *value=NULL;
            char dbg[500];
            strcpy(dbg,type.toLatin1().data());
            intrface->getPropertyValue(index, type, &value);
            if (value){
              propertyValue = value->intrface()->name();
            } else {
              propertyValue = "None";
            }
          }

          item = new QTableWidgetItem(propertyName.at(j));
          item->setFlags(Qt::ItemIsEnabled);
          item->setBackground(QBrush(QColor(240,240,240)));
          setItem(j, 0, item);

          item = new QTableWidgetItem(propertyValue);
          if (intrface->isReadOnly(index)){
            item->setFlags(Qt::ItemIsEnabled);
            item->setBackground(QBrush(QColor(240,240,240)));
          }
          setItem(j, 1, item);
        }
      }
    }

    selectionSet->unlockElement();
  }
}
//-----------------------------------------------------------------------------

void tSelectionView::editProperty(int tableIndex)
{
  if (tableIndex>=0){
    delegate.setCurrentProperty(propertyIndex.at(tableIndex));
  } else {
    delegate.setCurrentProperty(-1);
  }
}
