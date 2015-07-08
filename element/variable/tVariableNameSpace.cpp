/*
 * tVariableNameSpace.cpp
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#include "element/variable/tVariableNameSpace.h"

#include "element/variable/tRealVariable.h"
#include "element/variable/tVectorVariable.h"
#include "element/variable/tListVariable.h"

tVariableNameSpace::tVariableNameSpace(void *theowner) : tElement(theowner)
{
  inherits = NULL;
}
//-----------------------------------------------------------------------------

tVariableNameSpace::~tVariableNameSpace()
{
	clear();
}
//-----------------------------------------------------------------------------

void tVariableNameSpace::refresh(void)
{
	// es gibt nischt zu tun.
}

//-----------------------------------------------------------------------------
iElement* tVariableNameSpace::intrface(void)
{
  if (iface == NULL){
    iface = new iVariableNameSpace(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tVariableNameSpace::clear(void)
{
	int i;
  for (i=0;i<varList.count();i++){
    removeVariable(varList.at(i));
  }
  varList.clear();
}
//-----------------------------------------------------------------------------

void tVariableNameSpace::removeVariable(tVariable *var)
{
  if (varList.contains(var)){
    var->releaseOwner(this);
    varList.removeAll(var);
  } else if (inherits){
    inherits->removeVariable(var);
  }
}

//-----------------------------------------------------------------------------

tVariable* tVariableNameSpace::addRealVariable(QString function)
{
  tVariable *var;
  QString name;
  int pos;

  pos = function.indexOf("=");
  if (pos>0){
    name = function.left(pos);
    if (name.endsWith(":")){
      name.remove(name.length()-1,1);
    }
  }
  var = variable(name);
  if (!var) {
    var = new tRealVariable(this, function);
    varList.append(var);
  } else {
    var->setFullString(function);
  }
  return var;
}
//-----------------------------------------------------------------------------

tVariable* tVariableNameSpace::addVectorVariable(QString function)
{
	tVariable *var;
	QString name;
	int pos;

	pos = function.indexOf("=");
	if (pos>0){
		name = function.left(pos);
		if (name.endsWith(":")){
			name.remove(name.length()-1,1);
		}
	}

	var = variable(name);
	if (!var) {
		var = new tVectorVariable(this, function);
    varList.append(var);
	} else {
		var->setFullString(function);
	}
  return var;
}
//-----------------------------------------------------------------------------

tVariable* tVariableNameSpace::addListVariable(QString function)
{
	tVariable *var;
	QString name;
	int pos;

	pos = function.indexOf("=");
	if (pos>0){
		name = function.left(pos);
		if (name.endsWith(":")){
			name.remove(name.length()-1,1);
		}
	}

	var = variable(name);
	if (!var) {
		var = new tListVariable(this, function);
	  varList.append(var);
	} else {
		var->setFullString(function);
	}
  return var;
}
//-----------------------------------------------------------------------------

tVariable* tVariableNameSpace::addVariable(QString function)
{
	tVariable *var;
	QString name;
	int pos;

	pos = function.indexOf("=");
	if (pos>0){
		name = function.left(pos);
		if (name.endsWith(":")){
			name.remove(name.length()-1,1);
		}
	}

	var = variable(name);
	if (var) {
    var->setFullString(function);
  } else if (!name.isEmpty()){
		var = new tRealVariable(this, function);
		if (!var->isValidVariable()){
			var->releaseOwner(this);
			var = new tVectorVariable(this, function);
			if (!var->isValidVariable()){
				var->releaseOwner(this);
				var = new tListVariable(this, function);
				if (!var->isValidVariable()){
				  var->releaseOwner(this);
				  var = NULL;
				}
			}
		}
		if (var){
		  varList.append(var);
		}
	}
  return var;
}
//-----------------------------------------------------------------------------

bool tVariableNameSpace::contains(QString varName)
{
  int i;
  for (i=0;i<varList.count();i++){
  	if (varList.at(i)->name() == varName) {
  		return true;
  	}
  }
	if (inherits){
		return inherits->contains(varName);
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

tVariable* tVariableNameSpace::variable(QString varName)
{
	tVariable *var;
	int i;
	for (i=0;i<varList.count();i++){
		var = varList.at(i);
		if (var && var->name() == varName){
			return var;
		}
	}
	if (inherits){
		return inherits->variable(varName);
	} else {
		return NULL;
	}
}
//-----------------------------------------------------------------------------

tReal tVariableNameSpace::getRealVarValue(QString varName)
{
	tRealVariable* rVar;
	rVar = dynamic_cast<tRealVariable*>(variable(varName));
	return rVar->value();
}

//-----------------------------------------------------------------------------
tVector tVariableNameSpace::getVectorVarValue(QString varName)
{
	tVectorVariable* vVar;
	vVar = dynamic_cast<tVectorVariable*>(variable(varName));
	return vVar->value();
}
//-----------------------------------------------------------------------------

void tVariableNameSpace::inheritNameSpace(tVariableNameSpace *i)
{
	inherits = i;
}
//-----------------------------------------------------------------------------

