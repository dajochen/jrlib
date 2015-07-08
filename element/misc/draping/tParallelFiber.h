#ifndef TPARALLELFIBER_H
#define TPARALLELFIBER_H

#include "tFiber.h"

class tParallelFiber : public tFiber
{
public:
    tParallelFiber(tFiber *neighbour);

private:
    tFiber* refFiber;

};

#endif // TPARALLELFIBER_H
