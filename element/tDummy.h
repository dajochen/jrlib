/*
 * tDummy.h
 *
 *  Created on: 08.02.2011
 *      Author: Jochen
 */

#ifndef TDUMMY_H_
#define TDUMMY_H_

#include "element/tElement.h"
#include "iDummy.h"
class tDummy : public tElement
{
public:
  tDummy(void *theOwner);
  virtual ~tDummy();
  virtual iElement* intrface(void);

private:
  virtual void refresh(void){};

};
/*I!
*/

#endif /* TDUMMY_H_ */
