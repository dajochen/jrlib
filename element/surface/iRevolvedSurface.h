//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRevolvedSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IREVOLVEDSURFACE_H_
#define IREVOLVEDSURFACE_H_

#include "element/surface/tSurface.h"

class iRevolvedSurface : public iSurface
{
	public:
		iRevolvedSurface(tElement *el);
		virtual ~iRevolvedSurface();

		static tString theType(void) {return "RevolvedSurface";}
		virtual tString type(void) const {return iRevolvedSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+4;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IREVOLVEDSURFACE_H_*/
