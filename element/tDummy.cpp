/*
 * tDummy.cpp
 *
 *  Created on: 08.02.2011
 *      Author: Jochen
 */

#include "tDummy.h"

tDummy::tDummy(void* theOwner) :tElement(theOwner) {
}
//-----------------------------------------------------------------------------

tDummy::~tDummy() {
}

//-----------------------------------------------------------------------------
iElement* tDummy::intrface(void)
{
  if (iface == NULL){
    iface = new iDummy(this);
  }
  return iface;
}
//-----------------------------------------------------------------------------
