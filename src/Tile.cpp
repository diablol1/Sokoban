#include "Tile.h"

TextureCache* Tile::textureCache = nullptr;
const int Tile::Size = 64;

Tile::Tile(const tt::TileTypes& _type, const sf::Vector2i& positionInTiles) : type(_type)
{
	sprite.setPosition(positionInTiles.x * Size, positionInTiles.y * Size);

	switch (_type)
	{
	case tt::TileTypes::WALL:
		sprite.setTexture(textureCache->get("wall"));
		break;
	case tt::TileTypes::BOX:
		sprite.setTexture(textureCache->get("box"));
		break;
	case tt::TileTypes::FINISH:
		sprite.setTexture(textureCache->get("finishPoint"));
		break;
	}
}
