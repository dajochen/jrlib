//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tPlane.h (Mo. Jan. 27 23:16:24 2014)
//------------------------------------------------------------------------

#ifndef IPLANE_H_
#define IPLANE_H_

#include "tBasicPlane.h"

class iPlane : public iBasicPlane
{
	public:
		iPlane(tElement *el);
		virtual ~iPlane();

		static tString theType(void) {return "Plane";}
		virtual tString type(void) const {return iPlane::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iBasicPlane::nProperties()+4;}
		int nInheritedProperties(void) {return iBasicPlane::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IPLANE_H_*/
