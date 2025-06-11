#pragma once
#include "Entity.h"
#include <map>
#include "Map/Level.h"

class Player: public Entity
{
public:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder, FusRoDah } STATE;
	std::map<std::string, bool> key;
	float speed;

	float dx, dy;
	int dir, health;//
	
	int drawX, drawY;//
	double stom,  timer, force;//
	bool  ATTACK, HURT, onLadder, fusrodah, alive, shot;//

	Player(sf::Image img, std::string name, Level &lvl, sf::FloatRect rect);
	void update(double time);
	void draw(sf::RenderWindow &w);

private:
	void checkCollision(float Dx, float Dy);
	void handleControls();
	void checkCollision(int horizontal);
	//void keyCheck(double time);
};
