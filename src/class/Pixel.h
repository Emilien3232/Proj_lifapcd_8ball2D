#ifndef _PIXEL_H
#define _PIXEL_H

struct Pixel
{
    unsigned char r,g,b,a;
    Pixel() : r(0) , g(0) , b(0) , a(0) {}
    Pixel(unsigned char nr ,unsigned char ng ,unsigned char nb , unsigned char na) : r(nr) , g(ng) , b(nb) , a(na) {}
};

#endif