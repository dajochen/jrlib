//------------------------------------------------------------------------
//Automatically generated interface class
//generated from tLayer.h (Mo. Jan. 27 00:25:00 2014)
//------------------------------------------------------------------------

#ifndef ILAYER_H_
#define ILAYER_H_

#include "element/tGroup.h"

class iLayer : public iGroup
{
	public:
		iLayer(tElement *el):iGroup(el){}

		static tString theType(void) {return "Layer";}
		virtual tString type(void) const {return iLayer::theType();}

		virtual bool getPropertyValue(int index, tString propType, void* value){
			if (index == 0 && propType == "String"){
			*(tString*)value =iLayer::theType();
				return true;
			} else {
				return iGroup::getPropertyValue(index,propType,value);
			}
		}
		virtual QStringList inheritedTypes(void){
			return (iGroup::inheritedTypes() << theType());
		}
		virtual bool isOfType(QString thetype){
			if (theType() == thetype) {
				return true;
			} else {
				return iGroup::isOfType(thetype);
			}
		}
};
#endif /*ILAYER_H_*/
