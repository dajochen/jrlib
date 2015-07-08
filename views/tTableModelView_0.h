#ifndef TTABLEMODELVIEW_H_
#define TTABLEMODELVIEW_H_

#include "ui_TableModelView.h"
#include <QtGui>
#include "views/tModelView.h"
#include "tAvailableTypesViewer.h"
#include "model/tSelectionSet.h"


enum tmvSelectionMode{tmvSingleSelection, tmvMultipleSelection, tmvEnhancedSelection};

class tTableModelView : public QWidget, public tModelView, private Ui::ElementView {
/**
 * \brief Allow the user to select elements in a tModel.
 *
 * Elements in a model can be marked as selected, which is be done by selection the displayed elements in the table. The class can also
 * be used to chose one or more elements without selcting them in the model, but adding them to a seperate tGroup. This is done by calling
 * setModelSelectionUsage(false). In this case an own tGroup-element is created, which can be accessed by calling selection().
 *
 * Some restriction to the displayed elements can be set. setTypeFilter() allows only certain element types to be displayed. The user may
 * also select whether only visible elements shall be displayed or may specify the desired element type. Elements can also be found by their
 * names.
 */
Q_OBJECT

private:
  tList<tElement*> fSelectablesList;
  tAvailableTypesViewer* fAvailableTypes;

  tmvSelectionMode fselectionMode;
  int highlightedSelectionRow;


  //const bool fuseModelSelection;    // if useModelSelection ist true (default) the models selectionList is used,
  //tGroup* fSelection;               // otherwise the selection modifies the local fSelection
  //tGroup *setModelSelectionUsage(void) const;

  QHash<tLayer*,bool> isExpanded; // indicates weather a Layer is shown expanded or collapsed.

  virtual void addLayerToTreeWidget(tLayer *l, QTreeWidgetItem *parentItem=NULL);
  virtual void addLayerToTable(tLayer *G, const QString& firstSyllable, int &lastRow);
  virtual void refreshTable(void);
  virtual void refreshSelectionTable(void);
  virtual void refreshLayers(void);

protected:
  virtual void refresh(void);
  virtual void paintEvent(QPaintEvent * event);

  void setSelectionMode(tmvSelectionMode selectionMode);

public:
  tTableModelView(QWidget *parent = NULL, tModel* m=NULL,
                  tmvSelectionMode selectionMode=tmvMultipleSelection,
                  bool useOwnSelectionGroup=false,
                  bool showSelectionSummary=false);
  virtual ~tTableModelView();

  virtual void setModel(tModel *theModel);
  //virtual tGroup* selection(void) {return fSelection;} // return NULL is models selection is active


  tAvailableTypesViewer* availableTypes(void){return fAvailableTypes;}

public slots:
  virtual void invalidate(tElement *sender=NULL);
  virtual void repaintElement(void);
  void setLayerVisibility(QTreeWidgetItem *item);
  void currentLayerChanged(QTreeWidgetItem *current);
  void setSelection(void);
  void setSelectionArrangementSpinBox(int row);
  void extendSelection(QTableWidgetItem *item=NULL);
  void addDummy(void);

  void on_clearSelectionButton_clicked(void);
  void on_selectionSpinBox_valueChanged(int);
  void on_RemoveButton_clicked(void);
  void on_ReverseButton_clicked(void);

};

#endif /*TTABLEMODELVIEW_H_*/
