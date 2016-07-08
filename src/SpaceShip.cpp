#include "SpaceShip.h"
#include "GameManager.h"
#include "Definitions.h"
#include <stdio.h>
#include <iostream>
#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))
using namespace std;

sf::Image SpaceShip::spaceShipImg;
sf::Image SpaceShip::spaceShipImg2;
sf::Image SpaceShip::spaceShipImg3;
sf::Image SpaceShip::spaceShipImg4;
sf::Image SpaceShip::spaceShipImg5;
sf::Image SpaceShip::trailImg;

SpaceShip::SpaceShip(GameManager * ownerGame, Vector initialPosition)
    : GameObject(ownerGame){

    gameManager = ownerGame;


    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    rotationDir = 0;

    type = SPACESHIP;

    speed = 0.0f;
    acceleration = 160.0f;

    accelerating = false;
    sentido = true;

    sprite.SetImage(spaceShipImg);
    sprite2.SetImage(spaceShipImg2);
    sprite3.SetImage(spaceShipImg3);
    sprite4.SetImage(spaceShipImg4);

    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite2.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite3.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite4.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);


//    position = initialPosition;
//    position2 = initialPosition;
//    position3 = initialPosition;
//    position4 = initialPosition;
//    position5 = initialPosition;

    N = 120;
    i= 0;
    A = 50;
    B= 750;
}

SpaceShip::~SpaceShip()
{

}

void SpaceShip::Accelerate(float deltaTime, float mode){
    speed += acceleration * deltaTime * mode;
    if (mode>0){
        accelerating = true;
    } else {
        accelerating = false;
    }
    if (speed <= 0.0f) {
        speed = 0.0f;
    }
}

float SpaceShip::EaseOutBounce(float t, float b, float c){
    if(t < (1 / 2.75f))
        return c*(7.5625f*t*t) + b;
    else if(t < (2 / 2.75f))
        return c*(7.5625f*(t -= (1.5f / 2.75f))*t + .75f) + b;
    else if (t < (2.5f / 2.75f))
        return c*(7.5625f*(t -= (2.25f / 2.75f))*t + .9375f) + b;
    else
        return c*(7.5625f*(t -= (2.625f / 2.75f))*t + .984375f) + b;
}

void SpaceShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    orientation += deltaTime * rotationDir * 90;

    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(-angle);
    direction.y = sin(-angle);

//    position += direction * speed * deltaTime;

//    sprite2.SetRotation(orientation + spriteRotation);
//    sf::Vector2f tmp = sf::Vector2f(position.x, position.y);
//    sprite2.SetPosition(tmp);

    if (i<=N && i >= 0){
        float v=0.0f;
        float x = 0.0f;
        v = i/N;
        x = (B * v) + (A * (1 - v));
        position = Vector(x, 100);

        v = SMOOTHSTEP(v);
        x = (B * v) + (A * (1 - v));
        position2 = Vector(x, 200);

        v = i/N;
        v = v * v;
        x = (B * v) + (A * (1 - v));
        position3 = Vector(x, 300);

        float y= 0.0f;
        v = i/N;
        x = (B * v) + (A * (1 - v));
        v = v * v;
        y = EaseOut((float) i, 100.0f, 400.0f, (float) N);
//        v = EaseOutBounce(v, 400, 500);
//        int y =(500 * v) + (400 * (1 - v));
        position4 = Vector(x, (int)y);


        if(sentido) {
            i++;
        }else{
            i--;
        }
    } else {
        if(sentido){
            sentido = false;
            i--;
        } else{
            sentido = true;
            i++;
        }

    }
}

float SpaceShip::EaseOut(float t,float b , float c, float d) {
    if ((t/=d) < (1/2.75f)) {
        return c*(7.5625f*t*t) + b;
    } else if (t < (2/2.75f)) {
        float postFix = t-=(1.5f/2.75f);
        return c*(7.5625f*(postFix)*t + .75f) + b;
    } else if (t < (2.5/2.75)) {
            float postFix = t-=(2.25f/2.75f);
        return c*(7.5625f*(postFix)*t + .9375f) + b;
    } else {
        float postFix = t-=(2.625f/2.75f);
        return c*(7.5625f*(postFix)*t + .984375f) + b;
    }
}

void SpaceShip::Draw(sf::RenderWindow & render){
    GameObject::Draw(render);
    sprite2.SetPosition(sf::Vector2f(position2.x, position2.y));
    render.Draw(sprite2);

    sprite3.SetPosition(sf::Vector2f(position3.x, position3.y));
    render.Draw(sprite3);

    sprite4.SetPosition(sf::Vector2f(position4.x, position4.y));
    render.Draw(sprite4);
}

bool SpaceShip::LoadImages()
{
    if (!spaceShipImg.LoadFromFile("graphics/ball.png") || !trailImg.LoadFromFile("graphics/JetTrail.png")
        || !spaceShipImg2.LoadFromFile("graphics/ball01.png") || !spaceShipImg3.LoadFromFile("graphics/ball01.png")
            || !spaceShipImg4.LoadFromFile("graphics/ball01.png"))
        return false;

    return true;
}

// Getters and Setters

float SpaceShip::GetRotationDir(){
    return rotationDir;
}
void SpaceShip::SetRotationDir(float rotationDir){
    this->rotationDir = rotationDir;
}

float SpaceShip::GetSpeed(){
    return speed;
}
void SpaceShip::SetSpeed(float speed){
    this->speed = speed;
}

float SpaceShip::GetAcceleration(){
    return acceleration;
}
void SpaceShip::SetAcceleration(float acceleration){
    this->acceleration = acceleration;
}

sf::Image SpaceShip::GetSpaceShipImg(){
    return spaceShipImg;
}
