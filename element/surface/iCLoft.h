//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCLoft.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ICLOFT_H_
#define ICLOFT_H_

#include "element/surface/tSurface.h"

class iCLoft : public iSurface
{
	public:
		iCLoft(tElement *el);
		virtual ~iCLoft();

		static tString theType(void) {return "CLoft";}
		virtual tString type(void) const {return iCLoft::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSurface::nProperties()+3;}
		int nInheritedProperties(void) {return iSurface::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ICLOFT_H_*/
