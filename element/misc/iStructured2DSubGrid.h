//------------------------------------------------------------------------
//Automically generated interface class
//generated from tStructured2DSubGrid.h (Mo. Mär 5 07:46:10 2012)
//------------------------------------------------------------------------
#ifndef ISTRUCTURED2DSUBGRID_H_
#define ISTRUCTURED2DSUBGRID_H_

#include "iStructured2DGrid.h"

class iStructured2DSubGrid : public iStructured2DGrid
{
	public:
		iStructured2DSubGrid(tElement *el);
		virtual ~iStructured2DSubGrid();

		static tString theType(void) {return "Structured2DSubGrid";};
		virtual tString type(void) const {return iStructured2DSubGrid::theType();};

		virtual tString getPropertyName(unsigned int index);
		virtual tString getPropertyType(unsigned int index);
		virtual bool getPropertyValue(unsigned int index, tString type, void* value);
		virtual bool isReadOnly(unsigned int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual unsigned int nProperties(void) {return iStructured2DGrid::nProperties()+7;};
		unsigned int nInheritedProperties(void) {return iStructured2DGrid::nProperties();};
		virtual bool setPropertyValue(unsigned int index, tString type, void* value);
};
#endif /*ISTRUCTURED2DSUBGRID_H_*/
