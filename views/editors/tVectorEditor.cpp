#include "tVectorEditor.h"
#include "ui_tVectorEditor.h"

tVectorEditor::tVectorEditor(QString property, tVector value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tVectorEditor)
{
    ui->setupUi(this);
    ui->xValue->setText(QString::number(value.x));
    ui->yValue->setText(QString::number(value.y));
    ui->zValue->setText(QString::number(value.z));
    ui->property->setText(property);

    fValue = value;

    OkPal = ui->xValue->palette();
    WrongPal = OkPal;
    WrongPal.setColor(QPalette::Text, Qt::black);
    WrongPal.setColor(QPalette::Base, QColor(Qt::red).light(180));

}

tVectorEditor::~tVectorEditor()
{
    delete ui;
}

tVector tVectorEditor::value()
{
    return fValue;
}

void tVectorEditor::checkValues()
{
    bool okX, okY, okZ;
    double x = ui->xValue->text().toDouble(&okX);
    double y = ui->yValue->text().toDouble(&okY);
    double z = ui->zValue->text().toDouble(&okZ);
    if (okX && okY && okZ) {
        ui->xValue->setPalette(OkPal);
        ui->yValue->setPalette(OkPal);
        ui->zValue->setPalette(OkPal);
        fValue = tVector(x,y,z);
        emit valueChanged();
    } else {
        if (!okX)  ui->xValue->setPalette(WrongPal);
        if (!okY)  ui->yValue->setPalette(WrongPal);
        if (!okZ)  ui->zValue->setPalette(WrongPal);
    }
}

void tVectorEditor::on_xValue_editingFinished()
{
  checkValues();
}

void tVectorEditor::on_yValue_editingFinished()
{
  checkValues();
}

void tVectorEditor::on_zValue_editingFinished()
{
  checkValues();
}
