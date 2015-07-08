//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRealVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IREALVARIABLE_H_
#define IREALVARIABLE_H_

#include "tVariable.h"

class iRealVariable : public iVariable
{
	public:
		iRealVariable(tElement *el);
		virtual ~iRealVariable();

		static tString theType(void) {return "RealVariable";}
		virtual tString type(void) const {return iRealVariable::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iVariable::nProperties()+1;}
		int nInheritedProperties(void) {return iVariable::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IREALVARIABLE_H_*/
