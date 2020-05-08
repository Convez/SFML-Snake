//
// Created by convez on 05/05/2020.
//

#include <iostream>
#include "SnakeModel.h"
#include "../../Resources.h"

namespace convez::games::gameElement{

void SnakeModel::setTextureForSnakeSection(
        const games::fields::SnakeSectionStatusField &iSectionField, const sf::Texture &iTexture) {
    _snakePieceTextureMap[iSectionField] = iTexture;
}

bool SnakeModel::changeSnakeVelocity(sf::Vector2<int> iNewVelocity) {
    sf::Vector2<int> aSumVector = _snakeVelocity + iNewVelocity;
    // The requested turn is 180° if the sum of the old and new velocity vector is (0,0)
    if(!aSumVector.x && !aSumVector.y)
    {
        return false;
    }
    _snakeVelocity = iNewVelocity;
    return true;
}

void SnakeModel::init(const sf::Vector2<int>& iHeadPosition) {
    _snakePiecesField.clear();
    _snakeVelocity = sf::Vector2i(0,0);
    using games::fields::SnakeSectionStatusField;
    _snakePiecesField.emplace_front(iHeadPosition, SnakeSectionStatusField(SnakeSectionStatusField::k_HeadPieceDown));
    initSpriteMap();
}

void SnakeModel::initSpriteMap() {
    using fields::SnakeSectionStatusField;
    sf::Image aSnakeImage;
    aSnakeImage.loadFromFile(SNAKE_SPRITE_SHEET_PATH);
    sf::Texture aTmpTexture;
    //Head Sprite
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE*3,0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_HeadPieceUp), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE*4, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_HeadPieceDown), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE*3,SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_HeadPieceLeft), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE*4,0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_HeadPieceRight), aTmpTexture);
    // Tail Sprite
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE *3, SPRITE_TEXTURE_SIZE * 2, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_TailPieceUp), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE *4, SPRITE_TEXTURE_SIZE * 3, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_TailPieceDown), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE *3, SPRITE_TEXTURE_SIZE * 3, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_TailPieceLeft), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE *4, SPRITE_TEXTURE_SIZE * 2, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_TailPieceRight), aTmpTexture);
    // Corner Pieces
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(0,0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownRight), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE * 2,0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_CornerDownLeft), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpRight), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE *2, SPRITE_TEXTURE_SIZE*2, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_CornerUpLeft), aTmpTexture);
    // Line Pieces
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE, 0, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_LinePieceHoriz), aTmpTexture);
    aTmpTexture.loadFromImage(aSnakeImage,sf::IntRect(SPRITE_TEXTURE_SIZE * 2, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE));
    setTextureForSnakeSection(SnakeSectionStatusField(SnakeSectionStatusField::k_LinePieceVert), aTmpTexture);
}

bool SnakeModel::intersectsWithPoint(const sf::Vector2i& iPoint) {
    return std::any_of(_snakePiecesField.begin(), _snakePiecesField.end(),
                       [&iPoint](const SnakePiece& iPiece){ return iPoint == iPiece.getSectionPosition(); });
}

void SnakeModel::drawSnake(sf::RenderWindow& ioWindow) {
    for(auto aSnakePieceIt = _snakePiecesField.rbegin(); aSnakePieceIt != _snakePiecesField.rend(); ++aSnakePieceIt)
    {
        aSnakePieceIt->updateSpriteTexture(_snakePieceTextureMap.at(aSnakePieceIt->getSectionStatus()));
        ioWindow.draw(aSnakePieceIt->getSprite());
    }
}

void SnakeModel::advance() {
    for(auto aSnakeIter = _snakePiecesField.rbegin(); aSnakeIter != _snakePiecesField.rend(); ++aSnakeIter)
    {
        auto aNext = std::next(aSnakeIter);
        if(aNext != _snakePiecesField.crend()){
            aSnakeIter->setSectionPosition(aNext->getSectionPosition());
        }
    }
    _snakePiecesField.front().setSectionPosition(_snakePiecesField.front().getSectionPosition() + _snakeVelocity);

    if(_snakePiecesField.size() > 1)
    {
        for(auto aSnakeIter = std::next(_snakePiecesField.begin()); aSnakeIter != std::prev(_snakePiecesField.end()); ++aSnakeIter)
        {
            aSnakeIter->computeNewStatus(std::next(aSnakeIter)->getSectionPosition(), std::prev(aSnakeIter)->getSectionPosition());
        }

        auto aTailOffset = std::next(_snakePiecesField.rbegin())->getSectionPosition() - _snakePiecesField.back().getSectionPosition();
        fields::SnakeSectionStatusField aNewTailStatus;
        aNewTailStatus.setFromString("Tail" + getDirectionFromOffset(aTailOffset));
        _snakePiecesField.back().setSectionStatus(aNewTailStatus);
    }

    fields::SnakeSectionStatusField aNewHeadStatus;
    aNewHeadStatus.setFromString("Head" + getDirectionFromOffset(_snakeVelocity));
    _snakePiecesField.front().setSectionStatus(aNewHeadStatus);
}

bool SnakeModel::didHitWall(sf::Vector2<int> iBottomRightCorner) {
    return  _snakePiecesField.front().getSectionPosition().x == 0 ||
            _snakePiecesField.front().getSectionPosition().y == 0 ||
            _snakePiecesField.front().getSectionPosition().x == iBottomRightCorner.x ||
            _snakePiecesField.front().getSectionPosition().y == iBottomRightCorner.y;
}

bool SnakeModel::didHitHitself() {
    auto itSnake = _snakePiecesField.begin();
    itSnake++;
    while(itSnake != _snakePiecesField.end())
    {
        if(itSnake->getSectionPosition() == _snakePiecesField.front().getSectionPosition())
        {
            return true;
        }
        itSnake++;
    }
    return false;
}

void SnakeModel::eatApple() {
    _snakePiecesField.emplace_front(_snakePiecesField.front().getSectionPosition() + _snakeVelocity,
                                    fields::SnakeSectionStatusField(fields::SnakeSectionStatusField::k_HeadPieceDown));
    _snakePiecesField.front().accessSectionStatus().setFromString("Head" + getDirectionFromOffset(_snakeVelocity));
    std::next(_snakePiecesField.begin())->setSectionStatus(fields::SnakeSectionStatusField(fields::SnakeSectionStatusField::k_LinePieceHoriz));
    if(_snakePiecesField.size()>1)
    {
        auto aTailOffset = std::next(_snakePiecesField.rbegin())->getSectionPosition() - _snakePiecesField.back().getSectionPosition();
        fields::SnakeSectionStatusField aNewTailStatus;
        aNewTailStatus.setFromString("Tail" + getDirectionFromOffset(aTailOffset));
        _snakePiecesField.back().setSectionStatus(aNewTailStatus);
        if(_snakePiecesField.size()>2)
        {
            std::next(_snakePiecesField.begin())->computeNewStatus(_snakePiecesField.front().getSectionPosition(),
                      std::next(std::next(_snakePiecesField.begin()))->getSectionPosition());
        }
    }
}

std::string SnakeModel::getDirectionFromOffset(const sf::Vector2i& iOffsetVector) {
    std::string aOffsetString;
    if(iOffsetVector.y == 0)
    {
        if(iOffsetVector.x >0)
        {
            aOffsetString = "Right";
        }
        else
        {
            aOffsetString = "Left";
        }
    }
    else if (iOffsetVector.y > 0)
    {
        aOffsetString = "Down";
    }
    else
    {
        aOffsetString = "Up";
    }
    return aOffsetString;
}

}
