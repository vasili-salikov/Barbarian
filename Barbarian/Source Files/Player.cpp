#include "../Header Files/Player.h"
#include <iostream>

Player::Player(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect) : Entity(img, name, rect)
{
	//initialise objects collection with all the objects from the map
	health = 100;
	STATE = stay;
	stom = 45;
	force = 0;
	fusrodah = false;

	objects = lvl.GetAllObjects();
	onLadder = false;

	//list of animation declaration 
	anim.create("stay", texture, 0, 4, 32, 32, 5, 0.003, 32);
	anim.create("walk", texture, 0, 36, 32, 32, 8, 0.007, 32);
	anim.create("attack", texture, 0, 68, 32, 32, 7, 0.005, 32);
	anim.create("hurt", texture, 0, 100, 32, 32, 3, 0.0025, 32);
	anim.create("down", texture, 128, 144, 32, 32, 1, 0.02, 32);
	anim.create("crawl", texture, 96, 144, 32, 32, 4, 0.005, 32);
	anim.create("jump", texture, 0, 36, 32, 32, 3, 0.001, 32);
	anim.create("die", texture, 0, 132, 32, 32, 7, 0.002, 32);
	anim.create("ladder", texture, 0, 164, 32, 28, 2, 0.003, 32);
	anim.create("FusRoDah", texture, 0, 196, 32, 28, 4, 0.002, 32);
}

void Player::handleControls()
{
	bool topCollision = false;

	if (key["Left"] || key["Right"])
	{
		
		dir = (int)key["Left"]; //if the left key is pressed than direction is 1 otherwise 0
		
		dx = dir ? -0.08 : 0.08; //if direction left dx is negative and vice versa
		
		if (STATE == down || STATE == crawl)
		{
			STATE = crawl;
			dx = dir ? -0.03 : 0.03;
		}	
		if (onGround && STATE == stay)
			STATE = walk;
	}
	if (!key["Right"] && !key["Left"])
	{
		dx = 0;
		if (STATE == walk)
			STATE = stay;
		else if (STATE == crawl || STATE == down)
		{
			STATE = down;
		}
	}
	if (key["Up"] || key["Down"])
	{
		if (onGround)
		{
			if (key["Up"] && (STATE != down && STATE != crawl)) // Can jump only when on the ground and not sitting or crawling
			{
				onGround = false;
				STATE = jump;
				dy = -0.2;
			}
			else
			{
				sitDown(); // Shrink model for sitting/crawling pose

				if (STATE  != crawl)
					STATE = down;
			}
		}
		else if (onLadder)
		{
			// If crawling or falling while sitting, immediately switch to standing
			if (STATE == down || STATE == crawl)
				standUp();

			STATE = ladder;
			dy = key["Up"] ? -0.025 : 0.025;
			anim.set("ladder");
			anim.play();
		}
	}
	if (!key["Down"] && (STATE == down || STATE == crawl))
	{
		// Check if there's space above to stand up (temporary solution — should be improved)

		//imagine we are standing
		sf::FloatRect tempRect = rect;
		tempRect.size.y = 24;
		tempRect.position.y -= 12;
		
		//check collision
		for (int i = 0; i < objects.size(); i++)
			if (tempRect.findIntersection(objects[i].rect))
			{
				if (objects[i].name == "solid")
				{
					topCollision = true;

					if (dx != 0)
						STATE = crawl;
					else
						STATE = down;
				}
			}

		//if no collision - stand up
		if (!topCollision)
		{
			STATE = stay;
			standUp();
		}
	}
	if (!key["Up"] && !key["Down"]) //if both are not pressed
	{
		if (onLadder && dy != 0)
		{
			STATE = ladder;
			dy = 0;
			anim.set("ladder"); // <- Fixes transition with correct animation pause 
			anim.pause();		// from jump to ladder when the player falls onto a ladder
		}
		if (onGround && dx == 0 && !topCollision)
		{
			STATE = stay;
		}		
	}
	if (key["Space"])
	{
		STATE = attack;
	}
}

void Player::update(double time)
{
	handleControls();

	if (STATE != ladder) // For the ladder state, animation is handled separately in the handleControls method
	{
		if (anim.getCurrentAnimationName() != getCurrentStateAsString()) // change animation if needed
		{
			anim.set(getCurrentStateAsString());
			anim.play();
		}	
	}

	onGround = false; //permanent falling until collision
	//move x
	rect.position.x += dx * time;
	//check colission by x
	checkCollision(dx, 0);

	//move y
	rect.position.y += dy * time;
	//check collision by y;
	onLadder = false;
	checkCollision(0, dy);


	if (health == 0)
	{
		alive = false;
	}

	if(!onLadder)
		dy = dy + 0.0003 * time; //constant gravity if is not on ladder

	anim.tick(time);
	key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;
}

void Player::draw(sf::RenderWindow& w)
{
	//debug //see player body
	sf::RectangleShape playerRect(sf::Vector2f(rect.size.x, rect.size.y));
	playerRect.setFillColor(sf::Color::Green);
	playerRect.setPosition(sf::Vector2f(rect.position.x, rect.position.y));

	//std::cout << "width: " << playerRect.getSize().x << " height:" << playerRect.getSize().y <<std::endl;
	w.draw(playerRect);
	int magicOffsetX = -10; //fix it one day
	int magicOffsetY = -2; //fix it one day
	//


	anim.flip(dir);
	anim.draw(w, rect.position.x + magicOffsetX, rect.position.y + magicOffsetY);
}

void Player::checkCollision(float Dx, float Dy)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (rect.findIntersection(objects[i].rect).has_value())
		{
			if (objects[i].name == "solid")
			{
				//std::cout <<"COLLISION" <<std::endl;
				if (Dy > 0)
				{
					//position y = object position y - height of current object
					rect.position.y = objects[i].rect.position.y - rect.size.y;
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					//position y = object position y + height of current object
					rect.position.y = objects[i].rect.position.y + objects[i].rect.size.y;
					dy = 0;
				}
				if (Dx > 0)
				{
					//position x = object position x - width of current object
					rect.position.x = objects[i].rect.position.x - rect.size.x;
					dx = 0;
				}
				if (Dx < 0)
				{
					//position x = object position x + width of current object
					rect.position.x = objects[i].rect.position.x + objects[i].rect.size.x;
					dx = 0;
				}
			}
			if (objects[i].name == "ladder")
			{
				//std::cout << "COLLISION" << std::endl;
				onLadder = true;
			}
			if (objects[i].name == "pike")
			{
				health = 0;
				dy = 0;
				onGround = true;
			}
		}
	}
}

std::string Player::getCurrentStateAsString()
{
	switch (STATE) 
	{
		case stay: return "stay";
		case walk: return "walk";
		case jump: return "jump";
		case down: return "down";
		case attack: return "attack";
		case ladder: return "ladder";
		case crawl: return "crawl";
		default:     return "stay"; 
	}
}

// Switch hero to standing state (restore full height)
void Player::standUp()
{
	rect.size.y = 24;
	rect.position.y -= 12;
}

// Switch hero to sitting state (shrink model)
void Player::sitDown()
{
	rect.size.y = 12;
	//todo manage get rid of jump when trying to sit
}

