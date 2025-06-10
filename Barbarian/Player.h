#pragma once
#include "Entity.h"
#include <map>
#include "Level.h"

class Player: public Entity
{
public:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder, FusRoDah } STATE;

	std::map<std::string, bool> key;

	Player(sf::Image& img, std::string name, Level &lvl, float x, float y, int w, int h);
	void update(double &time);
	void draw(sf::RenderWindow &w);
};
