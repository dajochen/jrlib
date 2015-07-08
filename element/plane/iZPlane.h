//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tZPlane.h (Di. Jan. 28 22:15:13 2014)
//------------------------------------------------------------------------

#ifndef IZPLANE_H_
#define IZPLANE_H_

#include "tBasicPlane.h"

class iZPlane : public iBasicPlane
{
	public:
		iZPlane(tElement *el);
		virtual ~iZPlane();

		static tString theType(void) {return "ZPlane";}
		virtual tString type(void) const {return iZPlane::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iBasicPlane::nProperties()+1;}
		int nInheritedProperties(void) {return iBasicPlane::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IZPLANE_H_*/
