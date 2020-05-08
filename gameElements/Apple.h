//
// Created by convez on 07/05/2020.
//

#ifndef SIMPLESNAKE_APPLE_H
#define SIMPLESNAKE_APPLE_H


#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace convez::games::gameElement{

class Apple {
public:
    Apple();

    void drawApple(sf::RenderWindow& ioWindow);

    // Sets and gets position in map coordinates
    void setPosition(const sf::Vector2i& iPosition) { _applePosition = iPosition; }
    const sf::Vector2i& getPosition() { return _applePosition; }
private:
    sf::Texture _appleTexture;
    sf::Sprite _appleSprite;

    sf::Vector2i _applePosition;
};

}


#endif //SIMPLESNAKE_APPLE_H
