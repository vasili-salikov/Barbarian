#include "../../Header Files/Map/Object.h"

Object::Object(sf::Sprite sprite):
	sprite(sprite) {}

Object::Object(sf::Sprite sprite, std::string name, std::string type, sf::FloatRect rect) :
	sprite(sprite)
{
	this->name = name;
	this->type = type;
	this->rect = rect;
}

int Object::getPropertyInt(std::string name) 
{
	return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}

//get name as a string
std::string Object::getPropertyString(std::string name)
{
	return properties[name];
}