/*
 * tListOperator.cpp
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#include "tListOperator.h"
#include "element/variable/tRealVariable.h"
#include <QStringList>
#include "classes/utils.h"

tListOperator::tListOperator(tElement *theowner)
: tOperator(theowner)
{
	variable = NULL;
	opType = lotIsList;
	localNS = new tVariableNameSpace(this);
}
//-----------------------------------------------------------------------------

tListOperator::~tListOperator() {
  clear();
  localNS->releaseOwner(this);
}
//-----------------------------------------------------------------------------

iElement* tListOperator::intrface(void)
{
  if (iface == NULL){
    iface = new iListOperator(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tListOperator::clear(void)
{
  int i;
  for (i=0;i<element.count();i++){
  	element.at(i)->removeDependent(this);
  }
  element.clear();
  if (variable){
  	variable->removeDependent(this);
  	variable = NULL;
  }
  localNS->clear();
  localNS->inheritNameSpace(NULL);
  invalidate(this);
}
//-----------------------------------------------------------------------------

bool tListOperator::isRealOnly(void)
{
	int i;
	bool isReal = true;
	if (opType == lotIsVariable){
		if (variable){
			return variable->isRealOnly();
		} else {
			return false;
		}
	} else if (opType == lotIsList) {
		for (i=0;i<element.count();i++){
			if (dynamic_cast<tRealVariable*>(element.at(i)) == NULL){
				isReal = false;
			}
		}
		return isReal;
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

void tListOperator::appendItem(QString itemName, tVariableNameSpace* nameSpace)
{

	if (opType==lotIsList){
		tVariable *var;
		var = nameSpace->variable(itemName);
		if (!var){
			var = localNS->addVariable("__item" + QString::number(element.count()) + "=" + itemName);
		}
		element.append(var);
		var->addDependent(this);
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tListOperator::refresh(void)
{

}
//-----------------------------------------------------------------------------

void tListOperator::init(QString term, tVariableNameSpace* nameSpace)
{
	QStringList argString;
	int pos;

	clear();
	localNS->inheritNameSpace(nameSpace);

	// Die Operatoren in Gruppen aufteilen

	opType = lotInvalid;

	if(nameSpace->contains(term)){
		// Hinter dem String verbirgt sich eine Variable
		variable = dynamic_cast<tListVariable*>(nameSpace->variable(term));
		if (variable && variable->addDependent(this)){
			opType = lotIsVariable;
		} else {
			variable = NULL;
			opType = lotInvalid;
		}
	}	else if (term.endsWith('}') && term.startsWith('{')) {
		opType = lotIsList;
		term.remove(term.length()-1,1);
		term.remove(0,1);
		do {
			pos=firstOccurence(QStringList() << ";",term);
			if (pos>=0){
				argString.prepend(term.right(term.length()-pos-1));
				term.remove(pos,term.length());
			} else if (term.length()){
				argString.prepend(term);
			}
		} while (pos > 0);

		int i;
		for (i=0;i<argString.count();i++){
			tVariable *var;
			var = nameSpace->variable(argString.at(i));
			if (!var){
				var = localNS->addVariable("__item" + QString::number(element.count()) + "=" + argString.at(i));
			}
			element.append(var);
			var->addDependent(this);
		}
	} else {
		opType = lotInvalid;
	}
	invalidate(this);

}
//-----------------------------------------------------------------------------

QString tListOperator::toString(void)
{
	QString term;

	if (opType == lotInvalid){
		term = "*error*";
	} else if (opType == lotIsList){
		int i;
		term = '{';
		for (i=0;i<element.count();i++){
			if (element.at(i)->name()=="__item"+QString::number(i)){
				term.append(element.at(i)->RHS());
			} else {
				term.append(element.at(i)->name());
			}
			if (i<element.count()-1){
				term.append(';');
			}
		}
		term.append('}');
	} else if (opType == lotIsVariable && variable){
		term = variable->name();
	} else {
		term = "*error*";
	}
	return term;
}
//-----------------------------------------------------------------------------

bool tListOperator::isValidOperator(void)
{
	if (opType == lotInvalid){
		return false;
	} else {
		return true;
	}
}
//-----------------------------------------------------------------------------

tReal tListOperator::minimum(void)
{
	tReal minV,v;
	int i;
	if (opType == lotIsVariable) {
		return variable->minimum();
	} else if (opType == lotIsList && isRealOnly() && element.count()>0){
		minV = dynamic_cast<tRealVariable*>(element.at(0))->value();
		for (i=1;i<element.count();i++){
			v = dynamic_cast<tRealVariable*>(element.at(i))->value();
			minV = min(minV,v);
		}
		return minV;
	} else {
		return 0.;
	}
}
//-----------------------------------------------------------------------------

tReal tListOperator::maximum(void)
{
	tReal maxV,v;
	int i;
	if (opType == lotIsVariable) {
		return variable->maximum();
	} else if (opType == lotIsList && isRealOnly() && element.count()>0){
		maxV = dynamic_cast<tRealVariable*>(element.at(0))->value();
		for (i=1;i<element.count();i++){
			v = dynamic_cast<tRealVariable*>(element.at(i))->value();
			maxV = max(maxV,v);
		}
		return maxV;
	} else {
		return 0.;
	}
}
//-----------------------------------------------------------------------------
