#include "class/Image.h"
#include <cassert>

Image::Image(){
    Dimx = 0;
    Dimy = 0;
    dataPix = nullptr;
}

Image::Image(int X , int Y){
    Dimx = X;;
    Dimy = Y;
    assert(X < 0 || Y < 0);
    dataPix = new Pixel [Dimx * Dimy];
}

Image::~Image(){
    Dimx = 0;
    Dimy = 0;    
    delete [] dataPix;
    dataPix = nullptr;
}

Pixel Image::getPix(int x , int y){
    Pixel p;
    p.r = 0;
    p.g = 0;
    p.b = 0;
    if (x < Dimx && x > 0 && y < Dimy && y > 0) {
        return dataPix[y * Dimx + x];
    } else {
        return p;
    }
}

Pixel Image::getPix(int x , int y) const{
    Pixel P;
    if (x < Dimx && x > 0 && y < Dimy && y > 0) {
        P = dataPix[y * Dimx + x];
    } else {
        P.r = 0;
        P.g = 0;
        P.b = 0;
    }
    return P;
}

void Image::setPix(int x , int y , Pixel couleur){
    dataPix[y * Dimx + x] = couleur;
}

void Image::dessinerRectangle(int Xmin , int Ymin , int Xmax , int Ymax , Pixel couleur){
    for (unsigned int i = Ymin ; i <= Ymax ; i++){
        for(unsigned int j = Xmin ; j <= Xmax ; j++){
            setPix(j, i, couleur);
        }
    }
}

void Image::effacer(Pixel couleur){
    for (unsigned int i=0 ; i<Dimy ; i++){
        for(unsigned int j=0 ; j<Dimx ; j++ ){
            setPix(j,i,couleur);
        }
    }
}