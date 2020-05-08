//
// Created by convez on 05/05/2020.
//

#include "SnakePiece.h"
#include "../../Resources.h"

const convez::games::fields::SnakeSectionStatusField& convez::games::gameElement::SnakePiece::getSectionStatus() const {
    return _sectionStatus;
}

void convez::games::gameElement::SnakePiece::setSectionStatus(
        const convez::games::fields::SnakeSectionStatusField& sectionStatus) {
    _sectionStatus = sectionStatus;
}

const sf::Vector2<int>& convez::games::gameElement::SnakePiece::getSectionPosition() const {
    return _sectionPosition;
}

void convez::games::gameElement::SnakePiece::setSectionPosition(const sf::Vector2<int>& sectionPosition) {
    _sectionPosition = sectionPosition;
    _sectionSprite.setPosition(_sectionPosition.x * SPRITE_TEXTURE_SIZE, _sectionPosition.y * SPRITE_TEXTURE_SIZE);
}

convez::games::gameElement::SnakePiece::SnakePiece(const sf::Vector2i& iSectionPosition,
                                                   const convez::games::fields::SnakeSectionStatusField& iSectionStatus):
    _sectionPosition(iSectionPosition),
    _sectionStatus(iSectionStatus)
{
    _sectionSprite.setPosition(_sectionPosition.x * SPRITE_TEXTURE_SIZE, _sectionPosition.y * SPRITE_TEXTURE_SIZE);
}

void convez::games::gameElement::SnakePiece::updateSpriteTexture(const sf::Texture& iTexture) {
    _sectionSprite.setTexture(iTexture);
}

const sf::Sprite& convez::games::gameElement::SnakePiece::getSprite() {
    return _sectionSprite;
}

void convez::games::gameElement::SnakePiece::computeNewStatus(const sf::Vector2<int>& iPreviousElementPosition,
                                                              const sf::Vector2<int>& iNextElementPosition) {
    using fields::SnakeSectionStatusField;

    // Line piece - Going upwards or going straight
    if(iPreviousElementPosition.y == iNextElementPosition.y || iPreviousElementPosition.x == iNextElementPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_LinePieceVert);
        if(iPreviousElementPosition.y == iNextElementPosition.y)
        {
            _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_LinePieceHoriz);
        }
        return;
    }
    // Going down from the left
    if(iNextElementPosition.y > _sectionPosition.y && iPreviousElementPosition.x < _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownLeft);
        return;
    }
    // Going down from the right
    if(iNextElementPosition.y > _sectionPosition.y && iPreviousElementPosition.x > _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownRight);
        return;
    }
    // Going up from the left
    if(iNextElementPosition.y < _sectionPosition.y && iPreviousElementPosition.x < _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpLeft);
        return;
    }
    // Going up from the right
    if(iNextElementPosition.y < _sectionPosition.y && iPreviousElementPosition.x > _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpRight);
        return;
    }
    if(iPreviousElementPosition.y < _sectionPosition.y && iNextElementPosition.x < _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpLeft);
        return;
    }
    if(iPreviousElementPosition.y < _sectionPosition.y && iNextElementPosition.x > _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpRight);
        return;
    }
    if(iPreviousElementPosition.y > _sectionPosition.y && iNextElementPosition.x < _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownLeft);
        return;
    }
    if(iPreviousElementPosition.y > _sectionPosition.y && iNextElementPosition.x > _sectionPosition.x)
    {
        _sectionStatus = SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownRight);
        return;
    }

}

void convez::games::gameElement::SnakePiece::rotateAdjusted(float iDegrees){
    auto aOldOrigin = sf::Vector2f(_sectionSprite.getOrigin().x, _sectionSprite.getOrigin().y);
    _sectionSprite.setRotation(iDegrees);
    auto aOffset = _sectionSprite.getOrigin() - aOldOrigin;
    _sectionSprite.move(aOffset.x, aOffset.y);
}
