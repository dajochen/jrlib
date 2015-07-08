#ifndef TELEMENTCREATOR_H
#define TELEMENTCREATOR_H

#include "ui_tElementCreator.h"

#include "model/tModel.h"
#include "views/tModelView.h"

class tElementCreator : public QWidget, protected Ui::tElementCreatorClass, public tModelView
{
    Q_OBJECT

public:
    tElementCreator(void* theOwner, QWidget *parent /*= 0*/);
    ~tElementCreator();


protected:
    virtual void refresh( void ) {}
private:

private slots:
    void createElement(QTreeWidgetItem * item, int );
};

#endif // TELEMENTCREATOR_H
