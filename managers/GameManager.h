//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_GAMEMANAGER_H
#define SIMPLESNAKE_GAMEMANAGER_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "HudManager.h"
#include "FieldManager.h"

/*
 * What does a game of Snake needs?
 * It needs:
 *     A player, obviously. This concept can be included in the game, if we imagine: 1 GameManager for 1 Player
 *     A view of the game fields.
 *     A view of the score.
 *     A snake.
 */
namespace convez::games::managers{

class GameManager {
public:
    GameManager(const sf::FloatRect& iWindowViewRect, const std::string& iPlayerName);

    void initNewGame();

    void processInput();
    void tick();

    void drawGameView(sf::RenderWindow& ioWindow);
    bool isGameOver() { return _isGameOver; }
private:
    HudManager      _hudManager;
    FieldManager    _fieldManager;

    sf::View        _gameView;
    bool _isGameOver;
};

}

#endif //SIMPLESNAKE_GAMEMANAGER_H
