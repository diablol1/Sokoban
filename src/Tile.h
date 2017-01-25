#pragma once

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"

class Tile : public sf::Drawable
{
public:
	static TextureCache* textureCache;
	static const int Size;

	Tile(const tt::TileTypes& _type, const sf::Vector2i& positionInTiles);
	Tile() {}

	sf::Vector2i getPositionInTiles() const {
		return sf::Vector2i(sprite.getPosition().x / Size, sprite.getPosition().y / Size);
	}
	tt::TileTypes getType() {
		return type;
	}
	void setType(const tt::TileTypes& newType);
private:

	sf::Sprite sprite;
	tt::TileTypes type;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
};