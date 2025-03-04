#ifndef _VEC2_H
#define _VEC2_H

#include <math.h>

struct Vec2 {
    float x , y;
    Vec2(): x(0) , y(0) {}
    Vec2(float nx , float ny) : x(nx) , y(ny) {}
    Vec2 operator+(const Vec2 B) const {return Vec2(x+B.x , y+B.y);}
    Vec2 operator-(const Vec2 B) const {return Vec2(x-B.x , y-B.y);}
    Vec2 operator*(const Vec2 B) const {return Vec2(x * B.x - y * B.y , x * B.y + y * B.x);}
    Vec2 operator*(float lambda) const {return Vec2(x * lambda , y * lambda);}
    bool operator==(const Vec2 other) const {return x == other.x && y == other.y;}
    bool operator!=(const Vec2 other) const {return (x != other.x || y != other.y);}
    float Dist(const Vec2 other) const {return sqrt(pow(other.x - x , 2) + pow(other.y - y , 2));} //retourne la distance avec un autre vec2
    
    float ProduitScalaire(const Vec2 other) const {return x * other.x + y * other.y;} // <Vec2 , other> utiles pour les collisions
    float Normal() const {return ProduitScalaire(Vec2(x,y));} // ||Vec2||² utiles pour les collisions
    Vec2 normalized() const {
        float length = sqrt(x * x + y * y);
        if (length > 0) {
            return Vec2(x / length, y / length);
        } else {
            return Vec2(0, 0); // Éviter la division par zéro
        }
    }
};

#endif