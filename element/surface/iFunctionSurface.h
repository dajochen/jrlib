//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tFunctionSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IFUNCTIONSURFACE_H_
#define IFUNCTIONSURFACE_H_

#include "element/surface/tSurface.h"

class iFunctionSurface : public iSurface
{
	public:
		iFunctionSurface(tElement *el);
		virtual ~iFunctionSurface();

		static tString theType(void) {return "FunctionSurface";}
		virtual tString type(void) const {return iFunctionSurface::theType();}

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
#endif /*IFUNCTIONSURFACE_H_*/
