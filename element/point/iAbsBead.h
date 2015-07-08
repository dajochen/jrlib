//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbsBead.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IABSBEAD_H_
#define IABSBEAD_H_

#include "element/point/tDot.h"

class iAbsBead : public iDot
{
	public:
		iAbsBead(tElement *el);
		virtual ~iAbsBead();

		static tString theType(void) {return "AbsBead";}
		virtual tString type(void) const {return iAbsBead::theType();}

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
#endif /*IABSBEAD_H_*/
