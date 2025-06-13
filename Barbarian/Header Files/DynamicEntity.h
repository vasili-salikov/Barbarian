#pragma once
#include "Entity.h"

class DynamicEntity : public Entity
{
protected:
	AnimationManager anim;	// Manage animation
	std::vector<Object*> objects; // map objects to interact with
	float dx, dy;
	int dir;

public:
	DynamicEntity(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	virtual void update(double time) override = 0;
	virtual void draw(sf::RenderWindow& w) = 0;
};