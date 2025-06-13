#include "../Header Files/DynamicEntity.h"

DynamicEntity::DynamicEntity(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith) :
	Entity(img, name, rect)
{
	this->objects = objectsToInteractWith;
}