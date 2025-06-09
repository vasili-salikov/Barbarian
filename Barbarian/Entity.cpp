#include "Entity.h"

Entity::Entity(sf::Image& img, float x, float y, int w, int h, std::string name)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->name = name;

	health = 100;
	dx = dy = 0;
	onGround = isMoving = false;

	texture.loadFromImage(img);
}