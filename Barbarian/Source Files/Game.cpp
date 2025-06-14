#include "../Header Files/Game.h"

Game::Game(std::string pathToMapFile, std::string pathToPlayerSprite) :
	lvl(pathToMapFile),
	player(sf::Image(pathToPlayerSprite), "Player", lvl.getObjectByReference("player")->rect, lvl.getAllObjectsByReference())
{
	view = sf::View(sf::FloatRect({ 0, 100 }, { 512, 288 }));

	window.create(sf::VideoMode({ 512, 288 }), "Barbarian"); // 16:9 ratio small picture (according to tiles size)
	window.setSize({ 1536, 864 }); // image scale to size of modern monitor
	window.setPosition({ 500, 200 }); // temporary fix for beign in the centre of the screen

	window.setFramerateLimit(60); //speed fix
	window.setView(view);
}

void Game::startGame()
{
	std::vector<Object*> entitiesForEnemy; // entities for enemies to interact with (dynamically)
	
	entitiesForEnemy.push_back(lvl.getObjectByReference("player"));
	for (auto& obj : lvl.getObjectsByReference("solidforenemy"))
		entitiesForEnemy.push_back(obj);
	

	entities.push_back(new Sheep(sf::Image("resources/sprites/sheep.png"), "sheep", lvl.getObjectByReference("sheep")->rect, entitiesForEnemy));
	for (auto& enemy : lvl.getObjectsByReference("enemy"))
	{
		entities.push_back(new Skeleton(sf::Image("resources/sprites/skeleton.png"),"enemy",enemy->rect, entitiesForEnemy));
	}

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// speed of the game (bing to SFML time)
		time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 600; //Normal
		//time = time / 4500; //slowmo

		window.clear();
		updateCameraPosition(player.getRect().position.x, player.getRect().position.y); // Move the camera to follow the player
		window.setView(view); // refresh camera

		//auto playerRect = lvl.getObject("player").rect;
		//std::cout << "x: " << playerRect.position.x << " ,y:" << playerRect.position.y << std::endl;

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


		lvl.draw(window);
		//update and draw all entities
		for (auto& entity : entities)
		{
			entity->update(time);
			entity->draw(window);
		}

		player.update(time);
		if (!player.getHitboxes().empty())
		{
			for (auto h : player.getHitboxes())
			{
				for (auto& entity : entities)
				{
					
					if (h.getBounds().findIntersection(entity->getRect()))
					{
						
						IDamageable* damageable = dynamic_cast<IDamageable*>(entity);
						if(damageable)
						{
							//todo fix permanent damage
							damageable->takeDamage(h.getDamage());
							h.setExpired(true);
							break;
						}
					}
				}
			}
		}
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