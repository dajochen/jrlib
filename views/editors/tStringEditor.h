#ifndef TSTRINGEDITOR_H
#define TSTRINGEDITOR_H

#include <QWidget>

namespace Ui {
class tStringEditor;
}

class tStringEditor : public QWidget
{
    Q_OBJECT

public:
    explicit tStringEditor(QString property, QString value, QWidget *parent = 0);
    virtual ~tStringEditor();

    QString value(void);

signals:
    void valueChanged(void);

protected slots:
    void on_value_editingFinished(void);

private:
    Ui::tStringEditor *ui;
};

#endif // TSTRINGEDITOR_H
