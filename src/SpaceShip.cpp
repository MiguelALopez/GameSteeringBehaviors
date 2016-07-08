#include "SpaceShip.h"
#include "Projectile.h"
#include "GameManager.h"
#include "Asteroid.h"
#include "Definitions.h"
#include <stdio.h>
#include <iostream>
using namespace std;

sf::Image SpaceShip::spaceShipImg;
sf::Image SpaceShip::trailImg;

SpaceShip::SpaceShip(GameManager * ownerGame, sf::Vector2f initialPosition)
    : GameObject(ownerGame){

    gameManager = ownerGame;
    position = initialPosition;
    sprite.SetImage(spaceShipImg);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    sprite2.SetCenter((sprite.GetSize().x / 2)-20, (sprite.GetSize().y / 2)-85);
    sprite.SetScale(1.0f, 1.0f);
    spriteRotation = -90;
    rotationDir = 0;

    type = SPACESHIP;

    speed = 0.0f;
    acceleration = 160.0f;
    vida = 3;

    accelerating = false;

    sprite2.SetImage(trailImg);

    deltaPosition.x = initialPosition.x + 50;
    deltaPosition.y = initialPosition.y + 50;
}

SpaceShip::~SpaceShip()
{

}

// Encargado de lanzar un proyectil
void SpaceShip::EvalProjectile(Projectile::TypeProjectile typeProjectile)
{
    
        Projectile * projectile = new Projectile(gameManager, position, orientation, typeProjectile, GameObject::PROJECTILE_SPACE_SHIP);
        gameManager->RegisterGameObject(projectile); // Se registra la creacion del nuevo proyectil
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

void SpaceShip::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    orientation += deltaTime * rotationDir * 90;

    const float angle = orientation * PI / 180.0f;

    sf::Vector2f direction;
    direction.x = cos(-angle);
    direction.y = sin(-angle);

    position += direction * speed * deltaTime;

    sprite2.SetRotation(orientation + spriteRotation);
    sf::Vector2f tmp = sf::Vector2f(position.x, position.y);
    sprite2.SetPosition(tmp);
}

void SpaceShip::Damage(float x, float y){
    vida--;
    printf("Vidas: %d\n", vida);
    SetSpacePosition(sf::Vector2f(x, y));
    speed = 0;
    if(vida <= 0){
        gameManager->SetGameState(GameManager::GAMEOVER);
        Destroy();
    }
}

void SpaceShip::Draw(sf::RenderWindow & render){
    GameObject::Draw(render);
    if (accelerating){
        render.Draw(sprite2);
    }
}

bool SpaceShip::LoadImages()
{
    if (!spaceShipImg.LoadFromFile("graphics/Spaceship01.png") || !trailImg.LoadFromFile("graphics/JetTrail.png"))
        return false;

    return true;
}

// Getters and Setters

int SpaceShip::GetVida(){
    return vida;
}
void SpaceShip::SetVida(int vida){
    this->vida = vida;
}

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