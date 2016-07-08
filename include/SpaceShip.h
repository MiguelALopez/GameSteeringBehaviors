#pragma once

#include "GameObject.h"

class SpaceShip : public GameObject
{
public:

    SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition);
    virtual ~SpaceShip();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    static bool LoadImages();

    void Accelerate(float deltaTime, float mode);

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
    static sf::Image trailImg;

    float rotationDir; // Direccion de rotacion de la nave
    
    float speed; //Velocidad de la nave
    float acceleration; // Aceleracion de la nave

    sf::Sprite sprite2;
    bool accelerating;

    sf::Vector2f deltaPosition;

    int i;
    float N;
    float A;
    float B;
};
