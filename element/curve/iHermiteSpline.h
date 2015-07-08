//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tHermiteSpline.h (Mi. Apr. 2 22:07:46 2014)
//------------------------------------------------------------------------

#ifndef IHERMITESPLINE_H_
#define IHERMITESPLINE_H_

#include "tAbstractSpline.h"

class iHermiteSpline : public iAbstractSpline
{
	public:
		iHermiteSpline(tElement *el);
		virtual ~iHermiteSpline();

		static tString theType(void) {return "HermiteSpline";}
		virtual tString type(void) const {return iHermiteSpline::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iAbstractSpline::nProperties()+3;}
		int nInheritedProperties(void) {return iAbstractSpline::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*IHERMITESPLINE_H_*/
