#pragma once
#include <iostream>
#include "DynamicEntity.h"
#include "IDamageable.h"
#include "Map/Level.h"

class Skeleton : public DynamicEntity, public IDamageable
{
public:
	//std::vector<Object>* testObjects; // map objects to interact with

	bool isAttacking, isAlive;
	Skeleton(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(float time) override;
	void draw(sf::RenderWindow& w) override;
	void takeDamage(int amount) override;

private:
	int health;
	void checkCollision(float Dx, float Dy);
};