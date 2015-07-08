/*
 * tOperator.cpp
 *
 *  Created on: 07.01.2009
 *      Author: Jochen
 */

#include <QStringList>

#include "tOperator.h"
#include "tRealVariable.h"
#include "tVectorVariable.h"

#include "classes/utils.h"


tOperator::tOperator(tElement *theowner) : tElement(theowner)
{
}
//-----------------------------------------------------------------------------

tOperator::~tOperator()
{
}
//-----------------------------------------------------------------------------

iElement* tOperator::intrface(void)
{
  if (iface == NULL){
    iface = new iOperator(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------

QString tOperator::reverseString(QString s)
{
	int i;
	QString rev;
	for (i=s.length()-1;i>=0;i--){
		rev += s.at(i);
	}
	return rev;
}
//-----------------------------------------------------------------------------

int tOperator::startsWith(QStringList e, QString s){
	int i;
	bool isStarting = false;
	for (i=0;i<e.count() && !isStarting;i++){
		isStarting = s.startsWith(e.at(i));
	}
	return isStarting;
}
//-----------------------------------------------------------------------------

int tOperator::firstOccurence(QStringList e, QString s)
{
	// Die Terme werden ueblicher weise von links nach rechts abgearbeitet.
	// Daher hat der am weitesten rechts stehende Operator die geringste
	// Priorität. Da die Stringverarbeitung von links nach rechts einfacher ist,
	// werden die strings s und e vorher umgedreht...
	int pos, bracketLength;

	s = reverseString(s);
	for (pos=0;pos < e.count(); pos++){
		e[pos] = reverseString(e[pos]);
	}

	pos = s.length()-1;
	while (!s.isEmpty() && !startsWith(e,s)){
		if (s.at(0) == ')'){
			s.remove(0,1);
			bracketLength = s.length()-firstOccurence(QStringList("("),reverseString(s));
			if (bracketLength > 0){
				s.remove(0,bracketLength);
				pos -= 1 + bracketLength;
			} else {
				return -1;
			}
		} else if (s.at(0) == ']'){
			s.remove(0,1);
			bracketLength = s.length()-firstOccurence(QStringList("["),reverseString(s));
			if (bracketLength > 0){
				s.remove(0,bracketLength);
				pos -= 1 + bracketLength;
			} else {
				return -1;
			}
		} else if (s.at(0) == '}'){
			s.remove(0,1);
			bracketLength = s.length()-firstOccurence(QStringList("{"),reverseString(s));
			if (bracketLength > 0){
				s.remove(0,bracketLength);
				pos -= 1 + bracketLength;
			} else {
				return -1;
			}
		} else {
			s.remove(0,1);
			pos -= 1;
		}
	}
	if (startsWith(e,s)){
		return pos;
	} else {
		return -1;
	}
}
//--------------------------------------------------------------

