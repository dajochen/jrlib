#ifndef TINTEDITOR_H
#define TINTEDITOR_H

#include <QWidget>

namespace Ui {
class tIntEditor;
}

class tIntEditor : public QWidget
{
    Q_OBJECT

public:
    explicit tIntEditor(QString property, int value, QWidget *parent = 0);
    virtual ~tIntEditor();

    int value(void);

signals:
    void valueChanged(void);

protected:
    int fValue;
    QPalette OkPal,WrongPal;

protected slots:
    void on_value_editingFinished(void);


private:
    Ui::tIntEditor *ui;
};

#endif // TINTEDITOR_H
