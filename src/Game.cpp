#include "Game.h"

Game::Game() : window(sf::VideoMode(800, 600), "Sokoban", sf::Style::Close | sf::Style::Titlebar),
	gameState(gs::GameStates::PLAY)
{
	window.setFramerateLimit(60);
}

void Game::start()
{
	while (gameState != gs::GameStates::EXIT)
	{
		processEvents();
		draw();
	}
	window.close();
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gameState = gs::GameStates::EXIT;
	}
}

void Game::draw()
{
	window.clear();
	window.display();
}