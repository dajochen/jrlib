//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tVectorVariable.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IVECTORVARIABLE_H_
#define IVECTORVARIABLE_H_

#include "tVariable.h"

class iVectorVariable : public iVariable
{
	public:
		iVectorVariable(tElement *el);
		virtual ~iVectorVariable();

		static tString theType(void) {return "VectorVariable";}
		virtual tString type(void) const {return iVectorVariable::theType();}

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
#endif /*IVECTORVARIABLE_H_*/
