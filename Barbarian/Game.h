#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <thread>
#include <mutex>
#include <fstream>
#include "Player.h"
#include "Level.h"

class Game
{
private:
	std::fstream fs;
	sf::Clock clock;
	sf::RenderWindow window;
	//sf::Event event;
	std::mutex mtx;
	double time;

public:
	Game();
	~Game();
	void startGame();
};
