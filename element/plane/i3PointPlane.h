//------------------------------------------------------------------------
//Automatically generated interface class
//generated from t3PointPlane.h (Di. Jan. 28 23:37:56 2014)
//------------------------------------------------------------------------

#ifndef I3POINTPLANE_H_
#define I3POINTPLANE_H_

#include "tBasicPlane.h"

class i3PointPlane : public iBasicPlane
{
	public:
		i3PointPlane(tElement *el);
		virtual ~i3PointPlane();

		static tString theType(void) {return "3PointPlane";}
		virtual tString type(void) const {return i3PointPlane::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iBasicPlane::nProperties()+3;}
		int nInheritedProperties(void) {return iBasicPlane::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);
};
#endif /*I3POINTPLANE_H_*/
