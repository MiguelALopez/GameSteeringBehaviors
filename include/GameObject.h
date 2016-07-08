#pragma once

#include <SFML/Graphics.hpp>
#include "Vector.h"

class GameManager;


class GameObject
{

public:

    GameObject(GameManager * ownerGame);
    virtual ~GameObject();

    // Definicion del tipo de dato type que determina el tipo de objeto
    typedef enum {
        SPACESHIP, ASTEROID, PROJECTILE_SPACE_SHIP, PROJECTILE_ALIEN_SHIP, ALIENSHIP, EXPLOSION
    } Type;

    void Destroy();

    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow & render);

    // Getters and Setters
    float GetSpaceWidth();
    float GetSpaceHeight();
    Vector GetSpacePosition();
    void SetSpacePosition(Vector position);

    sf::Sprite GetSprite();
    void SetSprite(sf::Sprite sprite);

    float GetOrientation();
    void SetOrientation(float orientation);

    float GetSpriteRotation();
    void SetSpriteRotation(float spriteRotation);

    Type GetType();
    void SetType(Type type);

protected:

    GameManager * gameManager;

    sf::Sprite sprite;
    Vector position;
    float orientation;
    float spriteRotation;

    Type type;

};
