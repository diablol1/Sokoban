#pragma once

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"
#include "Tile.h"
#include <map>

class SceneManager : public sf::Drawable
{
public:
	SceneManager(TextureCache* _textureCache);

	void loadLevelFromFile(const std::string& filename);
	void processEvents(const sf::Event& event);
private:
	const int TileSize = 64;
	TextureCache* textureCache;

	std::map<unsigned int, std::map<unsigned int, Tile>> tiles;

	sf::Sprite player;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};