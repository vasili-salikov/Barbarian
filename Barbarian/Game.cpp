#include "Game.h"

Game::Game() 
{
	//todo initialisation
	window.create(sf::VideoMode({ 1280, 720 }), "Barbarian");

}

Game::~Game()
{
	//todo dispose
	window.close();
}

void Game::startGame()
{
	// run the program as long as the window is open
	while (window.isOpen())
	{
		window.clear();
		// check all the window's events that were triggered since the last iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPressed->scancode)
				{
					case sf::Keyboard::Scancode::Escape:
						window.close();
				}
			}
		}

		window.display();
	}
}
