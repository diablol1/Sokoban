#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "SceneManager.h"
#include "TextureCache.h"

class Game
{
public:
	Game();
	void start();
private:

	gs::GameStates gameState;
	sf::RenderWindow window;

	TextureCache textureCache;

	SceneManager sceneManager;

	void processEvents();
	void render();
};
