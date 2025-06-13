#include "../Header Files/Entity.h"

Entity::Entity(sf::Image img, std::string name, sf::FloatRect& rect):
	rect(rect)
{
	this->name = name;
	texture.loadFromImage(img);
}

sf::FloatRect Entity::getRect() const
{
	return rect;
}

std::string Entity::getName() const
{
	return name;
}