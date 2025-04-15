#ifndef _JOUEUR_H
#define _JOUEUR_H
#include "boule.h"

class Joueur {
    private : 
        int id; //Joueur 1 => id = 0 //Joueur 2 => id = 1
        int cmpt; //incrementer à chaque événement
        boule* CLRboules; //les boules que le joueur doit faire tomber
        int score; // nombre de CLRboules qui sont tombés 
        bool Actif;
    public:
        Joueur() : id() , cmpt() , CLRboules() , score() , Actif() {}
        Joueur(int nid , int ncmpt , boule* nCLRboules , int nscore , bool nActif) : id(nid) , cmpt(ncmpt) , CLRboules(nCLRboules) , score(nscore) , Actif(nActif) {}
        int& getid() {return id;}
        int& getcmpt() {return cmpt;}
        boule* & getCLRboules() {return CLRboules;}
        int& getscore() {return score;}
        bool& getActif() {return Actif;}

        void setId(int newId) { id = newId; }
        void setCmpt(int newCmpt) { cmpt = newCmpt; }
        void setCLRboules(boule* newBoules) { CLRboules = newBoules; }
        void setScore(int newScore) { score = newScore; }
        void setActif(bool newActif) {Actif = newActif;}
       
};
#endif