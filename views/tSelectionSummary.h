#ifndef TSELECTIONSUMMARY_H
#define TSELECTIONSUMMARY_H

#include <QWidget>
#include <QListWidgetItem>
#include <views/tModelView.h>
namespace Ui {
class tSelectionSummary;
}

class tSelectionSummary : public QWidget, public tModelView
{
    Q_OBJECT

public:
    explicit tSelectionSummary(void* theOwner, QWidget *parent /*= 0*/);
    virtual ~tSelectionSummary();

protected:
    virtual void invalidate(tElement *sender);
    virtual void refresh(void);
    virtual void paintEvent(QPaintEvent * event);

    QHash<QListWidgetItem*, tElement*> itemHash;

protected slots:
    void on_removeButton_clicked(void);
    void on_clearButton_clicked(void);
    void on_reverseButton_clicked(void);

    void on_listWidget_currentRowChanged(int currentRow);
    void positionSpinBox_valueChanged(int i);


private:
    Ui::tSelectionSummary *ui;
};

#endif // TSELECTIONSUMMARY_H
