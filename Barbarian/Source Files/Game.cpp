#include "../Header Files/Game.h"


Game::Game(std::string pathToMapFile, std::string pathToPlayerSprite) 
	: lvl(pathToMapFile), player(sf::Image(pathToPlayerSprite), "Player", lvl, lvl.GetObject("player").rect)
{
	view = sf::View(sf::FloatRect(sf::Vector2f(0, 100), sf::Vector2f(512, 288)));

	window.create(sf::VideoMode({ 512, 288 }), "Barbarian"); // 16:9 ratio small picture (according to tiles size)
	window.setSize(sf::Vector2u(1536, 864)); // image scale to size of modern monitor
	window.setPosition(sf::Vector2i(500, 200)); // temporary fix for beign in the centre of the screen

	window.setFramerateLimit(60); //speed fix
	window.setView(view);
}

void Game::startGame()
{
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// speed of the game (bing to SFML time)
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600; //Normal
		//time = time / 4500; //slowmo

		window.clear();
		lvl.Draw(window);
		// update player and camera
		player.update(time);
		updateCameraPosition(player.getRect().position.x, player.getRect().position.y); // Move the camera to follow the player
		window.setView(view); // refresh camera

		while (const std::optional event = window.pollEvent())
		{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}
		}

		// Real-time input polling: required for holding keys (e.g. continuous movement).
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) player.key["Up"] = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) player.key["Down"] = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) player.key["Left"] = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) player.key["Right"] = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) player.key["Space"] = true;

		
		player.draw(window);
		window.display();
	}
}

void Game::updateCameraPosition(double currentPlayerXposition, double currentPlayerYposition)
{
	const int cameraOffsetX = 100;

	// map boundary constants
	const int leftBoundary = 256;
	const int rightBoundary1 = 1016;
	const int rightBoundary2 = 1419;
	const int upperZone = 370;
	const int lowerZone = 100;
	const int centerY1 = 232;
	const int centerY2 = 490;

	double camX = currentPlayerXposition + cameraOffsetX;
	double camY = currentPlayerYposition;

	// clamp x to minimum boundary
	if (camX < leftBoundary)
		camX = leftBoundary;

	// y logic based on vertical zones
	if (camY > lowerZone && camY < upperZone)
	{
		camY = centerY1;
		if (camX > rightBoundary1)
			camX = rightBoundary1;
	}
	else if (camY > upperZone)
	{
		camY = centerY2;
		if (camX > rightBoundary2)
			camX = rightBoundary2;
	}

	view.setCenter(sf::Vector2f(camX, camY));
}