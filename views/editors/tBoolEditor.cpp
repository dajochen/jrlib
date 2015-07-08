#include "tBoolEditor.h"
#include "ui_tBoolEditor.h"

tBoolEditor::tBoolEditor(QString property, double value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tBoolEditor)
{
    ui->setupUi(this);
    ui->property->setText(property);
    if (value) {
        ui->value->setCurrentIndex(0);
    } else {
        ui->value->setCurrentIndex(1);
    }
}

tBoolEditor::~tBoolEditor()
{
    delete ui;
}

bool tBoolEditor::value()
{
    if (ui->value->currentIndex() == 0){
        return true;
    } else {
        return false;
    }
}

void tBoolEditor::on_value_currentIndexChanged(int)
{
    emit valueChanged();
}


