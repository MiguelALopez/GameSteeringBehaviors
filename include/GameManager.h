#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
using namespace std;

class GameObject;
class SpaceShip;

class GameManager
{
    public:

        typedef enum {
            MENU, GAME, GAMEOVER
        } GameState;

        GameManager(sf::RenderWindow & appWindow);
        virtual ~GameManager();

        bool Initialize();
        void FreeResources();

        void UpdateGame(float deltaTime);
        void DrawGame();

        void RegisterGameObject(GameObject * newGameObject);
        void RemoveGameObject(GameObject * gameObjectToRemove);
        bool CircleCollision(sf::Vector2f p1, float radius1, sf::Vector2f p2, float radius2);

        void Game(float deltaTime);

        int flag_menu; // Variable que verifica si la flecha esta arriba o abajo

        // Getters and Setters
        GameState GetGameState();
        void SetGameState(GameState gameState);

    protected:

        sf::RenderWindow & renderWindow;

        sf::Image menuImg;
        sf::Sprite menuSprite;

        sf::Image arrowLeftImg;
        sf::Sprite arrowLeftSprite;

        sf::Image arrowRightImg;
        sf::Sprite arrowRightSprite;

        sf::Image gameOverImg;
        sf::Sprite gameOverSprite;

        sf::Image backgroundImg;
        sf::Sprite backgroundSprite;

        SpaceShip * spaceShip;

        std::vector<GameObject *> activeGameObjects;
        std::vector<GameObject *> newGameObjects;

        GameState gameState;
};

#endif // GAMEMANAGER_H
