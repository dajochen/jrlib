#ifndef TMODELIO_H_
#define TMODELIO_H_

#include <QtXml>
#include "model/tModel.h"
#include "classes/tFunction.h"

class tVersion
{
private:
  int fbranch,frevision;
public:
  tVersion(QString ver){
    QStringList list= ver.split(".");
    if (list.count()>0){
      fbranch = list[0].toInt();
    } else {
      fbranch = 0;
    }
    if (list.count()>1){
      frevision = list[1].toInt();
    } else {
      frevision = 0;
    }
  }

  int branch(void) {return fbranch;}
  int revision(void) {return frevision;}
  QString versionString(void) {return QString::number(fbranch) + "." + QString::number(frevision);}

};
class tModelIO
{
private:
  tModel *model;
  QString currentFileName;
  QStringList fErrorMessages;
  tFunction funcs;

  tVector vectorize(QString str);
  tRGB colorize(QString str);
  QString resolveName(QString str);
protected:
  //writing functions:
  bool modelToXml(QDomElement m);
  void elementToXml(tElement *el, QDomDocument& doc, QDomElement& parentElement, QHash<tElement*, QString>& processedElements, QHash<QString, tElement*>& processedNames);
  //reading functions:
  bool executeXml(QDomElement m,QHash<QString,tElement*> *elName=NULL,QHash<QString,QDomElement> *macro=NULL);
  bool executeXml_2xx(QDomElement job, tVersion version);
  void executeFunctionSurfaceXml(tFunctionSurface *s, QDomElement el, QHash<QString,QDomElement> *macro);

public:
  tModelIO(tModel *m);
  virtual ~tModelIO();

  bool toXmlFile(QString fileName);
  bool fromXmlFile(QString fileName, QHash<QString,tElement*> *elName=NULL, QHash<QString,QDomElement> *macro=NULL);
  bool fromXmlElement(const QDomElement& el, QHash<QString,tElement*> *elName=NULL, QHash<QString,QDomElement> *macro=NULL);

  QStringList errorMessages(void){return fErrorMessages;}
  void clearErrorMessages(void){fErrorMessages.clear();}
};

#endif /*TMODELIO_H_*/
