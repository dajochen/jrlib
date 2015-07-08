#include "tIntEditor.h"
#include "ui_tIntEditor.h"

tIntEditor::tIntEditor(QString property, int value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tIntEditor)
{
    ui->setupUi(this);
    ui->value->setText(QString::number(value));
    ui->property->setText(property);

    fValue = value;

    OkPal = ui->value->palette();
    WrongPal = OkPal;
    WrongPal.setColor(QPalette::Text, Qt::black);
    WrongPal.setColor(QPalette::Base, QColor(Qt::red).light(180));

}

tIntEditor::~tIntEditor()
{
    delete ui;
}

int tIntEditor::value()
{
    return fValue;
}

void tIntEditor::on_value_editingFinished()
{
    bool ok;
    int v = ui->value->text().toInt(&ok);
    if (ok) {
        ui->value->setPalette(OkPal);
        fValue = v;
        emit valueChanged();
    } else {
        ui->value->setPalette(WrongPal);
    }
}
