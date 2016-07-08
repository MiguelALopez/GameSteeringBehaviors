#include "Vector.h"

Vector::Vector() { }

Vector::Vector(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector::~Vector() { }

Vector Vector::operator +(const Vector v){
    return Vector(this->x + v.x, this->y + v.y);
}