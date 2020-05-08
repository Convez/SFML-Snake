//
// Created by convez on 07/05/2020.
//

#include "Apple.h"
#include "../Resources.h"

namespace convez::games::gameElement{

Apple::Apple() {
    _appleTexture.loadFromFile(APPLE_SPRITE_PATH);
    _appleSprite.setTexture(_appleTexture);
}

void Apple::drawApple(sf::RenderWindow& ioWindow) {
    sf::Vector2f aWorldCoordVec(_applePosition * SPRITE_TEXTURE_SIZE);
    _appleSprite.setPosition(aWorldCoordVec);
    ioWindow.draw(_appleSprite);
}

}
