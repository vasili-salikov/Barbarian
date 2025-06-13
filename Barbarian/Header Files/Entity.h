#pragma once
#include <SFML/Graphics.hpp>
#include "Animation/AnimationManager.h"
#include "Map/Object.h"

//an abstract class for everything on the map
class Entity
{
protected:
	std::string name;
	sf::Texture texture;
	sf::FloatRect rect;
	//AnimationManager anim;
	//std::vector<Object> objects; //map objects
public:
	Entity(sf::Image img, std::string name, sf::FloatRect rect);

	virtual void update(double time) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;

	sf::FloatRect getRect() const;// get position and size
	std::string getName() const; //get the entity name
};