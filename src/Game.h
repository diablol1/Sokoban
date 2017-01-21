#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.h"
class Game
{
public:
	Game();
	void start();
private:
	gs::GameStates gameState;
	sf::RenderWindow window;

	void processEvents();
	void draw();
};