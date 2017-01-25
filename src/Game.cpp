#include "Game.h" 

Game::Game() : window(sf::VideoMode(800, 600), "Sokoban", sf::Style::Close | sf::Style::Titlebar),
	gameState(gs::GameStates::PLAY),
	sceneManager(&textureCache)
{
	Tile::textureCache = &textureCache;

	window.setFramerateLimit(60);
	sceneManager.loadLevelFromFile("data/levels/level1.lvl");
}

void Game::start()
{
	while (gameState != gs::GameStates::EXIT)
	{
		processEvents();
		update();
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
			sceneManager.processEvents(event);
	}
}

void Game::update()
{
	sceneManager.detectCollisions();
}

void Game::render()
{
	window.clear();
	window.draw(sceneManager);
	window.display();
}