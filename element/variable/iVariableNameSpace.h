//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVariableNameSpace.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IVARIABLENAMESPACE_H_
#define IVARIABLENAMESPACE_H_

#include "element/tElement.h"

class iVariableNameSpace : public iElement
{
	public:
		iVariableNameSpace(tElement *el);
		virtual ~iVariableNameSpace();

		static tString theType(void) {return "VariableNameSpace";}
		virtual tString type(void) const {return iVariableNameSpace::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+1;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IVARIABLENAMESPACE_H_*/
