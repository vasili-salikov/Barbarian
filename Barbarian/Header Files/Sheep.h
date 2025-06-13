#pragma once
#include "DynamicEntity.h"
#include "Map/Level.h"

class Sheep : public DynamicEntity
{
public:
	bool isRunning, beee;

	Sheep(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect);
	void update(double time) override;
	void draw(sf::RenderWindow& w);

private:
	void checkCollision(float Dx, float Dy);
};
