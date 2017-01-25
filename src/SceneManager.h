#pragma once

#include <string>
#include <fstream>
#include <map>

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"
#include "Tile.h"
#include "Player.h"

class SceneManager : public sf::Drawable
{
public:
	SceneManager(TextureCache* _textureCache);

	void loadLevelFromFile(const std::string& filename);
	void processEvents(const sf::Event& event);
	void detectCollisions();
private:
	TextureCache* textureCache;

	std::map<unsigned int, std::map<unsigned int, Tile>> tiles;

	Player player;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};