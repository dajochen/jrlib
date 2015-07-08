/*
 * tVectorVariable.cpp
 *
 *  Created on: 14.01.2009
 *      Author: Jochen
 */

#include "element/variable/tVectorVariable.h"
#include "tVectorOperator.h"

tVectorVariable::tVectorVariable(tVariableNameSpace *nameSpace, QString function)
	: tVariable(nameSpace)
{
	fvalue.setZero();
//  op = NULL;
  op = new tVectorOperator(this);
	op->addDependent(this);
  setFullString(function);
}
//-----------------------------------------------------------------------------

tVectorVariable::~tVectorVariable() {
	if (op){
		op->removeDependent(this);
	}
	op = NULL;
}
//-----------------------------------------------------------------------------

tOperator* tVectorVariable::oper(void)
{
	return op;
}
//-----------------------------------------------------------------------------

void tVectorVariable::refresh(void)
{
	if (op && op->type() == vtVector){
		fvalue = dynamic_cast<tVectorOperator*>(op)->value();
	} else {
		fvalue.setZero();
	}
}
//-----------------------------------------------------------------------------

iElement* tVectorVariable::intrface(void)
{
  if (iface == NULL){
    iface = new iVectorVariable(this);
//    iface->setPropertyString("name",fname);
  }
  return iface;
}
//-----------------------------------------------------------------------------

tVector tVectorVariable::value(void)
{
	update();
	return fvalue;
}
//-----------------------------------------------------------------------------

void tVectorVariable::setValue(tVector value)
{
  setElementLocked
	op->setValue(value);
}
//-----------------------------------------------------------------------------

void tVectorVariable::setRHS(QString rhs)
{
  setElementLocked
//  if (op){
//  	op->removeDependent(this);
//  	op->releaseOwner(this);
//  }
//  op = new tVectorOperator(this);
//  op->addDependent(this);
  op->init(rhs, fnameSpace);
  invalidate(this);
}
//-----------------------------------------------------------------------------

