//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured2DInterpolGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED2DINTERPOLGRID_H_
#define ISTRUCTURED2DINTERPOLGRID_H_

#include "element/misc/2DGrid/tStructured2DGrid.h"

class iStructured2DInterpolGrid : public iStructured2DGrid
{
	public:
		iStructured2DInterpolGrid(tElement *el);
		virtual ~iStructured2DInterpolGrid();

		static tString theType(void) {return "Structured2DInterpolGrid";}
		virtual tString type(void) const {return iStructured2DInterpolGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructured2DGrid::nProperties()+3;}
		int nInheritedProperties(void) {return iStructured2DGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED2DINTERPOLGRID_H_*/
