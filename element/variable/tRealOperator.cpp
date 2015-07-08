/*
 * tRealOperator.cpp
 *
 *  Created on: 25.08.2009
 *      Author: Jochen
 */

#include "tRealOperator.h"
#include "tVectorOperator.h"
#include "tListOperator.h"
#include <QStringList>

#include "classes/utils.h"

tRealOperator::tRealOperator(tElement *theowner)
: tOperator(theowner)
{
	variable = NULL;
	fvalue = 0.;
	opType = rotIsValue;
}
//-----------------------------------------------------------------------------

tRealOperator::~tRealOperator() {
	clear();
}
//-----------------------------------------------------------------------------

iElement* tRealOperator::intrface(void)
{
  if (iface == NULL){
    iface = new iRealOperator(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

void tRealOperator::clear(void)
{
  int i;
  for (i=0;i<arg.count();i++){
  	arg.at(i)->removeDependent(this);
  }
  arg.clear();
  if (variable){
  	variable->removeDependent(this);
  	variable = NULL;
  }
	opType = rotIsValue;
//  fvalue = 0.;
//  invalidate(this); Hier kein invalidate, da man sonst mit value(xxx) nich aut sich selbst verweisen kann.
}
//-----------------------------------------------------------------------------

tReal tRealOperator::value(void)
{
	update();
	return fvalue;
}
//-----------------------------------------------------------------------------

void tRealOperator::setValue(tReal v)
{
	clear();
	fvalue = v;
	opType = rotIsValue;
	invalidate(this);
}
//-----------------------------------------------------------------------------

void tRealOperator::refresh(void)
{
	tList<tRealOperatorType> oneArgs, twoArgs, threeArgs, manyArgs;

	oneArgs.append(rotBracket);
	oneArgs.append(rotSinus);
	oneArgs.append(rotCosinus);
	oneArgs.append(rotTangens);
	oneArgs.append(rotArccos);
	oneArgs.append(rotArcsin);
	oneArgs.append(rotArctan);
	oneArgs.append(rotSquareroot);
	oneArgs.append(rotAbsolut);
	oneArgs.append(rotRoundIt);
	oneArgs.append(rotCeilIt);
	oneArgs.append(rotFloorIt);

	twoArgs.append(rotArctan2);

	threeArgs.append(rotStep);

	manyArgs.append(rotMinimum);
	manyArgs.append(rotMaximum);

	if (opType == rotInvalid){
		fvalue = 0.;
	} if (opType == rotIsValue){
		// Wert wurde in der init-Funktion gesetzt
	} else if (opType == rotIsVariable){
		if (dynamic_cast<tRealVariable*>(variable)){
			fvalue = dynamic_cast<tRealVariable*>(variable)->value();
		} else {
			fvalue = 0.;
		}
	} else if (oneArgs.contains(opType)){ // alle Funktionen mit einem Argument
		if (arg.count()>=1){
			if (opType == rotBracket){
				fvalue = dynamic_cast<tRealOperator*>(arg.at(0))->value();
			} else if (opType == rotSinus) {
				fvalue = sin(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotCosinus) {
				fvalue = cos(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotTangens) {
				fvalue = tan(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotArccos) {
				fvalue = acos(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotArcsin) {
				fvalue = asin(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotArctan) {
				fvalue = atan(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotSquareroot) {
				fvalue = sqrt(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotAbsolut) {
				fvalue = fabs(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotRoundIt) {
				fvalue = round(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotCeilIt) {
				fvalue = ceil(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else if (opType == rotFloorIt) {
				fvalue = floor(dynamic_cast<tRealOperator*>(arg.at(0))->value());
			} else {
				fvalue = 0.; // Sollte nicht vorkommen.
			}
		} else {
			fvalue = 0.; // Sollte nicht vorkommen.
		}
	} else if (twoArgs.contains(opType)){
		if (arg.count()>=2){
			if (opType == rotArctan2) {
				fvalue = atan2(dynamic_cast<tRealOperator*>(arg.at(0))->value(),
											 dynamic_cast<tRealOperator*>(arg.at(1))->value());
			} else {
				fvalue = 0.; // Sollte nicht vorkommen.
			}
		} else {
			fvalue = 0.; // Sollte nicht vorkommen.
		}
	} else if (threeArgs.contains(opType)){
		if (arg.count()>=3){
			if (opType == rotStep){
				if (dynamic_cast<tRealOperator*>(arg.at(0))->value() > 0.){
					fvalue = dynamic_cast<tRealOperator*>(arg.at(1))->value();
				} else {
					fvalue = dynamic_cast<tRealOperator*>(arg.at(2))->value();
				}
			} else {
				fvalue = 0.; // Sollte nicht vorkommen.
			}
		} else {
			fvalue = 0.; // Sollte nicht vorkommen.
		}
	} else if (manyArgs.contains(opType)){
		if (opType == rotMinimum || opType == rotMaximum){
			int i;
			tReal v;
			if (arg.count()>0){
				if (arg.at(0)->type()==vtReal){
					fvalue = dynamic_cast<tRealOperator*>(arg.at(0))->value();
				} else if (arg.at(0)->type()==vtList){
					if (opType == rotMinimum){
						fvalue = dynamic_cast<tListOperator*>(arg.at(0))->minimum();
					} else {
						fvalue = dynamic_cast<tListOperator*>(arg.at(0))->maximum();
					}
				} else {
					fvalue = 0.;
				}
				for (i=1;i<arg.count();i++){
					if (arg.at(i)->type()==vtReal){
						v = dynamic_cast<tRealOperator*>(arg.at(i))->value();
					} else if (arg.at(i)->type()==vtList){
						if (opType == rotMinimum){
							v = dynamic_cast<tListOperator*>(arg.at(i))->minimum();
						} else {
							v = dynamic_cast<tListOperator*>(arg.at(i))->maximum();
						}
					} else {
						v = 0.;
					}
					if (opType == rotMinimum){
						fvalue = min(fvalue,v);
					} else {
						fvalue = max(fvalue,v);
					}
				}
			} else {
				fvalue = 0.;
			}
		} else {
			fvalue = 0.;
		}
	} else if (arg.count() == 2) {
		tRealOperator *r1, *r2;
		r1 = dynamic_cast<tRealOperator*>(arg.at(0));
		r2 = dynamic_cast<tRealOperator*>(arg.at(1));
		if (opType == rotMultiply) {
			if (r1 && r2){
				fvalue = r1->value() * r2->value();
			} else if (arg.at(0)->type()==vtVector && arg.at(1)->type()==vtVector) {
				fvalue = dynamic_cast<tVectorOperator*>(arg.at(0))->value() * dynamic_cast<tVectorOperator*>(arg.at(1))->value();
			}
		} else if (r1 && r2) {
			if (opType == rotPlus){
				fvalue = r1->value() + r2->value();
			} else if (opType == rotMinus){
				fvalue = r1->value() - r2->value();
			} else if (opType == rotModulo && r1 && r2){
				fvalue = (tReal)((int)(r1->value()) % (int)(r2->value()));
			} else if (opType == rotDivide) {
				if (r2->value() != 0.){
					fvalue = r1->value() / r2->value();
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotPower) {
				fvalue = pow(r1->value(), r2->value());
			} else if (opType == rotIsEqual) {
				if (r1->value() == r2->value()){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotIsLess) {
				if (r1->value() < r2->value()){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotIsLessOrEqual) {
				if (r1->value() <= r2->value()){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotIsGreater) {
				if (r1->value() > r2->value()){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotIsGreaterOrEqual) {
				if (r1->value() >= r2->value()){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotLogicalAnd) {
				if (r1->value() != 0. && r2->value() != 0.){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else if (opType == rotLogicalOr){
				if (r1->value() != 0. || r2->value() != 0.){
					fvalue = 1.;
				} else {
					fvalue = 0.;
				}
			} else {
				fvalue = 0.;
			}
		} else {
			fvalue = 0.;
		}
	} else {
		fvalue = 0.;
	}
}
//-----------------------------------------------------------------------------

void tRealOperator::init(QString term, tVariableNameSpace* nameSpace)
{
	QStringList argString;
	QList<QString> pm, md, comp, boolean, exponent;
	tList<tRealOperatorType> oneArgs, twoArgs, threeArgs, manyArgs;
	int pos;
	bool fisValue;

	clear();

	// Die Operatoren in Gruppen aufteilen
	boolean << "&"; // Boolsche Operatoren
	boolean << "|";
	comp << "=="; // Vergleiche
	comp << "<=";
	comp << ">=";
	comp << "<";
	comp << ">";
	pm << "+"; //plus und minus
	pm << "-";
	md << "*"; //mal, durch
	md << "/";
	md << "%"; // modulo und Kreuzproukt
	exponent << "^"; // hoch

	oneArgs.append(rotBracket);
	oneArgs.append(rotSinus);
	oneArgs.append(rotCosinus);
	oneArgs.append(rotTangens);
	oneArgs.append(rotArccos);
	oneArgs.append(rotArcsin);
	oneArgs.append(rotArctan);
	oneArgs.append(rotSquareroot);
	oneArgs.append(rotAbsolut);
	oneArgs.append(rotRoundIt);
	oneArgs.append(rotCeilIt);
	oneArgs.append(rotFloorIt);

	twoArgs.append(rotArctan2);
	twoArgs.append(rotPlus);
	twoArgs.append(rotMinus);
	twoArgs.append(rotMultiply);
	twoArgs.append(rotDivide);
	twoArgs.append(rotModulo);
	twoArgs.append(rotPower);
	twoArgs.append(rotIsEqual);
	twoArgs.append(rotIsLess);
	twoArgs.append(rotIsLessOrEqual);
	twoArgs.append(rotIsGreater);
	twoArgs.append(rotIsGreaterOrEqual);
	twoArgs.append(rotLogicalAnd);
	twoArgs.append(rotLogicalOr);

	threeArgs.append(rotStep);

	manyArgs.append(rotMinimum);
	manyArgs.append(rotMaximum);


	//opType = rotInvalid;

	term.toDouble(&fisValue);
	if (fisValue){
	  fvalue = term.toDouble(&fisValue); // fValue nicht eher ueberschreiben, wird evtl. noch von der value()-Funktion benötigt.
		opType = rotIsValue;
	} else if(nameSpace->contains(term)){
		// Hinter dem String verbirgt sich eine Variable
		variable = dynamic_cast<tRealVariable*>(nameSpace->variable(term));
		if (variable && variable->addDependent(this)){
			opType = rotIsVariable;
		} else {
			variable = NULL;
			opType = rotInvalid;
		}
	}	else {
		pos = firstOccurence(boolean,term);
		if (pos>0){
			argString << term.left(pos);
			argString << term.right(term.length()-pos);
			if (argString[1].startsWith("&")){
				opType = rotLogicalAnd;
				argString[1].remove(0,1);
			} else if (argString[1].startsWith("|")){
				opType = rotLogicalOr;
				argString[1].remove(0,1);
			}	else {
				opType = rotInvalid;
			}
		} else {
			pos = firstOccurence(comp,term);
			if (pos>0){
				argString << term.left(pos);
				argString << term.right(term.length()-pos);
				if (argString[1].startsWith("==")){
					opType = rotIsEqual;
					argString[1].remove(0,2);
				} else if (argString[1].startsWith("<=")){
					opType = rotIsLessOrEqual;
					argString[1].remove(0,2);
				} else if (argString[1].startsWith(">=")){
					opType = rotIsGreaterOrEqual;
					argString[1].remove(0,2);
				} else if (argString[1].startsWith("<")){
					opType = rotIsLess;
					argString[1].remove(0,1);
				} else if (argString[1].startsWith(">")){
					opType = rotIsGreater;
					argString[1].remove(0,1);
				} else {
					opType = rotInvalid; // Sollte nicht vorkommen, sonst Bug.
				}
			} else {
			// Suche nach Plus- und Minuszeichen nur auf der obersten Klammerebene.
				pos = firstOccurence(pm,term);
				if (pos>=0){
					argString <<  term.left(pos);
					argString << term.right(term.length()-pos-1);
					if (argString[0].length() == 0){
						argString[0] = "0.";
					}
					if (term.at(pos) == '+'){
						opType = rotPlus;
					} else {
						opType = rotMinus;
					}
				}	else {
					// Suche nach Mal- und Durchzeichen nur auf der obersten Klammerebene.
					pos = firstOccurence(md,term);
					if (pos>0){
						argString << term.left(pos);
						argString << term.right(term.length()-pos-1);
						if (term.at(pos) == '*'){
							opType = rotMultiply;
						} else if (term.at(pos) == '/'){
							opType = rotDivide;
						} else if (term.at(pos) == '%'){
							opType = rotModulo;
						} else {
							opType = rotInvalid; // sollte nicht vorkommen, sonst Programmierfehler
						}
					} else {
					// Suche nach "^"; nur auf der obersten Klammerebene.
						pos = firstOccurence(exponent,term);
						if (pos>0){
							argString << term.left(pos);
							argString << term.right(term.length()-pos-1);
							if (term.at(pos) == '^'){
								opType = rotPower;
							} else {
								opType = rotInvalid; // sollte nicht vorkommen, sonst Programmierfehler
							}
						}	else if (term.endsWith(')') && ( term.startsWith('(')
										        		   				  ||term.startsWith("cos(")
													 				  				||term.startsWith("sin(")
													 				  				||term.startsWith("tan(")
													 				  				||term.startsWith("asin(")
													 				  				||term.startsWith("acos(")
												   				  				||term.startsWith("atan(")
												   				  				||term.startsWith("atan2(")
												   				  				||term.startsWith("min(")
												   				  				||term.startsWith("max(")
												   				  				||term.startsWith("sqrt(")
												   				  				||term.startsWith("abs(")
												   				  				||term.startsWith("round(")
												   				  				||term.startsWith("ceil(")
												   				  				||term.startsWith("floor(")
												   				  				||term.startsWith("step(")
												   				  				||term.startsWith("value("))) {

							term.remove(term.length()-1,1);
							if (term.startsWith('(')){
								opType = rotBracket;
								term.remove(0,1);
							} else if (term.startsWith("abs(")){
								opType = rotAbsolut;
								term.remove(0,4);
							} else if (term.startsWith("round(")){
								opType = rotRoundIt;
								term.remove(0,6);
							} else if (term.startsWith("ceil(")){
								opType = rotCeilIt;
								term.remove(0,5);
							} else if (term.startsWith("floor(")){
								opType = rotFloorIt;
								term.remove(0,6);
							} else if (term.startsWith("cos(")){
								opType = rotCosinus;
								term.remove(0,4);
							} else if (term.startsWith("sin(")){
								opType = rotSinus;
								term.remove(0,4);
							} else if (term.startsWith("tan(")){
								opType = rotTangens;
								term.remove(0,4);
							} else if (term.startsWith("asin(")){
								opType = rotArcsin;
								term.remove(0,5);
							} else if (term.startsWith("acos(")){
								opType = rotArccos;
								term.remove(0,5);
							} else if (term.startsWith("atan(")){
								opType = rotArctan;
								term.remove(0,5);
							} else if (term.startsWith("atan2(")){
								opType = rotArctan2;
								term.remove(0,6);
							} else if (term.startsWith("min(")){
								opType = rotMinimum;
								term.remove(0,4);
							} else if (term.startsWith("max(")){
								opType = rotMaximum;
								term.remove(0,4);
							} else if (term.startsWith("sqrt(")){
								opType = rotSquareroot;
								term.remove(0,5);
							} else if (term.startsWith("step(")){
								opType = rotStep;
								term.remove(0,5);
							} else if (term.startsWith("value(")){
								opType = rotIsValue;
								term.remove(0,6);
								tRealOperator *op;
								op = new tRealOperator(this);
								op->init(term,nameSpace);
								fvalue = op->value();
								op->releaseOwner(this);
							} else {
								opType = rotInvalid; // sollte nicht vorkommen, ansonsten ->Bug
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
							fvalue = 0.;
							opType = rotInvalid;
						}
					}
				}
			}
		}
		if (opType != rotInvalid && opType != rotIsValue){
			int i,ni;
			if (oneArgs.contains(opType)){
				ni = 1;
			} else if (twoArgs.contains(opType)){
				ni = 2;
			} else if (threeArgs.contains(opType)){
				ni = 3;
			} else if (manyArgs.contains(opType)){
				ni = argString.count();
			}
			for (i=0;i<ni;i++){
				arg.append(new tRealOperator(NULL));
				arg.at(i)->addDependent(this);
				if (i>=argString.count()){
					argString.append("?");
				}
				arg.at(i)->init(argString.at(i),nameSpace);
			}
			if (!isValidOperator()){
				if (opType == rotMultiply && argString.count()==2){
					// ein Skalarprodukt erkennen.
					arg.at(0)->removeDependent(this);
					arg.at(1)->removeDependent(this);
					arg.clear();
					for (i=0;i<ni;i++){
						arg.append(new tVectorOperator(NULL));
						arg.at(i)->addDependent(this);
						if (i<argString.count()){
							arg.at(i)->init(argString.at(i),nameSpace);
						}
					}
				} else if (opType == rotMinimum || opType == rotMaximum){
					for (i=0;i<arg.count();i++){
						if (!arg.at(i)->isValidOperator()){
							arg.at(i)->removeDependent(this);
							arg.setAt(i,new tListOperator(NULL));
							arg.at(i)->init(argString.at(i),nameSpace);
						}
					}
				}
			}
		}
	}
	invalidate(this);
}
//-----------------------------------------------------------------------------

QString tRealOperator::toString(void)
{
	QString term;

	term = "*error*";
	if (opType == rotInvalid){
		term = "*error*";
	} else if (opType == rotIsValue){
		term = QString::number(fvalue);
	} else if (opType == rotIsVariable && variable){
		term = variable->name();
	// Alle Operatoren
	} else if (opType == rotPlus && arg.count() == 2){
		term = arg.at(0)->toString() + "+" + arg.at(1)->toString();
	} else if (opType == rotMinus && arg.count() == 2) {
		term = arg.at(0)->toString() + "-" + arg.at(1)->toString();
	} else if (opType == rotMultiply && arg.count() == 2) {
		term = arg.at(0)->toString() + "*" + arg.at(1)->toString();
	} else if (opType == rotDivide && arg.count() == 2) {
		term = arg.at(0)->toString() + "/" + arg.at(1)->toString();
	} else if (opType == rotModulo && arg.count() == 2) {
		term = arg.at(0)->toString() + "%" + arg.at(1)->toString();
	} else if (opType == rotPower && arg.count() == 2) {
		term = arg.at(0)->toString() + "^" + arg.at(1)->toString();
	} else if (opType == rotIsEqual && arg.count() == 2) {
		term = arg.at(0)->toString() + "==" + arg.at(1)->toString();
	} else if (opType == rotIsLess && arg.count() == 2) {
		term = arg.at(0)->toString() + "<" + arg.at(1)->toString();
	} else if (opType == rotIsLessOrEqual && arg.count() == 2) {
		term = arg.at(0)->toString() + "<=" + arg.at(1)->toString();
	} else if (opType == rotIsGreater && arg.count() == 2) {
		term = arg.at(0)->toString() + ">" + arg.at(1)->toString();
	} else if (opType == rotIsGreaterOrEqual && arg.count() == 2) {
		term = arg.at(0)->toString() + ">=" + arg.at(1)->toString();
	} else if (opType == rotLogicalAnd && arg.count() == 2) {
		term = arg.at(0)->toString() + "&" + arg.at(1)->toString();
	} else if (opType == rotLogicalOr && arg.count() == 2){
		term = arg.at(0)->toString() + "|" + arg.at(1)->toString();
	//Alle Funktionen
	} else {
		if (opType == rotBracket){
			term = "(";
		} else if (opType == rotSinus) {
			term = "sin(";
		} else if (opType == rotCosinus) {
			term = "cos(";
		} else if (opType == rotTangens) {
			term = "tan(";
		} else if (opType == rotArccos) {
			term = "acos(";
		} else if (opType == rotArcsin) {
			term = "asin(";
		} else if (opType == rotArctan) {
			term = "atan(";
		} else if (opType == rotSquareroot) {
			term = "sqrt(";
		} else if (opType == rotAbsolut) {
			term = "abs(";
		} else if (opType == rotRoundIt) {
			term = "round(";
		} else if (opType == rotCeilIt) {
			term = "ceil(";
		} else if (opType == rotFloorIt) {
			term = "floor(";
		} else if (opType == rotArctan2) {
			term = "atan2(";
		} else if (opType == rotStep){
			term = "step(";
		} else if (opType == rotMaximum) {
			term = "max(";
		} else if (opType == rotMinimum) {
			term = "min(";
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

bool tRealOperator::isValidOperator(void)
{
	if (opType == rotInvalid){
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

