//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tXPlane.h (Di. Jan. 28 21:50:56 2014)
//------------------------------------------------------------------------

#ifndef IXPLANE_H_
#define IXPLANE_H_

#include "tBasicPlane.h"

class iXPlane : public iBasicPlane
{
	public:
		iXPlane(tElement *el);
		virtual ~iXPlane();

		static tString theType(void) {return "XPlane";}
		virtual tString type(void) const {return iXPlane::theType();}

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
#endif /*IXPLANE_H_*/
