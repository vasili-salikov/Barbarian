#pragma once
#include <iostream>
#include "DynamicEntity.h"
#include "Map/Level.h"

class Skeleton : public DynamicEntity
{
public:
	//std::vector<Object>* testObjects; // map objects to interact with

	bool isAttacking, isAlive;
	Skeleton(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(double time) override;
	void draw(sf::RenderWindow& w);

private:
	void checkCollision(float Dx, float Dy);
};