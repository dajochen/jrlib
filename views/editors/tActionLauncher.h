#ifndef TACTIONLAUNCHER_H
#define TACTIONLAUNCHER_H

#include <QWidget>

namespace Ui {
class tActionLauncher;
}

class tActionLauncher : public QWidget
{
    Q_OBJECT

public:
    explicit tActionLauncher(QString label, QWidget *parent=0);
    virtual ~tActionLauncher();



signals:
    void actionTriggered(void);

protected slots:
    void on_button_clicked();

private:
    Ui::tActionLauncher *ui;
};

#endif // TACTIONLAUNCHER_H
