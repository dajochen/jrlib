//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tModel.h (So. Jan. 26 11:35:18 2014)
//------------------------------------------------------------------------

#ifndef IMODEL_H_
#define IMODEL_H_

#include "model/tLayer.h"

class iModel : public iLayer
{
	public:
		iModel(tElement *el):iLayer(el){}

		static tString theType(void) {return "Model";}
		virtual tString type(void) const {return iModel::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iModel::theType();
				return true;
			} else {
				return iLayer::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iLayer::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iLayer::isOfType(thetype);
			}
		}
};
#endif /*IMODEL_H_*/
