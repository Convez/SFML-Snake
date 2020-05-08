//
// Created by convez on 05/05/2020.
//

#ifndef SIMPLESNAKE_SNAKEPIECE_H
#define SIMPLESNAKE_SNAKEPIECE_H

/*
 * What does a snake piece need?
 * - The section status
 * - Its position in the map
 */
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../../fields/SnakeSectionStatusField.h"

namespace convez::games::gameElement {
class SnakePiece {
public:
    SnakePiece() = default;
    SnakePiece(const sf::Vector2i& iSectionPosition, const games::fields::SnakeSectionStatusField& iSectionStatus);
    //GETTERS
    const games::fields::SnakeSectionStatusField& getSectionStatus() const;
    games::fields::SnakeSectionStatusField& accessSectionStatus() { return _sectionStatus;}

    const sf::Vector2<int>& getSectionPosition() const;

    //SETTERS
    void setSectionStatus(const games::fields::SnakeSectionStatusField& iSectionStatus);

    void setSectionPosition(const sf::Vector2<int>& iSectionPosition);

    void updateSpriteTexture(const sf::Texture& iTexture);
    const sf::Sprite& getSprite();

    // Here I compute the new status of the section, based on the position of the previous and next elements.
    void computeNewStatus(const sf::Vector2<int>& iPreviousElementPosition, const sf::Vector2<int>& iNextElementPosition);
    void rotateAdjusted(float iDegrees);
private:
    games::fields::SnakeSectionStatusField _sectionStatus;
    sf::Vector2<int> _sectionPosition;
    sf::Sprite          _sectionSprite;
};
}


#endif //SIMPLESNAKE_SNAKEPIECE_H
