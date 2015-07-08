//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRotatedPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IROTATEDPOINT_H_
#define IROTATEDPOINT_H_

#include "element/point/tDot.h"

class iRotatedPoint : public iDot
{
	public:
		iRotatedPoint(tElement *el);
		virtual ~iRotatedPoint();

		static tString theType(void) {return "RotatedPoint";}
		virtual tString type(void) const {return iRotatedPoint::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDot::nProperties()+3;}
		int nInheritedProperties(void) {return iDot::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IROTATEDPOINT_H_*/
