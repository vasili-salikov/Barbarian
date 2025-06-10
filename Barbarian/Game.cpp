#include "Game.h"


Game::Game() 
{
	//todo initialisation
	window.create(sf::VideoMode({ 512, 288 }), "Barbarian");
	window.setSize(sf::Vector2u(1360, 768));
	window.setPosition(sf::Vector2i(500, 200)); //temporary fix for centre
	window.setFramerateLimit(60); //speed fix
}

Game::~Game()
{
	//todo dispose
	window.close();
}

void Game::startGame()
{
	Level lvl;
	lvl.LoadFromFile("lvl1.tmx");

	sf::Image heroImg;
	heroImg.loadFromFile("resources/sprites/barbarian.png");

	Player player = Player(heroImg, "Player", lvl, 0, 0, 32, 32);

	

	// run the program as long as the window is open
	while (window.isOpen())
	{
		//speed of the game (bing to SFML time)
		/*time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 200;*/
		time = clock.restart().asSeconds();

		player.update(time);
		window.clear();
		// check all the window's events that were triggered since the last iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch (keyPressed->scancode)
				{
					case sf::Keyboard::Scancode::Escape:
						window.close();
						break;
					case sf::Keyboard::Scancode::Up:
						player.key["Up"] = true;
						break;
					case sf::Keyboard::Scancode::Right:
						player.key["Right"] = true;
						break;
					case sf::Keyboard::Scancode::Left:
						player.key["Left"] = true;
						break;
					case sf::Keyboard::Scancode::Down:
						player.key["Down"] = true;
						break;
					case sf::Keyboard::Scancode::Space:
						player.key["Space"] = true;
						break;
				}
			}
		}
		lvl.Draw(window);
		player.draw(window);
		window.display();
	}
}
