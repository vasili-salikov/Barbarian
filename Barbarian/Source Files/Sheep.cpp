#include "../Header Files/Sheep.h"

Sheep::Sheep(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith) :
	DynamicEntity(img, name, rect, objectsToInteractWith)
{
	isRunning = false;
	beee = false;
	timer = 0;

	anim.create("stay", texture, { 0, 0 }, { 64, 64 }, 19, 0.003, { 64, 0 });
	anim.create("beee", texture, { 0, 62 }, { 64, 64 }, 9, 0.003, { 64, 0 });
	anim.create("run", texture, { 0, 128 }, { 64, 64 }, 5, 0.003, { 64, 0 });
}

void Sheep::update(float time)
{
	//std::cout << timer << std::endl;
	anim.set("stay");

	if (!isRunning || timer > 8500)
	{
		timer = 0;
		isRunning = false;
		dx = 0;
		//dir = 1;
		if (beee)
			anim.set("beee");
	}

	if (isRunning)
	{
		timer += time;
		anim.set("run");

		if (dir == 1)
		{
			dx = -0.03;
		}
		else
		{
			dx = 0.03;
		}
		
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

	int magicOffsetX = 112; // required x-offset for the sprite (rect width / 2 + sprite withd /2 (center)
	int magicOffsetY = +4; // required y-offset for the sprite

	anim.flip(dir);
	anim.setScale({ 0.5, 0.5 });
	anim.draw(w, { rect.position.x + magicOffsetX, rect.position.y + magicOffsetY });
}

void Sheep::checkCollision(float Dx, float Dy)
{
	beee = false;
	// Iterate over all the objects on the map
	for (const auto& obj : objects)
	{
		// Check if there colission with the player
		if (rect.findIntersection(obj->rect))
		{
			if (obj->name == "solidforenemy")
			{
				if (Dx > 0)
				{
					//position x = object position x - width of current object
					rect.position.x = obj->rect.position.x - rect.size.x;

					dir = 1;
					dx = -0.03;
				}
				if (Dx < 0)
				{
					//position x = object position x + width of current object
					rect.position.x = obj->rect.position.x + obj->rect.size.x;
					dir = 0;
					dx = 0.03;
				}
			}
			if (obj->name == "player")
			{
				beee = true;
				if (!isRunning)
				{
					if (rect.position.x + 112 > obj->rect.position.x)
					{
							dir = 1;
					}
					if (rect.position.x + 112 < obj->rect.position.x)
					{
							dir = 0;
					}
				}
			}
		}
	}
}

void Sheep::takeDamage(int amount)
{
	isRunning = true;
}