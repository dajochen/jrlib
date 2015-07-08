//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tSnake.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISNAKE_H_
#define ISNAKE_H_

#include "element/curve/tCurve.h"

class iSnake : public iCurve
{
	public:
		iSnake(tElement *el);
		virtual ~iSnake();

		static tString theType(void) {return "Snake";}
		virtual tString type(void) const {return iSnake::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iCurve::nProperties()+1;}
		int nInheritedProperties(void) {return iCurve::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISNAKE_H_*/
