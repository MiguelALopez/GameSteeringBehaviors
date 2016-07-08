#include "include/Vector.h"
#include <stdio.h>
#include <iostream>
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
using namespace std;

int main(){
    Vector vector = Vector(3.0f, 5.0f);
    Vector vector1 = Vector(1.0f, 2.0f);

    Vector resultado = vector + vector1;

    printf("resultado x: %f, y: %f\n", resultado.x, resultado.y);

    float v=0.0f;
    float N = 15.0f;
    float A= 10.0f;
    float B= 35.0f;
    float x = 0.0f;

    for (int i=0; i <= N; i++){
    	v = i/N;
    	v= v * v;
    	x = (B * v) + (A * (1 - v));
    	cout << x << endl;
    }

    return 0;
}