//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLine.h (Mo. Okt. 13 22:34:44 2014)
//------------------------------------------------------------------------

#ifndef ILINE_H_
#define ILINE_H_

#include "element/curve/tCurve.h"

class iLine : public iCurve
{
	public:
		iLine(tElement *el);
		virtual ~iLine();

		static tString theType(void) {return "Line";}
		virtual tString type(void) const {return iLine::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+2;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ILINE_H_*/
