#include "Player.h"

Player::Player(TextureCache* _textureCache, const int _TileSize, Counter* _movesCounter) :
	textureCache(_textureCache),
	TileSize(_TileSize),
	movesCounter(_movesCounter)
{
	sprite.setTexture(textureCache->get("playerLeft"));
	currentDirection = dt::Directions::LEFT;
}

void Player::move(const dt::Directions & newDirection)
{
	(*movesCounter)++;
	currentDirection = newDirection;
	std::string textureNameToSet;
	switch (newDirection)
	{
	case dt::Directions::LEFT:
		textureNameToSet = "playerLeft";
		sprite.move(-TileSize, 0);
		break;
	case dt::Directions::RIGHT:
		textureNameToSet = "playerRight";
		sprite.move(TileSize, 0);
		break;
	case dt::Directions::UP:
		textureNameToSet = "playerUp";
		sprite.move(0, -TileSize);
		break;
	case dt::Directions::DOWN:
		textureNameToSet = "playerDown";
		sprite.move(0, TileSize);
		break;
	}
	sprite.setTexture(textureCache->get(textureNameToSet));
}

void Player::undoMove()
{
	(*movesCounter)--;
	std::string textureNameToSet;
	switch (currentDirection)
	{
	case dt::Directions::LEFT:
		sprite.move(TileSize, 0);
		textureNameToSet = "playerLeft";
		break;
	case dt::Directions::RIGHT:
		sprite.move(-TileSize, 0);
		textureNameToSet = "playerRight";
		break;
	case dt::Directions::UP:
		sprite.move(0, TileSize);
		textureNameToSet = "playerUp";
		break;
	case dt::Directions::DOWN:
		sprite.move(0, -TileSize);
		textureNameToSet = "playerDown";
		break;
	}
	sprite.setTexture(textureCache->get(textureNameToSet));
}
