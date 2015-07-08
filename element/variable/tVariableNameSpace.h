/*
 * tVariableNameSpace.h
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#ifndef TVARIABLENAMESPACE_H_
#define TVARIABLENAMESPACE_H_

#include <QString>
#include "element/tElement.h"
#include "tVariable.h"
#include "iVariableNameSpace.h"

class tVariable;

class tVariableNameSpace : public tElement {
	tVariableNameSpace *inherits;
	tList<tVariable*> varList;

public:
	tVariableNameSpace(void *theowner);
	virtual ~tVariableNameSpace();

	virtual void refresh(void);
	iElement* intrface(void);

	tVariable* addRealVariable(QString function);
	tVariable* addVectorVariable(QString function);
	tVariable* addListVariable(QString function);
	tVariable* addVariable(QString function);

	bool contains(QString varName);

	int count(void){return varList.count();};

	tVariable* variable(QString varName);
	tVariable* variable(int count) {if (count<varList.count() && count>=0){return varList.at(count);} else {return NULL;}};
	tReal getRealVarValue(QString varName);
	tVector getVectorVarValue(QString varName);
	void clear(void);
	void removeVariable(tVariable *var);
	void inheritNameSpace(tVariableNameSpace *i);
};
/*I!
count Int read:count
*/

#endif /* TVARIABLENAMESPACE_H_ */
