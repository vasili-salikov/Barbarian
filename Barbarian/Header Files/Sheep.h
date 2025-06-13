#pragma once
#include "DynamicEntity.h"
#include "Map/Level.h"

class Sheep : public DynamicEntity
{
public:
	bool isRunning, beee, inDanger;
	double timer;

	Sheep(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(double time) override;
	void draw(sf::RenderWindow& w);

	void setInDanger(bool inDanger);

private:
	void checkCollision(float Dx, float Dy);
};
