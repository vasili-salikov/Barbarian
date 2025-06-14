#pragma once
#include "DynamicEntity.h"
#include "IDamageable.h"
#include "Map/Level.h"

class Sheep : public DynamicEntity, public IDamageable
{
public:
	bool isRunning, beee;
	double timer;

	Sheep(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(float time) override;
	void draw(sf::RenderWindow& w);
	void takeDamage(int amount) override;

private:
	void checkCollision(float Dx, float Dy);
};
