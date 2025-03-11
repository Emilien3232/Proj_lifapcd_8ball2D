#ifndef _BOULE_H
#define _BOULE_H

#include "Vec2.h"

struct boule{
    int IDnombre;
    float diam ;
    float masse ; 
    Vec2 positionBoule , directionBoule;
    float vitesseBoule;

    boule() : IDnombre(0) , diam(0.f) , masse(0.f) , positionBoule(Vec2(0,0)) , directionBoule(Vec2(0,0)) , vitesseBoule() {}
    boule(int nIDnombre , float nrayon , float nmasse , Vec2 npositionBoule , Vec2 ndirectionBoule , float nvitesseBoule) : 
        IDnombre(nIDnombre) , diam(nrayon) , masse(nmasse) , positionBoule(npositionBoule) ,directionBoule(ndirectionBoule) , vitesseBoule(nvitesseBoule)  {}
    
};

#endif
