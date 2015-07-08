//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tAbstractPolygon.h (Di. Okt. 14 23:53:08 2014)
//------------------------------------------------------------------------

#ifndef IABSTRACTPOLYGON_H_
#define IABSTRACTPOLYGON_H_

#include "element/tPaintableElement.h"

class iAbstractPolygon : public iPaintableElement
{
	public:
		iAbstractPolygon(tElement *el);
		virtual ~iAbstractPolygon();

		static tString theType(void) {return "AbstractPolygon";}
		virtual tString type(void) const {return iAbstractPolygon::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iPaintableElement::nProperties()+4;}
		int nInheritedProperties(void) {return iPaintableElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IABSTRACTPOLYGON_H_*/
