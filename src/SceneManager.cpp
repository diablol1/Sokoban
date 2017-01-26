#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(TextureCache* _textureCache) :
	textureCache(_textureCache),
	player(textureCache, Tile::Size)
{
	
}

void SceneManager::loadLevelFromFile(const std::string & filename)
{
	std::ifstream file(filename);

	std::string x, y;
	file >> x >> y;
	player.setPositionInTiles(sf::Vector2i(std::stoi(x), std::stoi(y)));

	sf::Vector2i loadCounter;
	while (!file.eof())
	{
		int tileType;
		file >> tileType;

		tiles[loadCounter.x][loadCounter.y] = Tile(static_cast<tt::TileTypes>(tileType), loadCounter);

		loadCounter.x++;
		if (file.peek() == '\n')
		{
			loadCounter.x = 0;
			loadCounter.y++;
		}
	}
}

void SceneManager::processEvents(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			player.move(dt::Directions::LEFT);
			break;
		case sf::Keyboard::Right:
			player.move(dt::Directions::RIGHT);
			break;
		case sf::Keyboard::Up:
			player.move(dt::Directions::UP);
			break;
		case sf::Keyboard::Down:
			player.move(dt::Directions::DOWN);
			break;
		}
	}
}

void SceneManager::detectCollisions()
{
	Tile *tileUnderPlayer = &tiles[player.getPositionInTiles().x][player.getPositionInTiles().y];
	if (tileUnderPlayer->getType() == tt::TileTypes::WALL)
		player.undoMove();

	Tile *nextTile = nullptr;
	switch (player.getCurrentDirection())
	{
	case dt::Directions::LEFT:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x - 1][tileUnderPlayer->getPositionInTiles().y];
		break;
	case dt::Directions::RIGHT:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x + 1][tileUnderPlayer->getPositionInTiles().y];
		break;
	case dt::Directions::UP:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x][tileUnderPlayer->getPositionInTiles().y - 1];
		break;
	case dt::Directions::DOWN:
		nextTile = &tiles[tileUnderPlayer->getPositionInTiles().x][tileUnderPlayer->getPositionInTiles().y + 1];
		break;
	}

	if (tileUnderPlayer->getType() == tt::TileTypes::BOX)
	{
		if (nextTile->getType() == tt::TileTypes::NONE)
		{
			tileUnderPlayer->setType(tt::TileTypes::NONE);
			nextTile->setType(tt::TileTypes::BOX);
		}
		else if (nextTile->getType() == tt::TileTypes::FINISH)
		{
			tileUnderPlayer->setType(tt::TileTypes::NONE);
			nextTile->setType(tt::TileTypes::BOX_ON_FINISH);
		}
		else
			player.undoMove();
	}
	else if (tileUnderPlayer->getType() == tt::TileTypes::BOX_ON_FINISH)
	{
		if (nextTile->getType() == tt::TileTypes::NONE)
		{
			tileUnderPlayer->setType(tt::TileTypes::FINISH);
			nextTile->setType(tt::TileTypes::BOX);
		}
		else if (nextTile->getType() == tt::TileTypes::FINISH)
		{
			tileUnderPlayer->setType(tt::TileTypes::FINISH);
			nextTile->setType(tt::TileTypes::BOX_ON_FINISH);
		}
		else
			player.undoMove();
	}
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto const& column : tiles)
	{
		for (auto const& tile : column.second)
		{
			target.draw(tile.second);
		}
	} //iteration through std::map of std::map
	target.draw(player);
}