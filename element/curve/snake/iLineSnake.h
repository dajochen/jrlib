//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLineSnake.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ILINESNAKE_H_
#define ILINESNAKE_H_

#include "element/curve/snake/tSnake.h"

class iLineSnake : public iSnake
{
	public:
		iLineSnake(tElement *el);
		virtual ~iLineSnake();

		static tString theType(void) {return "LineSnake";}
		virtual tString type(void) const {return iLineSnake::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iSnake::nProperties()+2;}
		int nInheritedProperties(void) {return iSnake::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ILINESNAKE_H_*/
