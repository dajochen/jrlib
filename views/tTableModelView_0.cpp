#include <QHBoxLayout>
#include "tTableModelView_0.h"

#include "classes/utils.h"
#include "element/tDummy.h"

class layerItem : public QTreeWidgetItem
{
  public:
    tLayer *layer;
    layerItem (tLayer *l, QTreeWidgetItem *parent, const QStringList &strings) : QTreeWidgetItem (parent,strings){layer=l;}
    layerItem (tLayer *l, QTreeWidget *parent, const QStringList &strings) : QTreeWidgetItem(parent,strings){layer=l;}
 };
//------------------------------------------------------------------------------

tTableModelView::tTableModelView(QWidget *parent, tModel *m,
                                 tmvSelectionMode selectionMode,
                                 bool useOwnSelectionGroup,
                                 bool showSelectionSummary )
  : QWidget(parent),
    tModelView(NULL)
//    fuseModelSelection(!useOwnSelectionGroup)
{
  //Gui-Setup
  setupUi(this);
  if (parent){
    QHBoxLayout *mainLayout = new QHBoxLayout;
    parent->setLayout(mainLayout);
    mainLayout->addWidget(this);
    mainLayout->setContentsMargins(0,0,0,0);
  } else {
    setWindowModality(Qt::ApplicationModal);
  }

  fAvailableTypes = new tAvailableTypesViewer(availableTypesWidget, m);
  fAvailableTypes->addDependent(this);
  //fSelectables = new tGroup(this);
  //isValid = false;

  fSelectionSet = NULL;
  /*if (fuseModelSelection){
    fSelection = NULL;
  } else {
    fSelection = new tGroup(this);
    fSelection->addDependent(this);
  }*/
  connect(showVisibleOnly,SIGNAL(stateChanged(int)), this, SLOT(invalidate()));
  connect(byNameSelection,SIGNAL(textChanged(QString)),this, SLOT(invalidate()));

  connect(addDummyButton,SIGNAL(clicked()),this, SLOT(addDummy()));
  connect(addToSelectionButton,SIGNAL(clicked()),this, SLOT(extendSelection()));

  elementTable->setColumnCount(3);
  elementTable->setRowCount(0);
  elementTable->setHorizontalHeaderLabels(QString("Name,Type,Layer").split(","));
  elementTable->resizeColumnsToContents();
  elementTable->horizontalHeader()->setStretchLastSection(true);

  // if showSelectionSummary is true all selected elements will be listed in a separate TableWidget
  selectionGroup->setVisible(showSelectionSummary);
  selectionTable->horizontalHeader()->setStretchLastSection(true);
  setSelectionMode(selectionMode);

  setModel(m);
}
//------------------------------------------t-------------------------------------

tTableModelView::~tTableModelView()
{
  fAvailableTypes->removeDependent(this);
  fAvailableTypes->releaseOwner(this);

  setSelectionSet(NULL);
  /*if (fSelection) {
    fSelection->removeDependent(this);
    fSelection->clear();
    fSelection->releaseOwner(this);
  }*/
}
//-------------------------------------------------------------------------------

void tTableModelView::setModel(tModel* theModel)
{
  tModelView::setModel(theModel);
  fAvailableTypes->setModel(theModel);
  if (theModel != fmodel && fSelectionSet) {
      fSelectionSet->clear();
  };
}
//-------------------------------------------------------------------------------
/*
void tTableModelView::setSelectionSet(tSelectionSet *set)
{
  if (fSelectionSet){
      fSelectionSet->removeDependent(this);
  }
  fSelectionSet = set;
  if (fSelectionSet){
      fSelectionSet->addDependent(this);
  }
}*/
//-------------------------------------------------------------------------------

void tTableModelView::invalidate(tElement *sender)
{
  if (sender==NULL){ sender = this; };
  tElement::invalidate(sender);
  QWidget::update();
}
//-------------------------------------------------------------------------------

void tTableModelView::repaintElement()
{
  invalidate(this);
}
//-------------------------------------------------------------------------------
/*void tTableModelView::repaint(void)
{
  invalidate(this);
  //tElement::repaint();
}*/
//-------------------------------------------------------------------------------

/**
 * @brief tTableModelView::paintEvent
 * @param event
 *
 * Performs an update.
 */
void tTableModelView::paintEvent (QPaintEvent * event)
{
  tElement::update();
  QWidget::paintEvent(event);
}
//-------------------------------------------------------------------------------
/**
 * @brief tTableModelView::refresh
 * Updates all tables, etc.
 */
void tTableModelView::refresh(void)
{
  //availableTypes()->tElement::update();
  refreshLayers();
  refreshTable();
  refreshSelectionTable();
}
//-------------------------------------------------------------------------------
/**
 * If useModelSelectionGroup is true, the selected elements will be added to the tGroup fmodel->selection(). (This is the default)
 * Otherwise an own tGroup is created. The selection can always be accessed through the tGroup selection().
 */
/*tGroup* tTableModelView::setModelSelectionUsage(void) const
{
  if (fuseModelSelection){
    return NULL;
    /*if (fmodel && selectionList!=fmodel->selection()){
      if (selectionList){
        selectionList->clear();
        selectionList->releaseOwner(this);
      }
      selectionList = fmodel->selection();
    } else {
      selectionList = NULL;
    }*/
 /* } else {
    //if (!selectionList || selectionList == fmodel->selection()){
    //  selectionList = new tGroup(this);
    return new tGroup(this);
    //}
  }
}*/
//-------------------------------------------------------------------------------
/**Sets the selection mode. This can be: one element only, many elements, special
 * selection mode.
 */
void tTableModelView::setSelectionMode(tmvSelectionMode selectionMode)
{
  fselectionMode = selectionMode;

  if (fselectionMode == tmvSingleSelection){
    elementTable->setSelectionMode(QAbstractItemView::SingleSelection);
    addDummyButton->setVisible(false);
    addToSelectionButton->setVisible(false);
  } else if (fselectionMode == tmvMultipleSelection){
    elementTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    addDummyButton->setVisible(false);
    addToSelectionButton->setVisible(false);
  } else if (fselectionMode == tmvEnhancedSelection){
    elementTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    addDummyButton->setVisible(true);
    addToSelectionButton->setVisible(true);
  }
}
//-------------------------------------------------------------------------------
/**
 * A function used to set up the layer list.
 */
void tTableModelView::addLayerToTreeWidget(tLayer *l, QTreeWidgetItem *parentItem)
{
  int i, ni;
  tLayer *ll;
  QTreeWidgetItem *item;

  QString layerCaption = l->intrface()->name();// + "[" + l->intrface()->type()+"]");
  if (l == fmodel->currentLayer()){
    layerCaption.prepend("! ");
  }

  if (parentItem){
    item = new layerItem(l, parentItem, QStringList(layerCaption));
  } else {
    item = new layerItem(l, layerWidget, QStringList(layerCaption));
  }
  if (l->intrface()->visibility()){
    item->setCheckState(0, Qt::Checked);
  } else {
    item->setCheckState(0, Qt::Unchecked);
  }

  if (l == fmodel->currentLayer()){
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0,font);
  } else {
    QFont font = item->font(0);
    font.setBold(false);
    item->setFont(0,font);
  }


  item->setExpanded( isExpanded.value(l,false) );

  ni = l->nElements();
  for (i=0;i<ni;i++){
    ll = dynamic_cast<tLayer*>(l->element(i));
    if (ll){
      addLayerToTreeWidget(ll, item);
    }
  }
}

//-------------------------------------------------------------------------------
/**
 * Rebuilds the List of the Layers, contained by the model.
 */
void tTableModelView::refreshLayers(void)
{
  disconnect(layerWidget,SIGNAL(itemChanged(QTreeWidgetItem*, int)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  disconnect(layerWidget,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  disconnect(layerWidget,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  disconnect(layerWidget,SIGNAL(itemActivated(QTreeWidgetItem*, int)),this,SLOT(currentLayerChanged(QTreeWidgetItem*)));

  layerWidget->clear();
  if (fmodel){
    addLayerToTreeWidget(fmodel);
  }
  connect(layerWidget,SIGNAL(itemChanged(QTreeWidgetItem*, int)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  connect(layerWidget,SIGNAL(itemExpanded(QTreeWidgetItem*)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  connect(layerWidget,SIGNAL(itemCollapsed(QTreeWidgetItem*)),this,SLOT(setLayerVisibility(QTreeWidgetItem*)));
  connect(layerWidget,SIGNAL(itemActivated(QTreeWidgetItem*, int)),this,SLOT(currentLayerChanged(QTreeWidgetItem*)));
}
//-------------------------------------------------------------------------------

void tTableModelView::setLayerVisibility(QTreeWidgetItem *item)
{
  layerItem *lItem;

  lItem = dynamic_cast<layerItem*>(item);
  if (lItem){
    if (item->checkState(0)==Qt::Checked){
      lItem->layer->intrface()->setVisibility(true);
    } else {
      lItem->layer->intrface()->setVisibility(false);
    }

    if (lItem->isExpanded()){
      isExpanded[lItem->layer] = true;
    } else {
      isExpanded[lItem->layer] = false;
    }
  }
  invalidate(this);
}
//-------------------------------------------------------------------------------
/**
 * @brief tTableModelView::currentLayerChanged A double click on the layer makes it the current layer within the model.
 * @param current
 */
void tTableModelView::currentLayerChanged( QTreeWidgetItem *current )
{
  layerItem *lItem;

  lItem = dynamic_cast<layerItem*>(current);
  if (lItem){
    if (current->checkState(0)==Qt::Checked){
      fmodel->setCurrentLayer(lItem->layer);
    } else {
      ///XXX???
    }
  }
  invalidate(this);

}

//-------------------------------------------------------------------------------
/**
 * Adds the content of a Layer to the table of selectable Elements
 */
void tTableModelView::addLayerToTable(tLayer *G, const QString& firstSyllable, int &lastRow)
{

  tList<tElement*> selectionList;
  if (fSelectionSet) {
      selectionList = fSelectionSet->elements();
  };

  /*if (fuseModelSelection){
    selectionList = fmodel->selection();
  } else {
    selectionList = fSelection->elements();
  }*/

  QString LayerName;
  tElement *el;
  if (G->intrface()->visibility()) {
    LayerName = G->intrface()->getPropertyString("name");
    elementTable->setRowCount(elementTable->rowCount()+G->nElements());

    for (int i=0;i<G->nElements();i++) {
      el = G->element(i);
      if (el){
        el->lockElement();

        // Prufen, ob das Element in die Liste der zulaessigen Elemente faellt.
        if (fAvailableTypes->isCheckedType(el)
          && (!showVisibleOnly->isChecked() || el->intrface()->visibility())
          && (firstSyllable.isEmpty() || el->intrface()->name().startsWith(firstSyllable))){
            // ein Element in die Tabelle eintragen.
            elementTable->setItem(lastRow,0,new QTableWidgetItem(el->intrface()->getPropertyString("name")));
            elementTable->setItem(lastRow,1,new QTableWidgetItem(el->intrface()->type()));
            elementTable->setItem(lastRow,2,new QTableWidgetItem(LayerName));
            if (fSelectionSet && fSelectionSet->contains(el)){
              elementTable->item(lastRow,0)->setSelected(true);
              elementTable->item(lastRow,1)->setSelected(true);
              elementTable->item(lastRow,2)->setSelected(true);
            } else {
              elementTable->item(lastRow,0)->setSelected(false);
              elementTable->item(lastRow,1)->setSelected(false);
              elementTable->item(lastRow,2)->setSelected(false);
            }
            fSelectablesList.append(el);
            // die spaetere Zuordnung der Elemente erfolgt ueber die Liste fSelectablesList: in der Art: "fSelectablesList(item->row)"
            lastRow++;
        } else {
          //Check if
          //if (selectionList.contains(el)){
          if (fSelectionSet) {
              fSelectionSet->removeAllElements(el);
          }
            /*if (fuseModelSelection){
              fmodel->removeFromSelection(el);
            } else if(fSelection){
              fSelection->removeAllElements(el);
            }*/
          //}
        }

        if (dynamic_cast<tLayer*>(el)){
          addLayerToTable(dynamic_cast<tLayer*>(el), firstSyllable, lastRow);
          int nRows = elementTable->rowCount()+G->nElements();
          elementTable->setRowCount(nRows);
        }

        el->unlockElement();
      }
    }

    // the upper setRowCount is just a guess
    elementTable->setRowCount(lastRow);
  }
}
//-------------------------------------------------------------------------------
/**
 * Rebuilds the list of the selectable elements.
 */
void tTableModelView::refreshTable(void){
//  setElementLocked

  int lastRow = 0;
  QString firstSyllable;

  // Signal und Slot unterbrechen, um eine endlosschleife durch das Editieren der Elemente zu vermeiden.
  //if (fselectionMode == tmvSingleSelection || fselectionMode == tmvMultipleSelection){
  //  disconnect(elementTable, SIGNAL(itemSelectionChanged()), this, SLOT(setSelection()));
  //}
  if (fselectionMode == tmvSingleSelection || fselectionMode == tmvMultipleSelection){
    disconnect(elementTable, SIGNAL(itemSelectionChanged()), this, SLOT(setSelection()));
  } else if (fselectionMode == tmvEnhancedSelection){
    disconnect(elementTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(extendSelection(QTableWidgetItem*)));
    disconnect(selectionTable, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(setSelectionArrangementSpinBox(int)));
  }

  fSelectablesList.clear();

  firstSyllable = byNameSelection->text();

  if (fmodel){
    fmodel->lockElement();
    elementTable->clearSelection();
    elementTable->setRowCount(0);

    // Element abarbeiten
    addLayerToTable(fmodel, firstSyllable, lastRow);
    selectionSet()->setElements(fSelectablesList);
    fmodel->unlockElement();
  } else {
  	elementTable->clearSelection();
    elementTable->setRowCount(0);
  }
  elementTable->resizeRowsToContents();

  //if (fselectionMode == tmvSingleSelection || fselectionMode == tmvMultipleSelection){
  //  connect(elementTable, SIGNAL(itemSelectionChanged()), this, SLOT(setSelection()));
  //}
  if (fselectionMode == tmvSingleSelection || fselectionMode == tmvMultipleSelection){
    connect(elementTable, SIGNAL(itemSelectionChanged()), this, SLOT(setSelection()));
  } else if (fselectionMode == tmvEnhancedSelection){
    connect(elementTable, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(extendSelection(QTableWidgetItem*)));
    connect(selectionTable, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(setSelectionArrangementSpinBox(int)));
  }

  //isValid = true;// sollte hier schon true sein...

}
//-------------------------------------------------------------------------------

void tTableModelView::refreshSelectionTable(void)
{
  if (fSelectionSet) {
    selectionTable->setRowCount(fSelectionSet->nElements());
    for (int i; i<fSelectionSet->nElements(); i++){
        tElement *el = fSelectionSet->element(i);
        if (el){
          selectionTable->setItem(i,0,new QTableWidgetItem(el->intrface()->name()));
          selectionTable->setItem(i,1,new QTableWidgetItem(el->intrface()->type()));
        } else {
          selectionTable->setItem(i,0,new QTableWidgetItem("*"));
          selectionTable->setItem(i,1,new QTableWidgetItem("dummy object"));
        }
    }
    selectionTable->resizeRowsToContents();
  }

  /*
  if (fSelection){
    selectionTable->setRowCount(fSelection->nElements());
    for (int i=0;i<fSelection->nElements();i++){
      tElement *el = fSelection->element(i);
      if (el){
        selectionTable->setItem(i,0,new QTableWidgetItem(el->intrface()->name()));
        selectionTable->setItem(i,1,new QTableWidgetItem(el->intrface()->type()));
      } else {
        selectionTable->setItem(i,0,new QTableWidgetItem("*"));
        selectionTable->setItem(i,1,new QTableWidgetItem("dummy object"));
      }
    }
    selectionTable->resizeRowsToContents();
  }*/
}
//-------------------------------------------------------------------------------
/**
 * @brief tTableModelView::clearSelection
 *
 */
void tTableModelView::on_clearSelectionButton_clicked(void)
{
  if (fSelectionSet){
      fSelectionSet->clear();
  }
/*  if (fmodel && fSelection){
    fmodel->lockElement();
    fSelection->clear();
    highlightedSelectionRow = 0;
    fmodel->unlockElement();
  }*/
}
//-------------------------------------------------------------------------------
/**
 * Use the currently selected elements as selection.
 */
void tTableModelView::setSelection(void)
{
  int row;
  tList<tElement*> selectionList;

  if (fSelectionSet && fmodel) {
    fmodel->lockElement();
    for (row=0; row<fSelectablesList.count(); row++){
      tElement *el = fSelectablesList.at(row);
      if (elementTable->item(row,0)->isSelected()){
            selectionList.append(el);
      }
    }
    fSelectionSet->setElements(selectionList);


    fmodel->unlockElement();
  }
}
//-------------------------------------------------------------------------------
/**
 * Add the currently selected elements to the selection.
 */
void tTableModelView::extendSelection(QTableWidgetItem *)
{
    int row;
    if (fSelectionSet){
        if (fmodel) fmodel->lockElement();
        for (row=0; row<fSelectablesList.count(); row++) {
            if (elementTable->item(row,0)->isSelected()){
                fSelectionSet->append(fSelectablesList.at(row));
            }
        }
        if (fmodel) fmodel->unlockElement();
    }
}

//-------------------------------------------------------------------------------

void tTableModelView::setSelectionArrangementSpinBox(int row)
{ /*
  row++;
  highlightedSelectionRow = row;
  selectionSpinBox->setValue(row);
  selectionSpinBox->setMinimum(0+1);
  selectionSpinBox->setMaximum(selectionTable->rowCount());*/
}
//-------------------------------------------------------------------------------

void tTableModelView::on_selectionSpinBox_valueChanged(int newRow)
{/*
  //newRow++; // Modify counter as counting starts at 1 instead of 0
  if (fSelection && newRow != highlightedSelectionRow){
    fSelection->moveElement(highlightedSelectionRow-1, newRow-1);
    refreshSelectionTable();
    selectionTable->setCurrentCell( newRow-1, selectionTable->currentColumn() );
  }*/
}
//-------------------------------------------------------------------------------
void tTableModelView::on_RemoveButton_clicked(void)
{/*
  if (fSelection){
    fSelection->removeElement(highlightedSelectionRow-1);
  }*/
}
//-------------------------------------------------------------------------------
void tTableModelView::on_ReverseButton_clicked(void)
{/*
  if (fSelection){
    fSelection->reverse();
  }*/
}
//-------------------------------------------------------------------------------

/**Add a dummy to the selection list.
 */
void tTableModelView::addDummy(void)
{ /*
  if (fSelection){
    fSelection->append(new tDummy(NULL));
  }*/
}
//-------------------------------------------------------------------------------
