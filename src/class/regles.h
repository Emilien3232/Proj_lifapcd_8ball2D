#ifndef _REGLES_H

#define _REGLES_H



#include "Jeu.h"



class Regles {

public:

    void verifierAssignationBoules(Jeu& jeu, int bouleId);

    void changerTour(Jeu& jeu);

    void verifierFinDePartie(Jeu& jeu);

    void bouletombéeBLCH(Jeu& jeu);

    void bouletombéeNR(Jeu& jeu, boule& B);

    bool checkFautes(Jeu& jeu, boule& B);

};



#endif



