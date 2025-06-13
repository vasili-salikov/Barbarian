#include "../Header Files/Skeleton.h"

Skeleton::Skeleton(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect) :
	DynamicEntity(img, name, rect)
{
	isAttacking = false;
	isAlive = true;
	//objects.push_back(lvl.getObject("player"));
	//objects.push_back(lvl.getObjects("solidforenemy"));
	objects = lvl.getObjects("solidforenemy");
	
	anim.create("stay", texture, 0, 192, 64, 64, 4, 0.003, 64);
	anim.create("walk", texture, 0, 128, 64, 64, 12, 0.004, 64);
	anim.create("attack", texture, 0, 0, 64, 64, 13, 0.004, 64);
	anim.create("die", texture, 0, 64, 64, 64, 13, 0.004, 64);


	dir = 0;
	dx = 0.03;
}

void Skeleton::update(double time)
{
	anim.set("walk");
	if (isAttacking)
	{
		anim.set("attack");

		if (dir)
			dx = -0.005;
		else
			dx = 0.005;
	}
	else if (!isAlive)
	{
		dx = 0;
		anim.set("die");
	}

	rect.position.x += dx * time;
	checkCollision(dx, 0);


	anim.tick(time);
}

void Skeleton::checkCollision(float Dx, float Dy)
{
	// Iterate over all the objects on the map
	for (const auto& obj : objects)
	{
		// Check if there colission with the player
		if (rect.findIntersection(obj.rect))
		{
			if (obj.name == "solidforenemy")
			{
				if (Dx > 0)
				{
					//position x = object position x - width of current object
					rect.position.x = obj.rect.position.x - rect.size.x;
					
					dir = 1;
					dx = -0.03;
				}
				if (Dx < 0)
				{
					//position x = object position x + width of current object
					rect.position.x = obj.rect.position.x + obj.rect.size.x;
					dir = 0;
					dx = 0.03;
				}
			}
		}
	}
}

void Skeleton::draw(sf::RenderWindow& w)
{
#pragma region Make skeleton body visible(debug)
	//sf::RectangleShape skeletonRect(sf::Vector2f(rect.size.x, rect.size.y));
	//skeletonRect.setFillColor(sf::Color::Red);
	//skeletonRect.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
	//w.draw(skeletonRect);
#pragma endregion

	int magicOffsetX = -10; // required x-offset for player's sprite
	int magicOffsetY = -15; // required y-offset for player's sprite

	anim.flip(dir);
	anim.draw(w, rect.position.x + magicOffsetX, rect.position.y + magicOffsetY);
}