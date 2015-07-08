//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tDot.h (So. Jan. 26 23:45:54 2014)
//------------------------------------------------------------------------

#ifndef IDOT_H_
#define IDOT_H_

#include "element/tElement.h"

class iDot : public iElement
{
	public:
		iDot(tElement *el);
		virtual ~iDot();

		static tString theType(void) {return "Dot";}
		virtual tString type(void) const {return iDot::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iElement::nProperties()+2;}
		int nInheritedProperties(void) {return iElement::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IDOT_H_*/
