//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSurface.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISURFACE_H_
#define ISURFACE_H_

#include "element/tElement.h"

class iSurface : public iElement
{
	public:
		iSurface(tElement *el);
		virtual ~iSurface();

		static tString theType(void) {return "Surface";}
		virtual tString type(void) const {return iSurface::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+6;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISURFACE_H_*/
