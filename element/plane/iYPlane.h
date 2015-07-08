//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tYPlane.h (Di. Jan. 28 21:48:12 2014)
//------------------------------------------------------------------------

#ifndef IYPLANE_H_
#define IYPLANE_H_

#include "tBasicPlane.h"

class iYPlane : public iBasicPlane
{
	public:
		iYPlane(tElement *el);
		virtual ~iYPlane();

		static tString theType(void) {return "YPlane";}
		virtual tString type(void) const {return iYPlane::theType();}

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
#endif /*IYPLANE_H_*/
