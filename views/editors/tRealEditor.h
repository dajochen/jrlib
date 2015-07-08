#ifndef TREALEDITOR_H
#define TREALEDITOR_H

#include <QWidget>

namespace Ui {
class tRealEditor;
}

class tRealEditor : public QWidget
{
    Q_OBJECT

public:
    explicit tRealEditor(QString property, double value, QWidget *parent = 0);
    virtual ~tRealEditor();

    double value(void);

signals:
    void valueChanged(void);

protected:
    double fValue;
    QPalette OkPal,WrongPal;

protected slots:
    void on_value_editingFinished(void);


private:
    Ui::tRealEditor *ui;
};

#endif // TINTEDITOR_H
