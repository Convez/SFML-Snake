//
// Created by convez on 06/05/2020.
//

#include "HudManager.h"

#include <utility>
#include <sstream>
#include "../Resources.h"
namespace convez::games::managers {

HudManager::HudManager(const sf::FloatRect& iWindowViewRect, std::string iPlayerName) :
        _isGameOver(false),
        _hudView(iWindowViewRect),
        _score(0),
        _playerName(std::move(iPlayerName)) {
    _textFont.loadFromFile(TEXT_FONT_PATH);
    _textDrawable.setFont(_textFont);
    _textDrawable.setCharacterSize(TEXT_SIZE_PIXELS);
    _textDrawable.setFillColor(sf::Color(TEXT_COLOR_RGB));
    _textDrawable.setPosition(TEXT_OFFSET_TOP_PIXELS, TEXT_OFFSET_LEFT_PIXELS);
}

void HudManager::drawHud(sf::RenderWindow& ioWindow) {
    std::stringstream aSs;
    if(_isGameOver)
    {
        aSs << "GAME OVER! ";
    }
    aSs << _playerName << "'s score: " << _score;

    _textDrawable.setString(aSs.str());
    ioWindow.setView(_hudView);
    ioWindow.draw(_textDrawable);
}

void HudManager::initNewGame() {
    _score = 0;
    _isGameOver = false;
    _textDrawable.setFillColor(sf::Color(TEXT_COLOR_RGB));
}

void HudManager::gameOver() {
    _isGameOver = true;
    _textDrawable.setFillColor(sf::Color(TEXT_GAMEOVER_COLOR_RGB));
}

}