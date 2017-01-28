#include "Game.h" 

Game::Game() : window(sf::VideoMode(800, 600), "Sokoban", sf::Style::Close | sf::Style::Titlebar),
	gameState(gs::GameStates::PLAY),
	sceneManager(&textureCache, font)
{
	window.setFramerateLimit(60);

	font.loadFromFile("data/font.ttf");
	Tile::textureCache = &textureCache;

	sceneManager.init();
}

void Game::start()
{
	while (gameState != gs::GameStates::EXIT)
	{
		processEvents();
		render();
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
		else if (gameState == gs::GameStates::PLAY)
			sceneManager.update(event);
	}
}

void Game::render()
{
	window.clear();
	window.draw(sceneManager);
	window.display();
}