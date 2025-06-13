#include "../Header Files/Sheep.h"

Sheep::Sheep(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect) :
	DynamicEntity(img, name, rect)
{
	isRunning = true;
	beee = false;
	objects = lvl.getObjects("solidforenemy"); //temporary

	anim.create("stay", texture, 0, 0, 64, 64, 19, 0.003, 64, 0);
	anim.create("beee", texture, 0, 62, 64, 64, 9, 0.003, 64, 0);
	anim.create("run", texture, 0, 128, 64, 64, 5, 0.003, 64, 0);

	dir = 1;
	dx = -0.03;
}

void Sheep::update(double time)
{
	anim.set("stay");
	if (!isRunning)
	{
		dx = 0;
		if (beee)
			anim.set("beee");
	}

	if (isRunning)
	{
		anim.set("run");
	}


	rect.position.x += dx * time;
	checkCollision(dx, 0);
	anim.tick(time);
}

void Sheep::draw(sf::RenderWindow& w)
{
#pragma region Make body visible(debug)
	//sf::RectangleShape bodyRect(sf::Vector2f(rect.size.x, rect.size.y));
	//bodyRect.setFillColor(sf::Color::Blue);
	//bodyRect.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
	//w.draw(bodyRect);
#pragma endregion
	int magicOffsetX = 0; // required x-offset for player's sprite
	int magicOffsetY = +4; // required y-offset for player's sprite

	anim.flip(dir);
	anim.setScale(sf::Vector2f(0.5, 0.5));
	anim.draw(w, rect.position.x + magicOffsetX, rect.position.y + magicOffsetY);
}

void Sheep::checkCollision(float Dx, float Dy)
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