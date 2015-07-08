/*
 * tVariable.cpp
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#include "tVariable.h"

/*
 * neue tVariable-Elemente muessen immer ueber die Klasse tVariableNameSpace
 * erzeugt werden. Dazu kann deren Methode addVariable(QString) verwendet werden.
 * Eine direkte Instanziierung mit new ist nicht zulaessig.
 * BSP:
 * 	ns.addVariable("a:=1");    // a nimmt den Wert 1 an.
 * 	ns.addVariable("b=a+1");  // b speichert den Term a+1 und wertet diesen aus.
 *  ns.addVariable("c:=c+2"); // c nimmt den Wert 4 an. (einmalige Auswertung)
 * 	ns.addVariable("a=1");    // a nimmt den Wert 1 an, ist identisch mit a:=1.
 */

tVariable::tVariable(tVariableNameSpace *nameSpace) : tElement(nameSpace)
{
	fnameSpace = nameSpace;
	fnameSpace->addDependent(this);
//	fname = "";
}
//-----------------------------------------------------------------------------

tVariable::~tVariable()
{
	fnameSpace->removeDependent(this);
}
//-----------------------------------------------------------------------------

iElement* tVariable::intrface(void){
  if (iface == NULL){
    iface = new iVariable(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

bool tVariable::isValidVariable(void)
{
  setElementLocked
	if (oper()){
		return oper()->isValidOperator();
	} else {
		return false;
	}
}
//-----------------------------------------------------------------------------

QString tVariable::name(void)
{
  setElementLocked
  return intrface()->name();
//	return fname;
}
//-----------------------------------------------------------------------------

void tVariable::setName(QString name)
{
//	fname = name;
  setElementLocked
  intrface()->setPropertyString("name",name);
	invalidate(this);
}
//-----------------------------------------------------------------------------

	QString tVariable::fullString(void)
{
	  setElementLocked
	if (oper()){
		return name() + "=" + oper()->toString();
	} else {
		return name() + "= *error*";
	}
}
//-----------------------------------------------------------------------------

QString tVariable::RHS(void)
{
  setElementLocked
	if (oper()){
		return oper()->toString();
	} else {
		return "*error*";
	}
}
//-----------------------------------------------------------------------------

void tVariable::setFullString(QString function)
{
  setElementLocked
  int pos;
  function = function.simplified();
	function.remove(" ");

	pos = function.indexOf(":=");
	if (pos > 0){
  	setName(function.left(pos));
	  function = function.right(function.length()-pos-2);
	  setRHS("value\"" + (function) + "\"");
	} else {
		pos = function.indexOf("=");
		if (pos > 0){
			setName(function.left(pos));
			function = function.right(function.length()-pos-1);
			setRHS(function);
		}
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------
/*
void tVariable::setRHS(QString rhs)
{
  if (op){
  	op->removeDependent(this);
  	op->releaseOwner(this);
  }
  op = new tOperator(this);
  op->addDependent(this);
  op->init(rhs, fnameSpace);
  invalidate(this);
}
//-----------------------------------------------------------------------------
*/
