#ifndef IELEMENT_H_
#define IELEMENT_H_

#include <QString>
#include <QStringList>
#include <QHash>

#include "classes/tVector.h"
#include "classes/tRGB.h"
#include "classes/jrTypes.h"

class tElement;

class iElement
{
  private:
    QString fname;
    tRGB fcolor;
    bool fvisibility;
    QHash<int, tElement*> linkedElement;
    QHash<int, QString> linkedProperty;
    bool linksLocked;

	protected:
    //bool isValid;
	  QString elementClassName;
	  tElement *element;


  public:
    static QStringList nonElementTypes(void){return QString("None|Bool|Int|Real|Vector|RGB|String").split("|");}
		iElement(tElement *el);
		virtual ~iElement();

    void invalidate(void);

    bool visibility(void);
    void setVisibility(bool value);

    tRGB color(void);
    void setColor(tRGB value);

    virtual tString name(void);
    void setName(QString value);

    static tString theType(void) {return "Element";}
    virtual tString type(void) const;
    virtual QStringList inheritedTypes(void);
    virtual bool isOfType(const QString thetype);

    virtual int nProperties(void) {return 6;}
    int nInheritedProperties(void) {return 0;}// must not be virtual

    virtual int getPropertyIndex(QString name);
    virtual QString getPropertyName(int index);
    virtual QString getPropertyType(int index);
    virtual QStringList getPropertyNames(void);
    virtual QStringList getPropertyTypes(void);
    virtual bool isReadOnly(int index);
    virtual bool isOptional(QString name);
    virtual bool getPropertyValue(int index, QString type, void* value);
    int getPropertyInt (QString name);
    QString getPropertyString (QString name);
    bool getPropertyValue(QString name, QString type, void* value);

    virtual bool setPropertyValue(int index, QString type, void* value);
    bool setPropertyValue(QString name, QString type, void* value);
    bool setPropertyString(QString name, QString value);
    bool setPropertyInt(QString name, int value);

    bool linkProperty(QString property, tElement* sender, QString senderProperty);
    void updateLinkedProperties(tElement *from);
    static void updateLinkedProperties(tElement*reveiver, tElement *from);
    //--------------------------------------------------------------------------------

    QStringList getActionNames();
    virtual int nActions(void) {return 0;}
    virtual int getActionIndex(QString name);
    virtual QString getActionName(int){ return "No Action";}
    virtual void runAction(int) {}
};


#endif /*IELEMENT_H_*/
