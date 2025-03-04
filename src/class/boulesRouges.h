#ifndef _BOULESROUGES_H
#define _BOULESROUGES_H

#include "boule.h"
#include "TableDeJeu.h"

class boulesRouges {
    private : 
        boule* Brouges;
        int nbBR;
    public :
        boulesRouges() : Brouges(nullptr) , nbBR(0) {}
        boulesRouges(boule* nBrouges , int nnBR) : Brouges(nBrouges) , nbBR(nnBR) {}
        boule* getBrouges() {return Brouges;}
        int getnbBR() {return nbBR;}
        void setnbBR(int A) {nbBR = A;}

};

#endif