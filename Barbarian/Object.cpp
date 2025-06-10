#include "Object.h"

Object::Object(sf::Sprite sprite):
	sprite(sprite) {}

Object::Object(sf::Sprite sprite, std::string name, std::string type, sf::FloatRect rect) :
	sprite(sprite)
{
	this->name = name;
	this->type = type;
	this->rect = rect;
}

int Object::GetPropertyInt(std::string name) 
{
	return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
	return strtod(properties[name].c_str(), NULL);
}

//get name as a string
std::string Object::GetPropertyString(std::string name)
{
	return properties[name];
}