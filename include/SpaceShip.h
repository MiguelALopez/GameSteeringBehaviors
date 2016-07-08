#pragma once
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))

#include "GameObject.h"
//#include "Vector.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, Vector initialPosition);
    virtual ~SpaceShip();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

    void Accelerate(float deltaTime, float mode);
    float EaseOutBounce(float t, float b, float c);

    // Getters and Setters
    int GetVida();
    void SetVida(int vida);

    float GetRotationDir();
    void SetRotationDir(float rotationDir);

    float GetSpeed();
    void SetSpeed(float speed);

    float GetAcceleration();
    void SetAcceleration(float acceleration);

    sf::Image GetSpaceShipImg();

private:

    static sf::Image spaceShipImg;
    static sf::Image spaceShipImg2;
    static sf::Image spaceShipImg3;
    static sf::Image spaceShipImg4;
    static sf::Image spaceShipImg5;
    static sf::Image trailImg;

    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;

    Vector position2;
    Vector position3;
    Vector position4;
    Vector position5;

    float rotationDir; // Direccion de rotacion de la nave
    
    float speed; //Velocidad de la nave
    float acceleration; // Aceleracion de la nave


    bool accelerating;
    bool sentido;

    int i;
    float N;
    float A;
    float B;
};
