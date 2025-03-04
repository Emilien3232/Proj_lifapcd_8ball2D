#ifndef _BOULESJAUNES_H
#define _BOULESJAUNES_H

#include "boule.h"
#include "TableDeJeu.h"

class boulesJaunes {
    private :
        boule* Bjaunes;
        int nbBJ;
    public :
        boulesJaunes() : Bjaunes(nullptr) , nbBJ(0) {}
        boulesJaunes(boule* nBjaunes , int nnBJ) : Bjaunes(nBjaunes) , nbBJ(nnBJ) {}
        boule* getBjaunes() {return Bjaunes;}
        int getnbBJ() {return nbBJ;}
        void setnbBJ(int A) {nbBJ = A;}

};

#endif