#include "../Header Files/Player.h"
#include <iostream>

Player::Player(sf::Image img, std::string name, Level& lvl, sf::FloatRect rect) : 
	DynamicEntity(img, name, rect),
	testRect(lvl.getObjectByReference("player").rect)
{
	//this->testObj = lvl.getObjectByReference("player");
	//rect = testObj->rect;
	//testRect = &lvl.getObjectByReference("player").rect;
	//this->rect = lvl.getObjectByReference("player").rect;

	STATE = stay;
	isAttacking = false;
	onGround = true;
	onLadder = false;
	//initialise objects collection with all the objects from the map
	health = 100;
	isAlive = true;
	objects = lvl.getAllObjects();

	//list of animation declaration 
	anim.create("stay", texture, 0, 4, 32, 32, 5, 0.003, 32);
	anim.create("walk", texture, 0, 36, 32, 32, 8, 0.007, 32);
	anim.create("attack", texture, 0, 68, 32, 32, 7, 0.01, 32);
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
	if (isAlive)
	{
		handleHorizontalMovement();
		handleVerticalMovement();
		handleLadderMovement();
		handleStandUpTransition();
		handleAttack();
	}
}

void Player::update(double time) 
{
	handleControls();

	if (isAttacking)
	{
		STATE = attack;
		if (anim.getCurrentFrame() > 6)
		{
			//std::cout << "isAttacking = false" << std::endl;
			isAttacking = false;
			anim.restart();
		}
	}
	else if (!isAlive)
	{
		if (anim.getCurrentFrame() > 6)
			anim.pause();
		
	}
	
	if (anim.getCurrentAnimationName() != getCurrentStateAsString()) // change animation if the state was changed
	{
		anim.set(getCurrentStateAsString());
		anim.play();
	}

	onLadder = false;
	onGround = false; //permanent falling until collision
	rect.position.x += dx * time; //move x
	checkCollision(dx, 0);//check colission by x

	rect.position.y += dy * time;//move y
	checkCollision(0, dy); //check collision by y;

	if (health == 0)
	{
		isAlive = false;
		STATE = die;
		dx = dy = 0;
	}

	if (!onLadder && isAlive)
		dy = dy + 0.0003 * time; //constant gravity if is not on ladder

	anim.tick(time);
	key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;

	//testObj->rect.position.x = rect.position.x;
	//testObj->rect.position.y = rect.position.y;
	testRect.position.x = rect.position.x;
	testRect.position.y = rect.position.y;
}

void Player::draw(sf::RenderWindow& w)
{
#pragma region Make player body visible(debug)
	//sf::RectangleShape playerRect(sf::Vector2f(rect.size.x, rect.size.y));
	//playerRect.setFillColor(sf::Color::Green);
	//playerRect.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
	//w.draw(playerRect);
#pragma endregion

	int magicOffsetX = -10; // required x-offset for player's sprite
	int magicOffsetY = -2; // required y-offset for player's sprite

	anim.flip(dir);
	anim.draw(w, rect.position.x + magicOffsetX, rect.position.y + magicOffsetY);
}

void Player::checkCollision(float Dx, float Dy)
{
	// Iterate over all the objects on the map
	for (const auto& obj : objects)
	{
		// Check if there colission with the player
		if (rect.findIntersection(obj.rect))
		{
			if (obj.name == "solid")
			{
				if (Dy > 0)
				{
					//position y = object position y - height of current object
					rect.position.y = obj.rect.position.y - rect.size.y;
					dy = 0;
					onGround = true;
				}
				if (Dy < 0)
				{
					//position y = object position y + height of current object
					rect.position.y = obj.rect.position.y + obj.rect.size.y;
					dy = 0;
				}
				if (Dx > 0)
				{
					//position x = object position x - width of current object
					rect.position.x = obj.rect.position.x - rect.size.x;
					dx = 0;
				}
				if (Dx < 0)
				{
					//position x = object position x + width of current object
					rect.position.x = obj.rect.position.x + obj.rect.size.x;
					dx = 0;
				}
			}
			if (obj.name == "ladder")
			{
				onLadder = true;
			}
			if (obj.name == "pike")
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
	case die: return "die";
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

void Player::handleHorizontalMovement()
{
	if (key["Left"] || key["Right"])
	{

		dir = (int)key["Left"]; //if the left key is pressed than direction is 1 otherwise 0

		dx = dir ? -0.08 : 0.08; //if direction left dx is negative and vice versa

		if (STATE == down || STATE == crawl)
		{
			STATE = crawl;
			dx = dir ? -0.03 : 0.03;
		}
		if (onGround && STATE != crawl)
			STATE = walk;
	}
	else //left and right are not pressed
	{
		dx = 0;
		if (STATE == walk)
			STATE = stay;
		else if (STATE == crawl || STATE == down)
			STATE = down;
	}
}

void Player::handleVerticalMovement()
{
	if (key["Up"] || key["Down"])
	{
		if (onGround)
		{
			//cant jump if sitting or crawling
			if (key["Up"] && STATE != down && STATE != crawl)
			{
				onGround = false;
				STATE = jump;
				dy = -0.2;
			}
			else //key down
			{
				if (!isAttacking) //cannot sit when attacking
				{
					sitDown(); //shrinks body
					if (STATE != crawl)
						STATE = down;
				}
			}
		}
	}
	else
	{
		// if onGround + is not moving + not sitting -> stand up
		if (onGround && dx == 0 && STATE != down)
			STATE = stay;
		// if in flight and attack animation ended -> back to jump animation
		else if (!isAttacking && STATE == attack)
			STATE = jump;
	}
}

void Player::handleLadderMovement()
{
	if (onLadder && !isAttacking)
	{
		if (STATE == down || STATE == crawl)
			standUp();

		STATE = ladder;

		if (anim.getCurrentAnimationName() == "attack") // Fix: switch to ladder animation after attack animation ends
			anim.set("ladder");

		anim.play(); // Fix: resume animation when the player starts climbing again after stopping

		//freeze on a ladder (do not play animation and do not move)
		if (!key["Up"] && !key["Down"])
		{
			dy = 0;
			anim.pause();
		}
		else
			dy = key["Up"] ? -0.025 : 0.025;
	}
}

void Player::handleStandUpTransition()
{
	if (!key["Down"] && (STATE == down || STATE == crawl))
	{
		// Check if there's space above to stand up (temporary solution — should be improved)
		bool topCollision = false;

		//imagine we are standing
		sf::FloatRect tempRect = rect;
		tempRect.size.y = 24;
		tempRect.position.y -= 12;

		//check collision in standing case
		for (const auto& obj : objects)
		{
			if (tempRect.findIntersection(obj.rect) && obj.name == "solid")
			{
				topCollision = true;
				STATE = (dx != 0) ? crawl : down;
				break;
			}
		}
		//if no collision - stand up
		if (!topCollision)
		{
			STATE = stay;
			standUp();
		}
	}
}

void Player::handleAttack()
{
	if (key["Space"] && STATE != down && STATE != crawl) //cannot attack when sitting or crawling
		isAttacking = true;
}

