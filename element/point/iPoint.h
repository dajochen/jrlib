//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPoint.h (Mi. Nov. 20 21:35:49 2013)
//------------------------------------------------------------------------

#ifndef IPOINT_H_
#define IPOINT_H_

#include "element/point/tDot.h"

class iPoint : public iDot
{
	public:
		iPoint(tElement *el);
		virtual ~iPoint();

		static tString theType(void) {return "Point";}
		virtual tString type(void) const {return iPoint::theType();}

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
#endif /*IPOINT_H_*/
