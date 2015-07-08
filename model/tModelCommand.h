#ifndef TMODELCOMMAND_H_
#define TMODELCOMMAND_H_

#include <QtCore>
#include "model/tModel.h"

class tModelCommand
{
private:
  tModel *model;
public:
	tModelCommand();
	virtual ~tModelCommand();

  void setModel(tModel *m){model=m;}
  QString execute(QStringList cmd);
  QString setProperty(tElement *el, QString property, QString value);
};
#endif /*TMODELCOMMAND_H_*/
