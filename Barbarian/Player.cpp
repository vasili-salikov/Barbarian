#include "Player.h"
#include <iostream>

Player::Player(sf::Image& img, std::string name, Level &lvl, float x, float y, int w, int h) : Entity(img, name, x, y, w, h)
{
	//initialise objects collection with all the objects from the map
	objects = lvl.GetAllObjects();


	//list of animation declaration 
	animManager.create("stay", texture, 0, 4, 32, 32, 5, 4, 32);
	animManager.create("walk", texture, 0, 36, 32, 32, 8, 10, 32);
	animManager.create("attack", texture, 0, 68, 32, 32, 7, 10, 32);
	animManager.create("hurt", texture, 0, 100, 32, 32, 3, 3, 32);
	animManager.create("down", texture, 128, 132, 32, 32, 1, 2, 32);
	animManager.create("crawl", texture, 96, 132, 32, 32, 4, 1, 32);
	animManager.create("jump", texture, 0, 36, 32, 32, 3, 10, 32);
	animManager.create("die", texture, 0, 132, 32, 32, 7, 2, 32);
	animManager.create("ladder", texture, 0, 164, 32, 28, 2, 1, 32);
	animManager.create("FusRoDah", texture, 0, 196, 32, 28, 4, 2, 32);
}

void Player::update(double& time) //temporary function
{
	const double GRAVITY = 10;          // units per second^2
	const double JUMP_SPEED = -3000;      // initial jump velocity
	const double MOVE_SPEED = 100.0;       // max horizontal speed
	std::cout << STATE << std::endl;

	if (key["Space"])
	{
		if (STATE == stay)
		{
			std::cout << "ATTACK" << std::endl;
			STATE = attack;
		}
	}
	if (key["Right"] && onGround) {
		dir = 0;
		dx = MOVE_SPEED * time;
	}
	if (key["Left"] && onGround) {
		dir = 1;
		dx = -MOVE_SPEED * time;
	}
	if (key["Up"] && onGround) {
		dy = JUMP_SPEED * time;
		onGround = false;
		STATE = jump;
	}
	if (key["Down"] && onGround) {
		STATE = down;
	}

	if (!onGround) {
		dy += GRAVITY * time;
	}
	else {
		dy = 0;
	}

	//Simulate ground contact (replace with real collision later) ---
	if (y >= 100) {
		y = 100;           
		onGround = true;
	}
	else {
		onGround = false;
	}
	

	// --- State selection ---
	if (!onGround) {
		STATE = jump;
	}
	else if (dx != 0) {
		STATE = walk;
		isMoving = true;


		//simulate inertia
		if (dx > 0)
		{
			dx -= time;
			if (dx < 0)
			{
				dx = 0;
				STATE = stay;
				isMoving = false;
			}
		}
		else if (dx < 0)
		{
			dx += time;
			if (dx > 0)
			{
				dx = 0;
				STATE = stay;
				isMoving = false;
			}
		}
	}
	else 
	{
		if (STATE == attack)
		{
			if (animManager.getCurrentFrame() > 6)
			{
				animManager.restart();
				STATE = stay;
			}
		}
		else
		{
			STATE = stay;
		}
		
	}
	//Movement
	x += dx;
	y += dy;

	switch (STATE)
	{
		case walk: animManager.set("walk"); break;
		case down: animManager.set("down"); break;
		case jump: animManager.set("jump"); break;
		case attack: animManager.set("attack");break;
		default:   animManager.set("stay"); break;
	}

	animManager.tick(time);
	key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;
}

void Player::draw(sf::RenderWindow& w)
{
	animManager.flip(dir);
	animManager.draw(w, x, y);
}