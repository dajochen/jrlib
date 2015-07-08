#include "tTriangle.h"

iElement *tTriangle::intrface()
{
    if (iface == NULL){
        iface = new iTriangle(this);
    }
    return iface;
}

