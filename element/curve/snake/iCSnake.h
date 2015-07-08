//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tCSnake.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ICSNAKE_H_
#define ICSNAKE_H_

#include "element/curve/snake/tSnake.h"

class iCSnake : public iSnake
{
	public:
		iCSnake(tElement *el);
		virtual ~iCSnake();

		static tString theType(void) {return "CSnake";}
		virtual tString type(void) const {return iCSnake::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSnake::nProperties()+1;}
		int nInheritedProperties(void) {return iSnake::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ICSNAKE_H_*/
