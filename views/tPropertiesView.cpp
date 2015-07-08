#include "tPropertiesView.h"
#include "ui_tPropertiesView.h"
#include "tVectorStringConverter.h"

tPropertiesView::tPropertiesView(void *theOwner, QWidget *parent) :
    QWidget(parent),
    tModelView(theOwner),
    ui(new Ui::tPropertiesView)
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

    connect(ui->tableWidget, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)), this, SLOT(selectedItemChanged(QTableWidgetItem*,QTableWidgetItem*)));

    keepPropertyTable = false;
}

tPropertiesView::~tPropertiesView()
{
    delete ui;
}

QString tPropertiesView::selectedProperty()
{
    int index = ui->tableWidget->currentRow();
    if (index >=0) {
        return ui->tableWidget->item(index, 0)->text();
    } else {
        return "";
    }
}

QString tPropertiesView::selectedPropertyType()
{
    int index = ui->tableWidget->currentRow();
    if (index >=0) {
        return ui->tableWidget->item(index, 1)->text();
    } else {
        return "";
    }
}

void tPropertiesView::invalidate(tElement *sender)
{
    tElement::invalidate(sender);
    QWidget::update();
}

void tPropertiesView::refresh()
{
    if ( !keepPropertyTable ) {
        QStringList propNames,
                    propTypes,
                    actionNames;
        QString selProperty = selectedProperty();

        ui->tableWidget->blockSignals(true);
        ui->tableWidget->clearContents();


        tElement* el = NULL;

        if (activeSelectionSet()) {
            //take first element as basis
            if (activeSelectionSet()->nElements()>0){
                el = activeSelectionSet()->element(0);

                propNames = el->intrface()->getPropertyNames();
                propTypes = el->intrface()->getPropertyTypes();
                actionNames = el->intrface()->getActionNames();
            }

            // compare other selection and remove props / action with other names/propTypes
            for (int i=0; i<activeSelectionSet()->nElements(); i++){
                tElement *el1 = activeSelectionSet()->element(i);

                for (int j=0; j<propNames.count() && j<propTypes.count(); j++){
                    if (el1->intrface()->getPropertyType( el1->intrface()->getPropertyIndex( propNames[j] )) != propTypes[j]){
                        propNames.removeAt(j);
                        propTypes.removeAt(j);
                        j--;
                    }
                }
                for (int j=0; j<actionNames.count(); j++){
                    if (el1->intrface()->getActionName(j) != actionNames[j]){
                        propNames.removeAt(j);
                        propTypes.removeAt(j);
                        actionNames.removeAt(j);
                        j--;
                    }
                }
            }

        }
        int propCount = std::min(propNames.count(), propTypes.count()),
            actionCount = actionNames.count();

        ui->tableWidget->setRowCount(propCount + actionCount);
        ui->tableWidget->setColumnCount(3);

        for (int i=0; i<propCount && el; i++){

            QString type = propTypes[i];
            QString propertyValue;

            QTableWidgetItem *nameItem, *typeItem, *valueItem;

            nameItem  = new QTableWidgetItem(propNames[i]);
            typeItem  = new QTableWidgetItem(propTypes[i]);
            valueItem = new QTableWidgetItem("Type not implemented");

            if (el->intrface()->isReadOnly(i)) {
                QBrush fgBrush = nameItem->foreground();
                fgBrush.setColor(Qt::darkGray);
                QColor bgColor = QColor(242,241,240);
                nameItem->setForeground(fgBrush);
                nameItem->setBackgroundColor(bgColor);
                typeItem->setForeground(fgBrush);
                typeItem->setBackgroundColor(bgColor);
                valueItem->setForeground(fgBrush);
                valueItem->setBackgroundColor(bgColor);
            }

            ui->tableWidget->setItem(i, 0, nameItem);
            ui->tableWidget->setItem(i, 1, typeItem);
            ui->tableWidget->setItem(i, 2, valueItem);




            if (type == "String"){
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &propertyValue);
            } else if (type == "Int"){
                int value;
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                propertyValue = QString::number(value);
            } else if (type == "Real") {
                double value;
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                propertyValue = QString::number(value);
            } else if (type == "Bool") {
                bool value;
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                if (value) {
                    propertyValue = "True";
                } else {
                    propertyValue = "False";
                }
            } else if (type == "Vector") {
                tVector value;
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                propertyValue = tVectorStringConverter::toString(value,";");
            } else if (type == "RGB") {
                tRGB value;
                el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                propertyValue = tVectorStringConverter::toString(value.toVector(),";");


            } else if (type.endsWith("List")) {

                if (type.startsWith("String")){
                    QStringList value;
                    el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                    propertyValue = value.join(";");

                } else if (type.startsWith("Int")){
                    tList<int> value;
                    el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                    for (int j=0; j<value.count(); j++){
                        propertyValue += QString::number(value.at(j)) + ";";
                    }
                } else if (type.startsWith("Real")) {
                    tList<double> value;
                    el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                    for (int j=0; j<value.count(); j++){
                        propertyValue += QString::number(value.at(j)) + ";";
                    }
                } else if (type.startsWith("Bool")) {
                    tList<bool> value;
                    el->intrface()->getPropertyValue(propNames[i],propTypes[i], &value);
                    for (int j=0; j<value.count(); j++){
                        if (value.at(j)) {
                            propertyValue += "True";
                        } else {
                            propertyValue += "False";
                        }
                        propertyValue +=";";
                    }
                } else {
                    tList<tElement*> value;
                    if (el->intrface()->getPropertyValue(propNames[i], propTypes[i], &value)){
                        if (value.count()>0){
                          for (int j=0; j<value.count(); j++){
                            tElement *item = value.at(j);
                            if (item) {
                              propertyValue.append(item->intrface()->name()+";");
                            } else {
                              propertyValue.append(";");
                            }
                          }
                        }
                    } else {
                        propertyValue = "Type not implemented!";
                    }
                }
            } else {
                tElement *value=NULL;
                if (el->intrface()->getPropertyValue(propNames[i], "Element", &value)) {
                    if (value) {
                        propertyValue = value->intrface()->name();
                    } else {
                        propertyValue = "None";
                    }
                } else {
                    propertyValue = "Type not implemented!";
                }
            }

            valueItem->setText(propertyValue);

            if (propNames[i] == selProperty) {
                ui->tableWidget->setCurrentCell(i,0);
            }
        }

        for (int i=0; i<actionCount && el; i++){

            QTableWidgetItem *nameItem, *typeItem;

            nameItem  = new QTableWidgetItem(actionNames[i]);
            typeItem  = new QTableWidgetItem("Action");

            ui->tableWidget->setItem(propCount + i, 0, nameItem);
            ui->tableWidget->setItem(propCount + i, 1, typeItem);
        }



        ui->tableWidget->blockSignals(false);
    }

    keepPropertyTable = false;
}

void tPropertiesView::paintEvent(QPaintEvent *event)
{
    tElement::update();
    QWidget::paintEvent(event);
}

void tPropertiesView::selectedItemChanged(QTableWidgetItem*, QTableWidgetItem*)
{
    keepPropertyTable = true;
    invalidate(this);
}
