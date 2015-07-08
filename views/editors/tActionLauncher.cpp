#include "tActionLauncher.h"
#include "ui_tActionLauncher.h"

tActionLauncher::tActionLauncher(QString label, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tActionLauncher)
{
    ui->setupUi(this);
    ui->label->setText(label);
}

tActionLauncher::~tActionLauncher()
{
    delete ui;
}

void tActionLauncher::on_button_clicked()
{
    emit actionTriggered();
}
