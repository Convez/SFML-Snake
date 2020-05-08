//
// Created by convez on 06/05/2020.
//

#ifndef SIMPLESNAKE_FIELDMANAGER_H
#define SIMPLESNAKE_FIELDMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../gameElements/snake/SnakeModel.h"
#include "../gameElements/Apple.h"

namespace convez::games::managers{

class FieldManager {
public:
    explicit FieldManager(const sf::FloatRect& iWindowViewRect);

    void drawField(sf::RenderWindow& ioWindow);

    void initNewGame();

    // Gets a chunk non occupied by either the wall, or the snake.
    // It is potentially very slow, since it uses rand
    sf::Vector2i getFreeChunk();

    gameElement::SnakeModel& accessSnake() { return _snakeModel; }
    bool isWallHit();

    bool isAppleEaten();
    void relocateApple();
private:
    void drawWall(sf::RenderWindow& ioWindow);

    sf::View _fieldView;
    sf::Texture _wallTexture;
    sf::Sprite  _wallSprite;

    gameElement::SnakeModel _snakeModel;
    gameElement::Apple      _apple;
    // Holds the coordinate of the bottom right corner in chunk map coordinates
    std::pair<int, int> _bottomRightCorner;
};

}


#endif //SIMPLESNAKE_FIELDMANAGER_H
