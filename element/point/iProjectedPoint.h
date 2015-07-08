//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tProjectedPoint.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IPROJECTEDPOINT_H_
#define IPROJECTEDPOINT_H_

#include "element/point/tDot.h"

class iProjectedPoint : public iDot
{
	public:
		iProjectedPoint(tElement *el);
		virtual ~iProjectedPoint();

		static tString theType(void) {return "ProjectedPoint";}
		virtual tString type(void) const {return iProjectedPoint::theType();}

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
#endif /*IPROJECTEDPOINT_H_*/
