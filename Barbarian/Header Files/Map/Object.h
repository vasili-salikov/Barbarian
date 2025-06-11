#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <memory> //for unique_ptr

struct Object
{
	int GetPropertyInt(std::string name);
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);

	std::string name;
	std::string type;
	sf::FloatRect rect;
	std::map<std::string, std::string> properties;

	sf::Sprite sprite;
	
	Object(sf::Sprite sprite);
	Object(sf::Sprite sprite, std::string name, std::string type, sf::FloatRect rect);
};