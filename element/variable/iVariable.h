//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IVARIABLE_H_
#define IVARIABLE_H_

#include "element/tElement.h"

class iVariable : public iElement
{
	public:
		iVariable(tElement *el);
		virtual ~iVariable();

		static tString theType(void) {return "Variable";}
		virtual tString type(void) const {return iVariable::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+4;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IVARIABLE_H_*/
