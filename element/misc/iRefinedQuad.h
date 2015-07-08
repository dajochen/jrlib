//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tRefinedQuad.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef IREFINEDQUAD_H_
#define IREFINEDQUAD_H_

#include "element/misc/tQuad.h"

class iRefinedQuad : public iQuad
{
	public:
		iRefinedQuad(tElement *el);
		virtual ~iRefinedQuad();

		static tString theType(void) {return "RefinedQuad";}
		virtual tString type(void) const {return iRefinedQuad::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iQuad::nProperties()+4;}
		int nInheritedProperties(void) {return iQuad::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IREFINEDQUAD_H_*/
