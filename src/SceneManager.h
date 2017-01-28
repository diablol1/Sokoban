#pragma once

#include <string>
#include <fstream>
#include <map>
#include <experimental/filesystem>

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "TextureCache.h"
#include "Tile.h"
#include "Player.h"
#include "Counter.h"

class SceneManager : public sf::Drawable
{
public:	
	SceneManager(TextureCache* _textureCache, const sf::Font& font);

	void init();
	void update(const sf::Event& event);
private:
	TextureCache* textureCache;

	std::map<unsigned int, std::map<unsigned int, Tile>> tiles;

	Player player;

	Counter pushesCounter;
	Counter movesCounter;

	void loadLevelFromFile(const std::string& filename);

	bool processEvents(const sf::Event& event);
	void detectCollisions();
	bool isEnd();
	void reset();

	void changeLevelToNext();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};