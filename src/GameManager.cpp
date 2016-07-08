#include "GameManager.h"
#include "SpaceShip.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

GameManager::GameManager(sf::RenderWindow & appWindow) :
    renderWindow(appWindow)
{
    spaceShip = NULL;

    gameState = MENU;

    flag_menu = 0;
}

GameManager::~GameManager()
{
    //dtor
}

bool GameManager::Initialize()
{
    activeGameObjects.clear();
    if(!menuImg.LoadFromFile("graphics/menu.png"))
        return false;

    menuSprite.SetImage(menuImg);
    menuSprite.SetScale(1.0f, 1.0f);

    if(!arrowLeftImg.LoadFromFile("graphics/arrow1.png"))
        return false;

    arrowLeftSprite.SetImage(arrowLeftImg);
    arrowLeftSprite.SetScale(1.0f, 1.0f);
    arrowLeftSprite.SetPosition(250.0f, 331.0f);

    if(!arrowRightImg.LoadFromFile("graphics/arrow2.png"))
        return false;

    arrowRightSprite.SetImage(arrowRightImg);
    arrowRightSprite.SetScale(1.0f, 1.0f);
    arrowRightSprite.SetPosition(510.0f, 331.0f);

    if(!gameOverImg.LoadFromFile("graphics/gameOver.png"))
        return false;

    gameOverSprite.SetImage(gameOverImg);

    if (!backgroundImg.LoadFromFile("graphics/Background.png"))
        return false;

    backgroundSprite.SetImage(backgroundImg);
    backgroundSprite.SetScale(0.5f, 0.5f);

    if (!SpaceShip::LoadImages())
        return false;

    spaceShip = new SpaceShip(this, sf::Vector2f(renderWindow.GetWidth()/2, renderWindow.GetHeight()/2));
    RegisterGameObject(spaceShip);
    return true;
}

void GameManager::FreeResources()
{
    if (spaceShip)
        delete spaceShip;
}

void GameManager::Game(float deltaTime){
    const sf::Input & input = renderWindow.GetInput();

    float rotationDir = 0;

    // Se establecen los eventos para el movimiento de la nave
    if (input.IsKeyDown(sf::Key::Left))
        rotationDir += 2.0f;

    if (input.IsKeyDown(sf::Key::Right))
        rotationDir -= 2.0f;

    spaceShip->SetRotationDir(rotationDir);


    if (input.IsKeyDown(sf::Key::Up)) {
        spaceShip->Accelerate(deltaTime, 1.0f);
    } else {
        spaceShip->Accelerate(deltaTime, -1.0f);
    }


    activeGameObjects.insert(activeGameObjects.end(),
                             newGameObjects.begin(),
                             newGameObjects.end());
    newGameObjects.clear();


    for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        // renderWindow.GetWidth()/2, renderWindow.GetHeight()/2
        // Verifica si se pasa del borde izquierdo
        if((*it)->GetSpacePosition().x < 0){
            (*it)->SetSpacePosition(sf::Vector2f(renderWindow.GetWidth(), (*it)->GetSpacePosition().y));
        }
        // Verifica si se pasa del borde derecho
        if((*it)->GetSpacePosition().x > renderWindow.GetWidth()){
            (*it)->SetSpacePosition(sf::Vector2f(0, (*it)->GetSpacePosition().y));
        }

        // Verifica si se pasa del borde superior
        if((*it)->GetSpacePosition().y < 0){
            (*it)->SetSpacePosition(sf::Vector2f((*it)->GetSpacePosition().x, renderWindow.GetHeight()));
        }

        // Verifica si se pasa del borde inferior
        if((*it)->GetSpacePosition().y > renderWindow.GetHeight()){
            (*it)->SetSpacePosition(sf::Vector2f((*it)->GetSpacePosition().x, 0));
        }

        (*it)->Update(deltaTime);
        if (it == activeGameObjects.end())
        {
            break;
        }
    }
}

void GameManager::UpdateGame(float deltaTime)
{
    const sf::Input & input = renderWindow.GetInput();
    if(gameState == MENU){
        if (input.IsKeyDown(sf::Key::Up) && flag_menu == 1) {
            arrowLeftSprite.SetPosition(arrowLeftSprite.GetPosition().x, arrowLeftSprite.GetPosition().y - 55);
            arrowRightSprite.SetPosition(arrowRightSprite.GetPosition().x, arrowRightSprite.GetPosition().y - 55);
            flag_menu = 0;
            
        }
        if (input.IsKeyDown(sf::Key::Down) && flag_menu == 0){
            arrowLeftSprite.SetPosition(arrowLeftSprite.GetPosition().x, arrowLeftSprite.GetPosition().y + 55);
            arrowRightSprite.SetPosition(arrowRightSprite.GetPosition().x, arrowRightSprite.GetPosition().y + 55);
            flag_menu = 1;
        }

        if(input.IsKeyDown(sf::Key::Return) && flag_menu == 0){
            gameState = GAME;
        }else if(input.IsKeyDown(sf::Key::Return) && flag_menu == 1){
            exit(0);
        }
    }else if(gameState == GAME){
        Game(deltaTime);

    }else if(gameState == GAMEOVER){
        if (input.IsKeyDown(sf::Key::Back)){
            gameState = MENU;
        }
    }
}

void GameManager::DrawGame()
{
    if(gameState == MENU){
        renderWindow.Draw(menuSprite);
        renderWindow.Draw(arrowLeftSprite);
        renderWindow.Draw(arrowRightSprite);
    } else if (gameState == GAME){
        // Se dibuja el fondo
        renderWindow.Draw(backgroundSprite);

        // Se dibuja cada uno de los objetos activos
        for (std::vector<GameObject *>::iterator it = activeGameObjects.begin();
             it != activeGameObjects.end(); ++it){
            (*it)->Draw(renderWindow);
        }

    } else if(gameState == GAMEOVER){
        renderWindow.Draw(gameOverSprite);
    }
}

// Agrega un objeto a la lista de objetos nuevos
void GameManager::RegisterGameObject(GameObject * newGameObject)
{
    newGameObjects.push_back(newGameObject);
}

// Elimina un objeto de la lista de objetos nuevos
void GameManager::RemoveGameObject(GameObject * gameObjectToRemove)
{
    for (std::vector<GameObject *>::iterator
            it = newGameObjects.begin();
         it != newGameObjects.end(); ++it)
    {
        if (*it == gameObjectToRemove)
        {
            newGameObjects.erase(it);
            break;
        }
    }

    for (std::vector<GameObject *>::iterator
            it = activeGameObjects.begin();
         it != activeGameObjects.end(); ++it)
    {
        if (*it == gameObjectToRemove)
        {
            activeGameObjects.erase(it);
            break;
        }
    }

}

bool GameManager::CircleCollision(sf::Vector2f p1, float radius1, sf::Vector2f p2, float radius2){
    float sumRadius = radius1 + radius2;
    sf::Vector2f delta = p2 - p1;
    float distanceSquare = delta.x * delta.x + delta.y * delta.y;
    return (distanceSquare < sumRadius * sumRadius);
}

// Getter and Setters
GameManager::GameState GameManager::GetGameState(){
    return gameState;
}

void GameManager::SetGameState(GameManager::GameState gameState){
    this->gameState = gameState;
}