//
// Created by convez on 06/05/2020.
//

#ifndef SIMPLESNAKE_HUDMANAGER_H
#define SIMPLESNAKE_HUDMANAGER_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace convez::games::managers{

class HudManager {
public:
    HudManager(const sf::FloatRect& iWindowViewRect, std::string  iPlayerName);

    void initNewGame();
    void gameOver();
    void drawHud(sf::RenderWindow& ioWindow);

    void addScore(uint64_t iDeltaScore) { _score+= iDeltaScore; }
private:
    bool            _isGameOver;
    sf::View        _hudView;
    sf::Font        _textFont;
    sf::Text        _textDrawable;
    uint64_t        _score;
    std::string     _playerName;
};

}

#endif //SIMPLESNAKE_HUDMANAGER_H
