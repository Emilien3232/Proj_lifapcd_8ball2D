#ifndef _TROU_H
#define _TROU_H

#include "Vec2.h"

struct trou{
    Vec2 posTrou;
    float rayonTrou;
    trou() : posTrou(Vec2(0,0)) , rayonTrou(0.f) {}
    trou(Vec2 nposTrou , float nrayonTrou) : posTrou(nposTrou) , rayonTrou(nrayonTrou) {}
};

#endif