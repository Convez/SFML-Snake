//
// Created by convez on 06/05/2020.
//

#include <random>
#include "FieldManager.h"
#include "../Resources.h"

namespace convez::games::managers {
FieldManager::FieldManager(const sf::FloatRect& iWindowViewRect) :
        _fieldView(iWindowViewRect) {
    _wallTexture.loadFromFile(WALL_SPRITE_PATH);
    _wallSprite.setTexture(_wallTexture);
    _wallSprite.setColor(sf::Color(WALL_SPRITE_COLOR_RGB));
    _bottomRightCorner.first = iWindowViewRect.width / SPRITE_TEXTURE_SIZE - 1;
    _bottomRightCorner.second = iWindowViewRect.height / SPRITE_TEXTURE_SIZE - 1;
}

void FieldManager::drawWall(sf::RenderWindow& ioWindow) {
    ioWindow.setView(_fieldView);

    //Draw upper and bottom wall
    for (int itWidth = 0; itWidth <= _bottomRightCorner.first; itWidth++) {
        // Upper wall chunk
        _wallSprite.setPosition(itWidth * SPRITE_TEXTURE_SIZE, 0);
        ioWindow.draw(_wallSprite);
        // Lower wall chunk
        _wallSprite.setPosition(itWidth * SPRITE_TEXTURE_SIZE, _bottomRightCorner.second * SPRITE_TEXTURE_SIZE);
        ioWindow.draw(_wallSprite);
    }
    // Draw left and right wall
    for (int itHeight = 0; itHeight <= _bottomRightCorner.second; itHeight++) {
        // Left wall chunk
        _wallSprite.setPosition(0, itHeight * SPRITE_TEXTURE_SIZE);
        ioWindow.draw(_wallSprite);
        //Right wall chunk
        _wallSprite.setPosition(_bottomRightCorner.first * SPRITE_TEXTURE_SIZE, itHeight * SPRITE_TEXTURE_SIZE);
        ioWindow.draw(_wallSprite);
    }
}


sf::Vector2i FieldManager::getFreeChunk() {
    std::random_device aRd;
    std::mt19937_64 aGen(aRd());
    std::uniform_int_distribution<> aHorizDis(1, _bottomRightCorner.first - 1);
    std::uniform_int_distribution<> aVertDis(1, _bottomRightCorner.second - 1);

    sf::Vector2i aCandidatePoint(aHorizDis(aGen), aVertDis(aGen));
    while(_snakeModel.intersectsWithPoint(aCandidatePoint))
    {
        aCandidatePoint.x = aHorizDis(aGen);
        aCandidatePoint.y = aVertDis(aGen);
    }
    return aCandidatePoint;
}

void FieldManager::initNewGame() {
    _snakeModel.init(getFreeChunk());
    relocateApple();
}

void FieldManager::drawField(sf::RenderWindow& ioWindow) {
    ioWindow.setView(_fieldView);
    drawWall(ioWindow);
    _apple.drawApple(ioWindow);
    _snakeModel.drawSnake(ioWindow);
}

bool FieldManager::isWallHit() {
    return _snakeModel.didHitWall(sf::Vector2i(_bottomRightCorner.first, _bottomRightCorner.second));
}

bool FieldManager::isAppleEaten() {
    return _snakeModel.intersectsWithPoint(_apple.getPosition());
}

void FieldManager::relocateApple() {
    _apple.setPosition(getFreeChunk());
}

}