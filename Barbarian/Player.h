#pragma once
#include "Entity.h"
#include <map>

class Player: public Entity
{
public:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder, FusRoDah } STATE;

	std::map<std::string, bool> key;

	Player(sf::Image& img, float x, float y, int w, int h, std::string name);
	void update(double &time);
	void draw(sf::RenderWindow &w);
};
