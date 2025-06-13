#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map/Level.h"
#include "Skeleton.h"
#include "Sheep.h"
//#include <thread>
//#include <mutex>
//#include <fstream>
//#include <list>

class Game
{
private:
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;
	Level lvl;
	Player player;
	std::vector<Entity*> entities; //collection of object in the game to interact with

	//std::fstream fs;
	//sf::Event event;
	//std::mutex mtx;
	double time;

public:
	Game(std::string pathToMapFile, std::string pathToPlayerSprite);

	void startGame();
	void updateCameraPosition(double currentPlayerXposition, double currentPlayerYposition);
};
