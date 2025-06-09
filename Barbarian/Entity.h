#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationManager.h"

class Entity
{
public:
	float x, y, dx, dy;
	int w, h, dir, health;
	bool isMoving, onGround;

	sf::Texture texture;
	sf::String name;

	AnimationManager animManager;

	Entity(sf::Image& img, float x, float y, int w, int h, std::string name);
};