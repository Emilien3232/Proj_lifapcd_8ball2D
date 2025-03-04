#ifndef _TABLEDEJEU_H
#define _TABLEDEJEU_H

#include "trou.h"
#include "Vec2.h"

class TableDeJeu{
    private :
        int DimTableX , DimTableY;
        Vec2 pos;
        trou* trous;
    public :
        TableDeJeu() : DimTableX(0) , DimTableY(0) , pos(Vec2(0,0)) , trous(nullptr) {}
        TableDeJeu( int nDimTableX , int nDimTableY , Vec2 npos , trou* ntrous) : DimTableX(nDimTableX) , DimTableY(nDimTableY) , pos(npos) , trous(ntrous) {}
        int getDimTableX() {return DimTableX;}
        int getDimTableY() {return DimTableY;}
        Vec2 getpos() {return pos;}
        trou* gettrous() {return trous;}
};

#endif