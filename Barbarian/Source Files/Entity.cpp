#include "../Header Files/Entity.h"

Entity::Entity(sf::Image img, std::string name, sf::FloatRect rect)
{
	this->name = name;
	this->rect = rect;

	texture.loadFromImage(img);
}

sf::FloatRect Entity::getRect() const
{
	return rect;
}