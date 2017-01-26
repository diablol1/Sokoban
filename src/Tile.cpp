#include "Tile.h"

TextureCache* Tile::textureCache = nullptr;
const int Tile::Size = 64;

Tile::Tile(const tt::TileTypes& _type, const sf::Vector2i& positionInTiles)
{
	sprite.setPosition(positionInTiles.x * Size, positionInTiles.y * Size);
	setType(_type);
}

void Tile::setType(const tt::TileTypes & newType)
{
	type = newType;
	switch (newType)
	{
	case tt::TileTypes::NONE:
		sprite.setTexture(textureCache->get("none"));
		break;
	case tt::TileTypes::WALL:
		sprite.setTexture(textureCache->get("wall"));
		break;
	case tt::TileTypes::BOX:
		sprite.setTexture(textureCache->get("box"));
		break;
	case tt::TileTypes::FINISH:
		sprite.setTexture(textureCache->get("finishPoint"));
		break;
	case tt::TileTypes::BOX_ON_FINISH:
		sprite.setTexture(textureCache->get("redBox"));
	}
}