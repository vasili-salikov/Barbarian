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

	// "rect" represents the physical bounds of the entity as defined in the map file.
	// It is passed and stored by reference to ensure that any changes made elsewhere 
	// (e.g. during collision handling or movement) are consistently reflected across the system.
	sf::FloatRect& rect;

	//AnimationManager anim;
	//std::vector<Object> objects; //map objects
public:
	Entity(sf::Image img, std::string name, sf::FloatRect& rect);

	virtual void update(double time) = 0;
	virtual void draw(sf::RenderWindow& w) = 0;

	sf::FloatRect getRect() const;// get position and size
	std::string getName() const; //get the entity name
};