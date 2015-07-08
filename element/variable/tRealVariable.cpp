/*
 * tRealVariable.cpp
 *
 *  Created on: 14.01.2009
 *      Author: Jochen
 */

#include "element/variable/tRealVariable.h"
#include "tRealOperator.h"

tRealVariable::tRealVariable(tVariableNameSpace *nameSpace, QString function)
: tVariable(nameSpace)
{
  fvalue = 0.;
  op = new tRealOperator(this);
  op->addDependent(this);
  setFullString(function);
}
//-----------------------------------------------------------------------------

tRealVariable::~tRealVariable()
{
  if (op){
    op->removeDependent(this);
  }
  op = NULL;
}
//-----------------------------------------------------------------------------

iElement* tRealVariable::intrface(void)
{
  if (iface == NULL){
    iface = new iRealVariable(this);
    //    iface->setPropertyString("name",fname);
  }
  return iface;
}
//-----------------------------------------------------------------------------

tOperator* tRealVariable::oper(void)
{
  return op;
}
//-----------------------------------------------------------------------------

void tRealVariable::refresh(void)
{
  if (op && op->type() == vtReal){
    fvalue = (dynamic_cast<tRealOperator*>(op))->value();
  } else {
    fvalue = 0.;
  }
}
//-----------------------------------------------------------------------------

tReal tRealVariable::value(void)
{
  update();
  return fvalue;
}
//-----------------------------------------------------------------------------

void tRealVariable::setValue(tReal value)
{
  op->setValue(value);
  invalidate(this);
}
//-----------------------------------------------------------------------------

void tRealVariable::setRHS(QString rhs)
{
  //  if (op){
  //  	op->removeDependent(this);
  //  	op->releaseOwner(this);
  //  }
  //  op = new tRealOperator(this);
  //  op->addDependent(this);
  op->init(rhs, fnameSpace);
  invalidate(this);
}
//-----------------------------------------------------------------------------
