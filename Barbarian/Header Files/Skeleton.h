#pragma once
#include <iostream>
#include "DynamicEntity.h"
#include "Map/Level.h"

class Skeleton : public DynamicEntity
{
public:
	bool isAttacking, isAlive;
	Skeleton(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect);
	void update(double time) override;
	void draw(sf::RenderWindow& w);

private:
	void checkCollision(float Dx, float Dy);
};