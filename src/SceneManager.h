#pragma once

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"

class SceneManager : public sf::Drawable
{
public:
	SceneManager(TextureCache* _textureCache);

	void loadLevelFromFile(const std::string& filename);
	void processEvents(const sf::Event& event);
private:
	const int TileSize = 64;
	TextureCache* textureCache;

	sf::Sprite player;
	std::vector<sf::Sprite> walls;
	std::vector<sf::Sprite> boxes;
	std::vector<sf::Sprite> finishPoints;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};