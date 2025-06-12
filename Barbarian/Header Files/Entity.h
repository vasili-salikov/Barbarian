#pragma once
#include <SFML/Graphics.hpp>
#include "Animation/AnimationManager.h"
#include "Map/Object.h"

class Entity
{
public:
	std::vector<Object> objects; //map objects
	sf::FloatRect rect;
	AnimationManager anim;
	sf::Texture texture;
	std::string name;

	Entity(sf::Image img, std::string name, sf::FloatRect rect);
	sf::FloatRect getRect() const;// get position and size
};