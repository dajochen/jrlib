class iElement {

%TypeHeaderCode
#include "iElement.h"
%End

public:
    iElement(tElement *el);
    virtual ~iElement();

    bool visibility();
    void setVisibility(bool value);

    tRGB color();
    void setColor(tRGB value);

    virtual QString name();
    void setName(QString value);

    static QString theType();
    virtual QString type() const;
    virtual QStringList inheritedTypes();
    virtual bool isOfType(const QString thetype);

    virtual unsigned int nProperties();
    unsigned int nInheritedProperties();

    virtual int getPropertyIndex(QString name);
    virtual QString getPropertyName(unsigned int index);
    virtual QString getPropertyType(unsigned int index);
    virtual bool isReadOnly(unsigned int index);
    virtual bool isOptional(QString name);
    virtual bool getPropertyValue(unsigned int index, QString type, void* value);
    int getPropertyInt (QString name);
    QString getPropertyString (QString name);
    bool getPropertyValue(QString name, QString type, void* value);

    virtual bool setPropertyValue(unsigned int index, QString type, void* value);
    bool setPropertyValue(QString name, QString type, void* value);
    bool setPropertyString(QString name, QString value);
    bool setPropertyInt(QString name, int value);   
};
   
   
//------------------------------------------------------------------

class tElement /Abstract/{
%TypeHeaderCode
#include "tElement.h"
%End
public:
    tElement(void *theOwner /TransferThis/);
    virtual ~tElement();

    virtual iElement* intrface();
};
//------------------------------------------------------------------



