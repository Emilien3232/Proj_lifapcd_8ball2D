#include "Pixel.h"

class Image {
    private :
        int Dimx , Dimy ;
        Pixel* dataPix;
    public : 
        Image();
        Image(int X , int Y);
        ~Image();
        int GetDimx(){return Dimx;}
        int GetDimy(){return Dimy;}
        Pixel* GetdataPix(){return dataPix;}
        Pixel getPix(int x, int y);
        Pixel getPix(int x, int y) const;
        void setPix(int x, int y, Pixel couleur);
        void dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, Pixel couleur);
        void effacer(Pixel clr);

};