#pragma once

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"

class Tile : public sf::Drawable, public sf::Transformable
{
public:
	static TextureCache* textureCache;

	Tile(const tt::TileTypes& _type, const sf::Vector2i& positionInTiles);
	Tile() {}
private:
	static const int Size;

	sf::Sprite sprite;
	tt::TileTypes type;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
};