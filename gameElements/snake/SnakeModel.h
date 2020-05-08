//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_SNAKEMODEL_H
#define SIMPLESNAKE_SNAKEMODEL_H

#include <string>
#include <list>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../fields/SnakeSectionStatusField.h"
#include "SnakePiece.h"

namespace convez::games::gameElement {

/*
 * What does a snake need for a game of snake?
 * - Textures: One for the head, one for the tail, one for the body and the corner pieces
 * - A list of each of its pieces, each with its current status
 */
class SnakeModel {
public:
    SnakeModel() = default;

    void init(const sf::Vector2<int>& iHeadPosition);

    //Returns false if velocity change is not possible: I.E. A 180° turn
    bool changeSnakeVelocity(sf::Vector2<int> iNewVelocity);
    void setTextureForSnakeSection(const games::fields::SnakeSectionStatusField& iSectionField, const sf::Texture& iTexture);

    bool intersectsWithPoint(const sf::Vector2i& iPoint);

    void drawSnake(sf::RenderWindow& ioWindow);
    void advance();

    bool didHitWall(sf::Vector2<int> iBottomRightCorner);
    bool didHitHitself();
    bool isStill() { return _snakeVelocity == sf::Vector2i(0,0); }

    void eatApple();
private:
    static std::string getDirectionFromOffset(const sf::Vector2i& iOffsetVector);
    void initSpriteMap();
    std::map<games::fields::SnakeSectionStatusField, sf::Texture> _snakePieceTextureMap;
    std::list<SnakePiece> _snakePiecesField;
    sf::Vector2<int> _snakeVelocity;
};
}

#endif //SIMPLESNAKE_SNAKEMODEL_H
