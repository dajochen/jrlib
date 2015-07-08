#include "tStringEditor.h"
#include "ui_tStringEditor.h"

tStringEditor::tStringEditor(QString property, QString value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tStringEditor)
{
    ui->setupUi(this);
    ui->value->setText(value);
    ui->property->setText(property);
}

tStringEditor::~tStringEditor()
{
    delete ui;
}

void tStringEditor::on_value_editingFinished()
{
    emit valueChanged();
}


QString tStringEditor::value()
{
     return ui->value->text();
}
