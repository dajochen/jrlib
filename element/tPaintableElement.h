#ifndef TPAINTABLEELEMENT_H
#define TPAINTABLEELEMENT_H

#include "element/tElement.h"
#include "GL/glu.h"

#include "iPaintableElement.h"

class tPaintableElement : public tElement
{
public:
    tPaintableElement(void* theOwner) : tElement(theOwner) {}

    virtual void paintGL(const tVector& EyePoint, const tVector& ObjectPoint, const tRGB& rgb, const tVector& defaultN, const bool& isSelected) = 0;
/*I!
*/
};

#endif // TPAINTABLEELEMENT_H
