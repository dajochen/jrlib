//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tStructured3DTwoSidedGrid.h (Di. Nov. 5 21:48:35 2013)
//------------------------------------------------------------------------

#ifndef ISTRUCTURED3DTWOSIDEDGRID_H_
#define ISTRUCTURED3DTWOSIDEDGRID_H_

#include "element/misc/3DGrid/tStructured3DGrid.h"

class iStructured3DTwoSidedGrid : public iStructured3DGrid
{
	public:
		iStructured3DTwoSidedGrid(tElement *el);
		virtual ~iStructured3DTwoSidedGrid();

		static tString theType(void) {return "Structured3DTwoSidedGrid";}
		virtual tString type(void) const {return iStructured3DTwoSidedGrid::theType();}

		virtual tString getPropertyName(int index);
		virtual tString getPropertyType(int index);
		virtual bool getPropertyValue(int index, tString type, void* value);
		virtual bool isReadOnly(int);
		virtual bool isOptional(QString propName);
		virtual bool isOfType(QString type);
		virtual QStringList inheritedTypes(void);
		virtual int nProperties(void) {return iStructured3DGrid::nProperties()+4;}
		int nInheritedProperties(void) {return iStructured3DGrid::nProperties();}
		virtual bool setPropertyValue(int index, tString type, void* value);

};
#endif /*ISTRUCTURED3DTWOSIDEDGRID_H_*/
