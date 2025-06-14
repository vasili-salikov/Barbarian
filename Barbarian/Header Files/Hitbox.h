#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Hitbox 
{
private:
	sf::FloatRect bounds;   // rect of hitbox
	sf::Vector2f velocity; // speed and direction (simanteniously)
	float lifetime;
	bool expired;
	float elapsed = 0.0f;
	float damage;
	Entity* owner;

public:
	Hitbox(sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity, float damage, Entity* owner, float lifetime = 0);

	void setVelocity(sf::Vector2f newVelocity);
	void setExpired(bool expired);
	void update(float time);
	bool isExpired() const;
	sf::FloatRect getBounds() const;
	float getDamage() const;
	Entity* getOwner() const;
};
