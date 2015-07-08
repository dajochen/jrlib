//------------------------------------------------------------------------
//Automically generated interface class
//generated from tStructured2DInterpolGrid.h (Mo. Mär 5 07:46:10 2012)
//------------------------------------------------------------------------
#ifndef ISTRUCTURED2DINTERPOLGRID_H_
#define ISTRUCTURED2DINTERPOLGRID_H_

#include "iStructured2DGrid.h"

class iStructured2DInterpolGrid : public iStructured2DGrid
{
	public:
		iStructured2DInterpolGrid(tElement *el);
		virtual ~iStructured2DInterpolGrid();

		static tString theType(void) {return "Structured2DInterpolGrid";};
		virtual tString type(void) const {return iStructured2DInterpolGrid::theType();};

		virtual tString getPropertyName(unsigned int index);
		virtual tString getPropertyType(unsigned int index);
		virtual bool getPropertyValue(unsigned int index, tString type, void* value);
		virtual bool isReadOnly(unsigned int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual unsigned int nProperties(void) {return iStructured2DGrid::nProperties()+3;};
		unsigned int nInheritedProperties(void) {return iStructured2DGrid::nProperties();};
		virtual bool setPropertyValue(unsigned int index, tString type, void* value);
};
#endif /*ISTRUCTURED2DINTERPOLGRID_H_*/
