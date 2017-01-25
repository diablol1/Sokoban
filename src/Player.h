#pragma once

#include "Enums.h"
#include "TextureCache.h"
#include <iostream>

class Player : public sf::Drawable
{
public:
	Player(TextureCache* _textureCache, const int _TileSize);

	void move(const dt::Directions& newDirection);
	void undoMove();

	void setPositionInTiles(const sf::Vector2i& position) {
		sprite.setPosition(position.x * TileSize, position.y * TileSize);
	}
	sf::Vector2i getPositionInTiles() {
		return sf::Vector2i(sprite.getPosition().x / TileSize, sprite.getPosition().y / TileSize);
	}
	dt::Directions getCurrentDirection() const {
		return currentDirection;
	}
private:
	const int TileSize;
	sf::Sprite sprite;
	TextureCache* textureCache;

	dt::Directions currentDirection;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
};