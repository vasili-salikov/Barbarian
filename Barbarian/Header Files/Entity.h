#pragma once
#include <SFML/Graphics.hpp>
#include "Animation/AnimationManager.h"
#include "Map/Object.h"

class Entity
{
public:
	std::vector<Object> objects; //map objects
	/*float x, y, dx, dy;
	int w, h, dir, health;*/
	sf::FloatRect rect;
	bool isMoving, onGround;

	sf::Texture texture;
	std::string name;

	AnimationManager anim;

	Entity(sf::Image img, std::string name, sf::FloatRect rect);

	//get entity Rect (position and size)
	sf::FloatRect getRect() const;
};