//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tQuad.h (Mo. Jan. 27 20:43:29 2014)
//------------------------------------------------------------------------

#ifndef IQUAD_H_
#define IQUAD_H_

#include "element/tElement.h"

class iQuad : public iElement
{
	public:
		iQuad(tElement *el);
		virtual ~iQuad();

		static tString theType(void) {return "Quad";}
		virtual tString type(void) const {return iQuad::theType();}

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
#endif /*IQUAD_H_*/
