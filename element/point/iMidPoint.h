//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tMidPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IMIDPOINT_H_
#define IMIDPOINT_H_

#include "element/point/tDot.h"

class iMidPoint : public iDot
{
	public:
		iMidPoint(tElement *el);
		virtual ~iMidPoint();

		static tString theType(void) {return "MidPoint";}
		virtual tString type(void) const {return iMidPoint::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDot::nProperties()+1;}
		int nInheritedProperties(void) {return iDot::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IMIDPOINT_H_*/
