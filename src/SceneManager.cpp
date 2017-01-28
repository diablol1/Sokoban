#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(TextureCache* _textureCache, const sf::Font& font) :
	textureCache(_textureCache),
	player(textureCache, Tile::Size, &movesCounter),
	pushesCounter("PUSHES: ", sf::Vector2f(600, 560), font),
	movesCounter("MOVES: ", sf::Vector2f(80, 560), font)
{
	
}

void SceneManager::init()
{
	changeLevelToNext();
}

void SceneManager::update(const sf::Event& event)
{
	if (processEvents(event))
	{
		detectCollisions();
		if (isEnd())
		{
			reset();
			changeLevelToNext(); 
		}
	}
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

void SceneManager::changeLevelToNext()
{
	static int currentLevel;
	currentLevel++;
	std::string filePath = "data/levels/level" + std::to_string(currentLevel) + ".lvl";
	if (!std::experimental::filesystem::exists(filePath))
	{
		currentLevel = 0;
		changeLevelToNext();
	}
	else
		loadLevelFromFile(filePath);
}

bool SceneManager::processEvents(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			player.move(dt::Directions::LEFT);
			return true;
		case sf::Keyboard::Right:
			player.move(dt::Directions::RIGHT);
			return true;
		case sf::Keyboard::Up:
			player.move(dt::Directions::UP);
			return true;
		case sf::Keyboard::Down:
			player.move(dt::Directions::DOWN);
			return true;
		}
	}
	return false;
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
			pushesCounter++;
		}
		else if (nextTile->getType() == tt::TileTypes::FINISH)
		{
			tileUnderPlayer->setType(tt::TileTypes::NONE);
			nextTile->setType(tt::TileTypes::BOX_ON_FINISH);
			pushesCounter++;
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
			pushesCounter++;
		}
		else if (nextTile->getType() == tt::TileTypes::FINISH)
		{
			tileUnderPlayer->setType(tt::TileTypes::FINISH);
			nextTile->setType(tt::TileTypes::BOX_ON_FINISH);
			pushesCounter++;
		}
		else
			player.undoMove();
	}
}

bool SceneManager::isEnd()
{
	for (auto const& column : tiles)
	{
		for (auto const& tile : column.second)
		{
			if (tile.second.getType() == tt::TileTypes::FINISH)
				return false;
		}
	}
	return true;
}

void SceneManager::reset()
{
	tiles.clear();
	movesCounter.reset();
	pushesCounter.reset();
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
	
	target.draw(movesCounter);
	target.draw(pushesCounter);
}
