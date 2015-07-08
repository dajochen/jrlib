  //------------------------------------------------------------------------
//Automatically generated interface class
//generated from tUnifiedProperties.h (Di. Nov. 5 22:07:23 2013)
//------------------------------------------------------------------------

#ifndef IUNIFIEDPROPERTIES_H_
#define IUNIFIEDPROPERTIES_H_

#include "tElement.h"

class iUnifiedProperties : public iElement
{
	public:
		iUnifiedProperties(tElement *el);
		virtual ~iUnifiedProperties();

		static tString theType(void) {return "UnifiedProperties";}
		virtual tString type(void) const {return iUnifiedProperties::theType();}

        virtual tString getPropertyName(int index);
        virtual tString getPropertyType(int index);
        virtual bool getPropertyValue(int index, tString type, void* value);
        virtual bool isReadOnly(int index);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
        virtual int nProperties(void);// {return iElement::nProperties() +3;}
        int nInheritedProperties(void) {return iElement::nProperties();}
        virtual bool setPropertyValue(int index, tString type, void* value);


};
#endif /*IUNIFIEDPROPERTIES_H_*/
