#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(TextureCache* _textureCache) : textureCache(_textureCache)
{
	player.setTexture(_textureCache->get("playerRight"));
}

void SceneManager::loadLevelFromFile(const std::string & filename)
{
	std::ifstream file(filename);

	std::string x, y;
	file >> x >> y;
	player.setPosition(std::stoi(x) * TileSize, std::stoi(y) * TileSize);

	sf::Vector2i loadCounter = sf::Vector2i(0, 0);
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
			player.move(-TileSize, 0);
			player.setTexture(textureCache->get("playerLeft"));
			break;
		case sf::Keyboard::Right:
			player.move(TileSize, 0);
			player.setTexture(textureCache->get("playerRight"));
			break;
		case sf::Keyboard::Up:
			player.move(0, -TileSize);
			player.setTexture(textureCache->get("playerUp"));
			break;
		case sf::Keyboard::Down:
			player.move(0, TileSize);
			player.setTexture(textureCache->get("playerDown"));
			break;
		}
	}
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(player);

	for (auto const& column : tiles)
	{
		for (auto const& tile : column.second)
		{
			target.draw(tile.second);
		}
	}//iteration through std::map of std::map
}