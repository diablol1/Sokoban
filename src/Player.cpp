#include "Player.h"

Player::Player(TextureCache* _textureCache, const int _TileSize) : textureCache(_textureCache),
	TileSize(_TileSize)
{
	move(dt::Directions::UP);
}

void Player::move(const dt::Directions & newDirection)
{
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
	std::string textureNameToSet;
	switch (currentDirection)
	{
	case dt::Directions::LEFT:
		move(dt::Directions::RIGHT);
		textureNameToSet = "playerLeft";
		break;
	case dt::Directions::RIGHT:
		move(dt::Directions::LEFT);
		textureNameToSet = "playerRight";
		break;
	case dt::Directions::UP:
		move(dt::Directions::DOWN);
		textureNameToSet = "playerUp";
		break;
	case dt::Directions::DOWN:
		move(dt::Directions::UP);
		textureNameToSet = "playerDown";
		break;
	}
	sprite.setTexture(textureCache->get(textureNameToSet));
}
