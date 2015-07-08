//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IFUNCTIONPOINT_H_
#define IFUNCTIONPOINT_H_

#include "element/point/tDot.h"

class iFunctionPoint : public iDot
{
	public:
		iFunctionPoint(tElement *el);
		virtual ~iFunctionPoint();

		static tString theType(void) {return "FunctionPoint";}
		virtual tString type(void) const {return iFunctionPoint::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDot::nProperties()+4;}
		int nInheritedProperties(void) {return iDot::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IFUNCTIONPOINT_H_*/
