#ifndef _JEU_H
#define _JEU_H

#include "TableDeJeu.h"
#include "boulesJaunes.h"
#include "boulesRouges.h"
#include "boule.h"

class Jeu {
    private:
        TableDeJeu TDJ;
        boulesJaunes BJ;
        boulesRouges BR;
        boule BouleBlanche;
        boule BouleNoire;
    public:
        Jeu() : TDJ(), BJ(), BR(), BouleBlanche(), BouleNoire() {} // constructeur vide
        Jeu(TableDeJeu nTDJ , boulesJaunes nBJ , boulesRouges nBR , boule nBouleBlanche , boule nBouleNoire) :
            TDJ(nTDJ) , BJ(nBJ) , BR(nBR) , BouleBlanche(nBouleBlanche) , BouleNoire(nBouleNoire) {}

        TableDeJeu getTDJ() {return TDJ;}
        boulesJaunes getBJ() {return BJ;}
        boulesRouges getBR() {return BR;}
        boule getBouleBlanche() {return BouleBlanche;}
        boule getBouleNoire() {return BouleNoire;}
        void INITJEU();
        void test_INITJEU(); //peut etre passé en bool
        bool UPDATEJEU(); // à faire 
        void MAJpositionBoules(); //applique le vecteurs vitesse à la position des boules
        void bouletombé(boulesJaunes B); //verifis et applique des modifications (reduire nombre boules) si les boules jaunes tombent un trou
        void bouletombé(boulesRouges B); //pour les boules rouges
        void bouletombéBLCH(boule B); //pour la boule blanche , cas particulier
        bool bouletombéNR(boule B); //pour la boule noire , cas particulier
        bool checkCollision(const boule b1, const boule b2); //renvoie true si les boules en parametre sont en situation de collision
        void resultCollision(boule &b1 , boule &b2); //applique les nouvelles vitesses au boules après une collision
        void GestionCollisionsBoules();
        void GestionCollisionsBords();

};

#endif
