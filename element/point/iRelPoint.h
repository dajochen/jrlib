//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRelPoint.h (So. Jan. 26 23:45:49 2014)
//------------------------------------------------------------------------

#ifndef IRELPOINT_H_
#define IRELPOINT_H_

#include "element/point/tDot.h"

class iRelPoint : public iDot
{
	public:
		iRelPoint(tElement *el);
		virtual ~iRelPoint();

		static tString theType(void) {return "RelPoint";}
		virtual tString type(void) const {return iRelPoint::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iDot::nProperties()+2;}
		int nInheritedProperties(void) {return iDot::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IRELPOINT_H_*/
