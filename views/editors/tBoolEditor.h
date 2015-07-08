#ifndef TBOOLEDITOR_H
#define TBOOLEDITOR_H

#include <QWidget>

namespace Ui {
class tBoolEditor;
}

class tBoolEditor : public QWidget
{
    Q_OBJECT

public:
    explicit tBoolEditor(QString property, double value, QWidget *parent = 0);
    virtual ~tBoolEditor();

    bool value(void);

signals:
    void valueChanged(void);

protected:
    QPalette OkPal,WrongPal;

protected slots:
    void on_value_currentIndexChanged(int);


private:
    Ui::tBoolEditor *ui;
};

#endif // TINTEDITOR_H
