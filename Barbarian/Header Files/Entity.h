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

	bool isMoving, onGround;

	Entity(sf::Image img, std::string name, sf::FloatRect rect);
	// get position and size
	sf::FloatRect getRect() const;
};