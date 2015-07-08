//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tOffsetPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IOFFSETPOINT_H_
#define IOFFSETPOINT_H_

#include "element/point/tDot.h"

class iOffsetPoint : public iDot
{
	public:
		iOffsetPoint(tElement *el);
		virtual ~iOffsetPoint();

		static tString theType(void) {return "OffsetPoint";}
		virtual tString type(void) const {return iOffsetPoint::theType();}

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
#endif /*IOFFSETPOINT_H_*/
