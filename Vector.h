

class Vector{
public:
    Vector();
    Vector(float x, float y);
    ~Vector();

    Vector operator +(const Vector v);

    float x;
    float y;


};