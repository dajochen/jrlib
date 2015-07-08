/*
 * ttVectorOperator.cpp
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#include "tVectorOperator.h"
#include "tRealOperator.h"
#include "classes/tVectorStringConverter.h"
#include <QStringList>

tVectorOperator::tVectorOperator(tElement *theowner) : tOperator(theowner)
{
	variable = NULL;
	fvalue.setZero();
//  opType = votIsValue;
  opType = votInvalid;
}
//-----------------------------------------------------------------------------

tVectorOperator::~tVectorOperator()
{
  clear();
}
//-----------------------------------------------------------------------------

iElement* tVectorOperator::intrface(void)
{
  if (iface == NULL){
    iface = new iVectorOperator(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tVectorOperator::clear(void)
{
  int i;
  for (i=0;i<arg.count();i++){
  	arg.at(i)->removeDependent(this);
  }
  arg.clear();
  if (variable){
  	variable->removeDependent(this);
  }
  variable = NULL;
  fvalue.setZero();
  opType = votInvalid;
  invalidate(this);
}
//-----------------------------------------------------------------------------

tVector tVectorOperator::value(void)
{
	update();
	return fvalue;
}
//-----------------------------------------------------------------------------

void tVectorOperator::setValue(tVector v)
{
  setElementLocked
  tRealOperator *ro;
	clear();
	fvalue = v;
	opType = votIsValue;
  ro = new tRealOperator(NULL);
  ro->setValue(v.x);
  arg.append(ro);
  ro = new tRealOperator(NULL);
  ro->setValue(v.y);
  arg.append(ro);
  ro = new tRealOperator(NULL);
  ro->setValue(v.z);
  arg.append(ro);
  invalidate(this);

}
//-----------------------------------------------------------------------------

void tVectorOperator::refresh(void)
{
	tList<tVectorOperatorType> oneArgs, threeArgs;

	oneArgs.append(votBracket);

	threeArgs.append(votStep);

	if (opType == votInvalid){
		fvalue.setZero();
	} if (opType == votIsValue){
		fvalue.x = dynamic_cast<tRealOperator*>(arg.at(0))->value();
		fvalue.y = dynamic_cast<tRealOperator*>(arg.at(1))->value();
		fvalue.z = dynamic_cast<tRealOperator*>(arg.at(2))->value();
	} else if (opType == votIsVariable){
		fvalue = variable->value();
	} else if (oneArgs.contains(opType)){ // alle Funktionen mit einem Argument
		if (arg.count()>=1){
			if (opType == votBracket){
				fvalue = dynamic_cast<tVectorOperator*>(arg.at(0))->value();
			} else {
				fvalue.setZero(); // Sollte nicht vorkommen.
			}
		} else {
			fvalue.setZero(); // Sollte nicht vorkommen.
		}
	} else if (threeArgs.contains(opType)){
		if (arg.count()>=3){
			if (opType == votStep){
				if (dynamic_cast<tRealOperator*>(arg.at(0))->value() > 0.){
					fvalue = dynamic_cast<tVectorOperator*>(arg.at(1))->value();
				} else {
					fvalue = dynamic_cast<tVectorOperator*>(arg.at(2))->value();
				}
			} else {
				fvalue.setZero(); // Sollte nicht vorkommen.
			}
		} else {
			fvalue.setZero(); // Sollte nicht vorkommen.
		}
	} else if (arg.count() == 2) {
		tVectorOperator *v1, *v2;
		v1 = dynamic_cast<tVectorOperator*>(arg.at(0));
		v2 = dynamic_cast<tVectorOperator*>(arg.at(1));
		if (opType == votProduct) {
			if (v1 && dynamic_cast<tRealOperator*>(arg.at(1))){
				fvalue = v1->value() * dynamic_cast<tRealOperator*>(arg.at(1))->value();
			} else if (v2 && dynamic_cast<tRealOperator*>(arg.at(0))){
				fvalue = v2->value() * dynamic_cast<tRealOperator*>(arg.at(0))->value();
			} else {
				opType = votInvalid;
			}
		} else if (v1 && v2) {
			if (opType == votPlus){
				fvalue = v1->value() + v2->value();
			} else if (opType == votMinus){
				fvalue = v1->value() - v2->value();
			} else if (opType == votCrossProduct){
				fvalue = v1->value() % v2->value();
			} else {
				fvalue.setZero();
			}
		} else {
			fvalue.setZero();
		}
	} else {
		fvalue.setZero();
	}
}
//-----------------------------------------------------------------------------

void tVectorOperator::init(QString term, tVariableNameSpace* nameSpace)
{
  setElementLocked
	QStringList argString;
	QList<QString> pm, md, comp;
	tList<tVectorOperatorType> oneArgs, twoArgs, threeArgs;
	int pos;

	clear();

	// Die Operatoren in Gruppen aufteilen
	pm << "+"; // plus und minus
	pm << "-";
	md << "*"; // mal
	md << "%"; // modulo und Kreuzproukt

	oneArgs.append(votBracket);

	twoArgs.append(votPlus);
	twoArgs.append(votMinus);
	twoArgs.append(votProduct);
	twoArgs.append(votCrossProduct);

	threeArgs.append(votStep);
	threeArgs.append(votIsValue);

	opType = votInvalid;

	if(nameSpace->contains(term)){
		// Hinter dem String verbirgt sich eine Variable
		variable = dynamic_cast<tVectorVariable*>(nameSpace->variable(term));
		if (variable && variable->addDependent(this)){
			opType = votIsVariable;
		} else {
			variable = NULL;
			opType = votInvalid;
		}
	}	else {
		// Suche nach Plus- und Minuszeichen nur auf der obersten Klammerebene.
		pos = firstOccurence(pm,term);
		if (pos>=0){
			argString << term.left(pos);
			argString << term.right(term.length()-pos-1);
			if (argString[0].length() == 0){
				argString[0] = "0.";
			}
			if (term.at(pos) == '+'){
				opType = votPlus;
			} else {
				opType = votMinus;
			}
		}	else {
			// Suche nach Mal- und Durchzeichen nur auf der obersten Klammerebene.
			pos = firstOccurence(md,term);
			if (pos>0){
				argString << term.left(pos);
				argString << term.right(term.length()-pos-1);
				if (term.at(pos) == '*'){
					opType = votProduct;
				} else if (term.at(pos) == '%'){
					opType = votCrossProduct;
				} else {
					opType = votInvalid; // sollte nicht vorkommen, sonst Programmierfehler
				}
			}	else if (   (term.endsWith(')') && (   term.startsWith('(')
									   				  				      || term.startsWith("step(")))
								 || (term.endsWith(']') &&      term.startsWith('['))) {
				term.remove(term.length()-1,1);
				if (term.startsWith('[')){
					opType = votIsValue;
					term.remove(0,1);
				} else if (term.startsWith('(')){
					opType = votBracket;
					term.remove(0,1);
				} else if (term.startsWith("step(")) {
					opType = votStep;
					term.remove(0,1);
				} else {
					opType = votInvalid;
				}
				do {
					pos=firstOccurence(QStringList() << ";",term);
					if (pos>=0){
						argString.prepend(term.right(term.length()-pos-1));
						term.remove(pos,term.length());
					} else if (term.length()){
						argString.prepend(term);
					}
				} while (pos > 0);
			} else {
				opType = votInvalid;
			}
		}

		if (opType != votInvalid){
			if (oneArgs.contains(opType)){
				while (argString.count()<1){
					argString.append("?");
				}
				arg.append(new tVectorOperator(NULL));
				arg.at(0)->addDependent(this);
				arg.at(0)->init(argString.at(0),nameSpace);
			} else if (twoArgs.contains(opType)){
				while (argString.count()<2){
					argString.append("?");
				}
				if (opType == votProduct){
					// Erst das Skalar, dann der Vektor.
					arg.append(new tRealOperator(NULL));
					arg.append(new tVectorOperator(NULL));
					arg.at(0)->init(argString.at(0),nameSpace);
					arg.at(1)->init(argString.at(1),nameSpace);
					if (!arg.at(0)->isValidOperator() && !arg.at(1)->isValidOperator()){
						// Dann halt anders rum. Erst der Vektor, dann das Skalar.
						arg.at(0)->releaseOwner(NULL);
						arg.at(1)->releaseOwner(NULL);
						arg.clear();
						arg.append(new tVectorOperator(NULL));
						arg.append(new tRealOperator(NULL));
						arg.at(0)->init(argString.at(0),nameSpace);
						arg.at(1)->init(argString.at(1),nameSpace);
					}
				} else {
					arg.append(new tVectorOperator(NULL));
					arg.append(new tVectorOperator(NULL));
					arg.at(0)->init(argString.at(0),nameSpace);
					arg.at(1)->init(argString.at(1),nameSpace);
				}
				arg.at(0)->addDependent(this);
				arg.at(1)->addDependent(this);
			} else if (threeArgs.contains(opType)){
				while (argString.count()<2){
					argString.append("?");
				}
				if (opType == votStep){
					arg.append(new tRealOperator(NULL));
					arg.append(new tVectorOperator(NULL));
					arg.append(new tVectorOperator(NULL));
				} else {
					// votIsValue;
					arg.append(new tRealOperator(NULL));
					arg.append(new tRealOperator(NULL));
					arg.append(new tRealOperator(NULL));
				}
				arg.at(0)->addDependent(this);
				arg.at(1)->addDependent(this);
				arg.at(2)->addDependent(this);
				arg.at(0)->init(argString.at(0),nameSpace);
				arg.at(1)->init(argString.at(1),nameSpace);
				arg.at(2)->init(argString.at(2),nameSpace);
			} else {
				opType = votInvalid;
			}
		}
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

QString tVectorOperator::toString(void)
{
  setElementLocked
	QString term;
	term = "*error*";
	if (opType == votInvalid){
		term = "*error*";
	} else if (opType == votIsValue){
	  //todo: Anzahl der Argumente ueberpruefen. arg0, arg1 und arg2 kann zum  Programmabsturz fuehren, wenn diese nicht vorhanden sind.
	  // Dies gilt natuerlich auch fuer die anderen else if Eintraege...
		term = '[' + arg.at(0)->toString() + ';' + arg.at(1)->toString() + ';' + arg.at(2)->toString() + ']';
	} else if (opType == votIsVariable && variable){
		term = variable->name();
	// Alle Operatoren
	} else if (opType == votPlus && arg.count() == 2){
		term = arg.at(0)->toString() + "+" + arg.at(1)->toString();
	} else if (opType == votMinus && arg.count() == 2) {
		term = arg.at(0)->toString() + "-" + arg.at(1)->toString();
	} else if (opType == votProduct && arg.count() == 2) {
		term = arg.at(0)->toString() + "*" + arg.at(1)->toString();
	} else if (opType == votCrossProduct && arg.count() == 2) {
		term = arg.at(0)->toString() + "%" + arg.at(1)->toString();
	//Alle Funktionen
	} else {
		if (opType == votBracket){
			term = "(";
		} else if (opType == votStep){
			term = "step(";
		} else {
			term = "*unknown*(";
		}
		int i;
		for (i=0;i<arg.count();i++){
			if (i>0){
				term += ";";
			}
			term += arg.at(i)->toString();
		}
		term += ")";
	}

	return term;
}
//-----------------------------------------------------------------------------

bool tVectorOperator::isValidOperator(void)
{
  setElementLocked
	if (opType == votInvalid){
		return false;
	} else {
		int i;
		bool isValidOp = true;
		for (i=0;i<arg.count();i++){
			if (!arg.at(i)->isValidOperator()){
				isValidOp = false;
				i = arg.count();
			}
		}
		return isValidOp;
	}
}
//-----------------------------------------------------------------------------
