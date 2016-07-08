#include "Vector.h"
#include <stdio.h>

int main(){
    Vector vector = Vector(3.0f, 5.0f);
    Vector vector1 = Vector(1.0f, 2.0f);

    Vector resultado = vector + vector1;

    printf("resultado x: %f, y: %f\n", resultado.x, resultado.y);

    return 0;
}