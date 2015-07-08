#ifndef TVECTOREDITOR_H
#define TVECTOREDITOR_H

#include <QWidget>
#include <tVector.h>

namespace Ui {
class tVectorEditor;
}

class tVectorEditor : public QWidget
{
    Q_OBJECT

public:
    explicit tVectorEditor(QString property, tVector value, QWidget *parent = 0);
    virtual ~tVectorEditor();

    tVector value(void);

signals:
    void valueChanged(void);

protected:
    tVector fValue;
    QPalette OkPal,WrongPal;
    void checkValues(void);

protected slots:
    void on_xValue_editingFinished(void);
    void on_yValue_editingFinished(void);
    void on_zValue_editingFinished(void);


private:
    Ui::tVectorEditor *ui;
};

#endif // TINTEDITOR_H
