#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "Object.h"

class Entity
{
public:
	std::vector<Object> objects; //map objects
	float x, y, dx, dy;
	int w, h, dir, health;
	bool isMoving, onGround;

	sf::Texture texture;
	sf::String name;

	AnimationManager animManager;

	Entity(sf::Image& img, std::string name, float x, float y, int w, int h);

	//get entity Rect (position and size)
	sf::FloatRect getRect() const;
};