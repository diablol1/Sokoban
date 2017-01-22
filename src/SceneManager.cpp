#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(TextureCache* _textureCache) : textureCache(_textureCache)
{
	player.setTexture(_textureCache->get("player"));
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
		std::string str;
		file >> str;

		sf::Sprite tileToAdd;
		tileToAdd.setPosition(loadCounter.x  * TileSize, loadCounter.y * TileSize);
		switch (std::stoi(str))
		{
		case tt::TileTypes::WALL:
			tileToAdd.setTexture(textureCache->get("wall"));
			walls.push_back(tileToAdd);
			break;
		case tt::TileTypes::BOX:
			tileToAdd.setTexture(textureCache->get("box"));
			boxes.push_back(tileToAdd);
			break;
		case tt::TileTypes::FINISH:
			tileToAdd.setTexture(textureCache->get("finishPoint"));
			finishPoints.push_back(tileToAdd);
			break;
		}

		loadCounter.x++;
		if (file.peek() == '\n')
		{
			loadCounter.x = 0;
			loadCounter.y++;
		}
	}
}

void SceneManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(player);
	for (auto const& wall : walls)
	{
		target.draw(wall);
	}
	for (auto const& box : boxes)
	{
		target.draw(box);
	}
	for (auto const& finishPoint : finishPoints)
	{
		target.draw(finishPoint);
	}
}