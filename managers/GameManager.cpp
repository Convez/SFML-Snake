//
// Created by convez on 05/05/2020.
//

#include "GameManager.h"

#include <utility>
#include <sstream>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../Resources.h"

namespace convez::games::managers {
GameManager::GameManager(const sf::FloatRect& iWindowViewRect, const std::string& iPlayerName) :
        _hudManager(iWindowViewRect, iPlayerName),
        _fieldManager(iWindowViewRect)
{
}

void GameManager::drawGameView(sf::RenderWindow& ioWindow) {
    _fieldManager.drawField(ioWindow);
    _hudManager.drawHud(ioWindow);
}

void GameManager::initNewGame() {
    _isGameOver = false;
    _fieldManager.initNewGame();
    _hudManager.initNewGame();
}

void GameManager::processInput() {
    using sf::Keyboard;
    if(Keyboard::isKeyPressed(Keyboard::Up))
        _fieldManager.accessSnake().changeSnakeVelocity(sf::Vector2i(0,-1));
    else if(Keyboard::isKeyPressed(Keyboard::Down))
        _fieldManager.accessSnake().changeSnakeVelocity(sf::Vector2i(0, 1));
    else if(Keyboard::isKeyPressed(Keyboard::Left))
        _fieldManager.accessSnake().changeSnakeVelocity(sf::Vector2i(-1,0));
    else if(Keyboard::isKeyPressed(Keyboard::Right))
        _fieldManager.accessSnake().changeSnakeVelocity(sf::Vector2i(1,0));
    else if(_isGameOver && Keyboard::isKeyPressed(Keyboard::BackSpace))
        initNewGame();
}

void GameManager::tick() {
    if(!_isGameOver)
    {
        if(!_fieldManager.accessSnake().isStill())
        {
            _hudManager.addScore(GAME_SCORE_NORMAL);
            if(_fieldManager.isAppleEaten()){
                _hudManager.addScore(GAME_SCORE_APPLE);
                _fieldManager.relocateApple();
                _fieldManager.accessSnake().eatApple();
            }
            else
            {
                _fieldManager.accessSnake().advance();
            }
            _isGameOver = _fieldManager.isWallHit() || _fieldManager.accessSnake().didHitHitself();
        }
    }
    else
    {
        _fieldManager.accessSnake().changeSnakeVelocity(sf::Vector2i(0,0));
        _hudManager.gameOver();
    }
}

}