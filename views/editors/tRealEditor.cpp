#include "tRealEditor.h"
#include "ui_tRealEditor.h"

tRealEditor::tRealEditor(QString property, double value, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tRealEditor)
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

tRealEditor::~tRealEditor()
{
    delete ui;
}

double tRealEditor::value()
{
    return fValue;
}

void tRealEditor::on_value_editingFinished()
{
    bool ok;
    double v = ui->value->text().toDouble(&ok);
    if (ok) {
        ui->value->setPalette(OkPal);
        fValue = v;
        emit valueChanged();
    } else {
        ui->value->setPalette(WrongPal);
    }
}
