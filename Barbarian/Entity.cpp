#include "Entity.h"

Entity::Entity(sf::Image& img, std::string name, float x, float y, int w, int h)
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

sf::FloatRect Entity::getRect() const
{
	return sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(w, h));
}