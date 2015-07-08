#ifndef TINITIALFIBER_H
#define TINITIALFIBER_H

#include "element/misc/draping/tFiber.h"

class NodeLocation {
public:
    NodeLocation(int I,int J): i(I),j(J){}
    bool operator == (const NodeLocation& l) const {
        return (i==l.i && j==l.j);
    }
    const int i,j;
};
inline uint qHash(const NodeLocation &key,uint seed)
{
    return qHash(key.i, seed);
}

class tInitialFiber : public tFiber
{
public:
    tInitialFiber(tTrianglePatch *patch, tDot *refPoint, const tVector fiberDir, const tVector projDir, const double meshSize);


private:
    QHash<NodeLocation,tDot*> mesh;
    void addParallelFiber(int j, int dj);
};

class tParallelFiber : public tFiber
{
public:
    tParallelFiber(tFiber* referenceFiber, bool rightHand);

private:
    tFiber* referenceFiber_;
    tList<tFiber*> fibers;
};

#endif // TINITIALFIBER_H
