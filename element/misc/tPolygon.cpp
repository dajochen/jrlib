#include "tPolygon.h"

iElement *tPolygon::intrface()
{
    if (iface == NULL){
        iface = new iPolygon(this);
    }
    return iface;
}
