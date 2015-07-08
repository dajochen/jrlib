/*
 * tListVariable.cpp
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#include "element/variable/tListVariable.h"

tListVariable::tListVariable(tVariableNameSpace *nameSpace, QString function)
	: tVariable(nameSpace)
{
	op = new tListOperator(this);
	op->addDependent(this);
  setFullString(function);
}
//-----------------------------------------------------------------------------

tListVariable::~tListVariable()
{
	if (op){
		op->removeDependent(this);
	}
	op->releaseOwner(this);
	op = NULL;
}
//-----------------------------------------------------------------------------

void tListVariable::refresh(void)
{

}
//-----------------------------------------------------------------------------

iElement* tListVariable::intrface(void)
{
  if (iface == NULL){
    iface = new iListVariable(this);
//    iface->setPropertyString("name",fname);
  }
  return iface;
}
//-----------------------------------------------------------------------------

tOperator* tListVariable::oper(void)
{
	return op;
}
//-----------------------------------------------------------------------------

bool tListVariable::isRealOnly(void)
{
	return op->isRealOnly();
}
//-----------------------------------------------------------------------------
tReal tListVariable::minimum(void)
{
	return op->minimum();
}
//-----------------------------------------------------------------------------

tReal tListVariable::maximum(void)
{
	return op->maximum();
}
//-----------------------------------------------------------------------------

void tListVariable::setRHS(QString rhs)
{
  if (op){
  	op->removeDependent(this);
  	op->releaseOwner(this);
  }
  op = new tListOperator(this);
  op->addDependent(this);
  op->init(rhs, fnameSpace);
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tListVariable::appendItem(QString itemName)
{
	op->appendItem(itemName, fnameSpace);
}
