

class Vector{
public:
    Vector();
    Vector(float x, float y);
    ~Vector();

    Vector operator +(const Vector vector);
    Vector operator -(const Vector vector);
    Vector operator *(const float escalar);
    Vector operator /(const float escalar);
    Vector operator *(const Vector vector);

    float x;
    float y;


};