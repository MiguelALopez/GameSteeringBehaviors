#include "../include/Vector.h"

Vector::Vector() { }

Vector::Vector(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector::~Vector() { }

Vector Vector::operator +(const Vector vector){
    return Vector(this->x + vector.x, this->y + vector.y);
}

Vector Vector::operator -(const Vector vector){
    return Vector(this->x - vector.x, this->x - vector-y);
}

Vector Vector::operator *(const float escalar){
    return Vector(this->x * escalar, this->y * escalar);
}

Vector Vector::operator /(const float escalar){
    return Vector(this->x / escalar, this->y / escalar);
}

Vector Vector::operator *(const Vector vector){
    return Vector(this->x * vector.x, this->y * vector.y);
}