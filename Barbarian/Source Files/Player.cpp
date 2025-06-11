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
	anim.create("walk", texture, 0, 36, 32, 32, 8, 0.005, 32);
	anim.create("attack", texture, 0, 68, 32, 32, 7, 0.005, 32);
	anim.create("hurt", texture, 0, 100, 32, 32, 3, 0.0025, 32);
	anim.create("down", texture, 128, 132, 32, 32, 1, 0.02, 32);
	anim.create("crawl", texture, 96, 132, 32, 32, 4, 0.005, 32);
	anim.create("jump", texture, 0, 36, 32, 32, 3, 0.01, 32);
	anim.create("die", texture, 0, 132, 32, 32, 7, 0.002, 32);
	anim.create("ladder", texture, 0, 164, 32, 28, 2, 0.002, 32);
	anim.create("FusRoDah", texture, 0, 196, 32, 28, 4, 0.002, 32);
}

void Player::handleControls()
{
	//STATE = stay;
	if (key["Left"])
	{
		dir = 1;
		//std::cout << "[Left]" << std::endl;

		//speed = 0.08;
		dx = -0.08;
		STATE = walk;
		//isMoving = true;
	}
	if (key["Right"])
	{
		//std::cout << "[Right]" << std::endl;
		dir = 0;

		//speed = 0.08;
		dx = 0.08;
		STATE = walk;
		//isMoving = true;	
	}
	if (!(key["Right"] || key["Left"]))
	{
		if (STATE == walk)
		{
			STATE = stay;
		}
		//if (STATE == crawl || STATE == down)
		//{
		//	STATE = down;
		//}
		dx = 0;
	}
	if (key["Up"])
	{
		//std::cout << "[Up]" << std::endl;
		if (onGround)
		{
			dy = -0.2;
			onGround = false;
			STATE = jump;
		}
		if (onLadder)
		{
			dy = -0.02;
		}
	}
	if (key["Down"])
	{
		//std::cout << "[Down]" << std::endl;
		//speed = 0.05;
		
		if (onGround)
		{
			STATE = down;
		}
		if (onLadder)
		{
			dy = 0.02;
		}
	}
	if (key["Space"])
	{
		//std::cout << "[Space]" << std::endl;
		STATE = attack;
	}
}

void Player::update(double time)
{
	//std::cout << "speed:" << speed << std::endl;
	//std::cout << "ismoving:"<<isMoving << std::endl;
	handleControls();

	if (STATE == stay) anim.set("stay");
	if (STATE == walk)
	{
		/*if (dir == 0)
			dx = speed;
		else
			dx = -speed;*/
		anim.set("walk");
	}
	if (STATE == jump)
	{
		if (onGround)
		{
			STATE = stay;
		}
		else
			anim.set("jump");
	}
	if (STATE == down) anim.set("down");
	if (STATE == attack) anim.set("attack");
	if (STATE == ladder) anim.set("ladder");

	if (onLadder)
	{
		STATE = ladder;
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


	//check if is moving them slow down until stop
	//if (isMoving && speed > 0)
	//{
	//	speed -= 0.00001;
	//	if (speed <= 0)
	//	{
	//		speed =dx= 0;
	//		isMoving = false;
	//		STATE = stay;
	//	}

	//}

	//if (!isMoving)
	//{
	//	speed = 0;
	//}
	if (health == 0)
	{
		alive = false;
	}
	//if (!onGround) // gravity
	//{
	if(!onLadder)
		dy = dy + 0.0003 * time; //constant gravity

	//}

	anim.tick(time);
	key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;
}

void Player::draw(sf::RenderWindow& w)
{
	//debug //see player body
	sf::RectangleShape playerRect(sf::Vector2f(rect.size.x, rect.size.y));
	playerRect.setFillColor(sf::Color::Green);
	playerRect.setPosition(sf::Vector2f(rect.position.x, rect.position.y));
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



//void Player::update(double time) //temporary function
//{
//	//const double GRAVITY = 10;          // units per second^2
//	//const double JUMP_SPEED = -3000;      // initial jump velocity
//	//const double MOVE_SPEED = 100.0;       // max horizontal speed
//	//std::cout << STATE << std::endl;
//
//	//if (key["Space"])
//	//{
//	//	if (STATE == stay)
//	//	{
//	//		std::cout << "ATTACK" << std::endl;
//	//		STATE = attack;
//	//	}
//	//}
//	//if (key["Right"] && onGround) {
//	//	dir = 0;
//	//	dx = MOVE_SPEED * time;
//	//}
//	//if (key["Left"] && onGround) {
//	//	dir = 1;
//	//	dx = -MOVE_SPEED * time;
//	//}
//	//if (key["Up"] && onGround) {
//	//	dy = JUMP_SPEED * time;
//	//	onGround = false;
//	//	STATE = jump;
//	//}
//	//if (key["Down"] && onGround) {
//	//	STATE = down;
//	//}
//
//	//if (!onGround) {
//	//	dy += GRAVITY * time;
//	//}
//	//else {
//	//	dy = 0;
//	//}
//
//	////Simulate ground contact (replace with real collision later) ---
//	//if (y >= 100) {
//	//	y = 100;           
//	//	onGround = true;
//	//}
//	//else {
//	//	onGround = false;
//	//}
//	//
//
//	//// --- State selection ---
//	//if (!onGround) {
//	//	STATE = jump;
//	//}
//	//else if (dx != 0) {
//	//	STATE = walk;
//	//	isMoving = true;
//
//
//	//	//simulate inertia
//	//	if (dx > 0)
//	//	{
//	//		dx -= time;
//	//		if (dx < 0)
//	//		{
//	//			dx = 0;
//	//			STATE = stay;
//	//			isMoving = false;
//	//		}
//	//	}
//	//	else if (dx < 0)
//	//	{
//	//		dx += time;
//	//		if (dx > 0)
//	//		{
//	//			dx = 0;
//	//			STATE = stay;
//	//			isMoving = false;
//	//		}
//	//	}
//	//}
//	//else 
//	//{
//	//	if (STATE == attack)
//	//	{
//	//		if (animManager.getCurrentFrame() > 6)
//	//		{
//	//			animManager.restart();
//	//			STATE = stay;
//	//		}
//	//	}
//	//	else
//	//	{
//	//		STATE = stay;
//	//	}
//	//	
//	//}
//	////Movement
//	//x += dx;
//	//y += dy;
//
//	//switch (STATE)
//	//{
//	//	case walk: animManager.set("walk"); break;
//	//	case down: animManager.set("down"); break;
//	//	case jump: animManager.set("jump"); break;
//	//	case attack: animManager.set("attack");break;
//	//	default:   animManager.set("stay"); break;
//	//}
//
//	//animManager.tick(time);
//	//key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;
//
//
//	int GRAVITY = 80;
//	int MOVE_SPEED = 50;
//	drawY = rect.position.y - 2;
//	drawX = rect.position.x - 10;
//	/*drawX = obj.rect.left - 10;
//	drawY = obj.rect.top - 2;*/
//
//
//	if (health <= 0)
//	{
//		dx = 0;
//		STATE = die;
//		anim.set("die");
//		timer += time;
//		if (timer > 3500)
//		{
//			anim.pause();
//			if (timer > 4500)
//			{
//				anim.play();
//				STATE = stay;
//				alive = false;
//				timer = 0;
//			}
//		}
//	}
//	else
//	{
//		keyCheck(time);
//	}
//	if (STATE == ladder) { anim.set("ladder"); }
//	if (STATE == stay)	anim.set("stay");
//	if (STATE == walk)	anim.set("walk");
//	if (STATE == hurt) { anim.set("hurt"); if (anim.getCurrentFrame() > 2) { STATE = stay; anim.restart(); } }
//	if (STATE == down) { anim.set("down"); rect.size.y = 13; drawY -= 12; }
//	if (STATE == crawl) { anim.set("crawl"); rect.size.y = 13; drawY -= 12; }
//	//if (STATE == down) { anim.set("down"); obj.rect.height = 13; drawY -= 12; }
//	//if (STATE == crawl) { anim.set("crawl"); obj.rect.height = 13; drawY -= 12; }
//	if (STATE == jump)	anim.set("jump");
//	if (STATE == attack) { anim.set("attack"); }
//	if (STATE == FusRoDah)
//	{
//		anim.set("FusRoDah");
//		if (anim.getCurrentFrame() > 3.9)
//		{
//			fusrodah = true;
//			anim.restart();
//			STATE = stay;
//			stom = 0;
//		}
//	}
//
//	if (rect.size.y == 13)
//	//if (obj.rect.height == 13)
//	{
//		if (STATE != down && STATE != crawl)
//		{
//			rect.size.y = 24;
//			rect.position.y -= 12;
//			/*obj.rect.height = 24;
//			obj.rect.top -= 12;*/
//		}
//	}
//
//	if (stom < 1 && STATE != hurt && STATE != FusRoDah)
//	{
//		HURT = true;
//		stom = 0;
//	}
//	anim.flip(dir);
//
//	if (HURT)
//	{
//		STATE = hurt;
//		dx = 0;
//		timer += time;
//		if (timer > 4000)
//		{
//			STATE = stay;
//			HURT = false;
//			timer = 0;
//			stom = 2;
//		}
//	}
//	rect.position.x += dx * time;
//	//obj.rect.left += dx * time;
//	checkCollision(0);
//
//	if (!onGround && !onLadder)
//	{
//		
//		dy = dy + GRAVITY * time;
//	}
//	if (stom < 45 && !HURT && health > 0)
//	{
//		stom += 5 * time;
//	}
//	rect.position.y += dy * time;
//	//std::cout << "rect.position.y:" << rect.position.y << std::endl;
//	//obj.rect.top += dy * time;
//	onLadder = false;
//	onGround = false;
//	
//	checkCollision(1);
//
//	anim.tick(time);
//
//	//setPlayerCoordForView(obj.rect.left, obj.rect.top);
//
//	key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
//}




void Player::checkCollision(int horizontal) 
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (rect.findIntersection(objects[i].rect).has_value())
		{
			//std::cout << "COLLISION" << std::endl;
			if (objects[i].name == "solid")
			{
				std::cout << "COLLISION" << std::endl;
				if ((dy > 0) && (horizontal == 1))
				{
					//std::cout << "COLLISION" << std::endl;
					//position y = object position y - height of current object
					rect.position.y = objects[i].rect.position.y - rect.size.y;
					dy = 0;
					onGround = true;
				}
				if ((dy < 0) && (horizontal == 1))
				{
					//position y = object position y + height of current object
					rect.position.y = objects[i].rect.position.y + objects[i].rect.size.y;
					dy = 0;
				}
				if ((dx > 0) && (horizontal == 0))
				{
					//position x = object position x - width of current object
					rect.position.x = objects[i].rect.position.x - rect.size.x;
				}
				if ((dx < 0) && (horizontal == 0))
				{
					//position x = object position x + width of current object
					rect.position.x = objects[i].rect.position.x + objects[i].rect.size.x;
				}
			}
			if (objects[i].name == "ladder")
			{
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

//void Player::keyCheck(double time)
//{
//	if (STATE != hurt)
//	{
//		if (STATE != attack && STATE != FusRoDah)
//		{
//			if (key["R"] || key["L"])
//			{
//				if (key["R"])
//				{
//					dir = 0;
//					dx = 50;
//
//					if (STATE == down || STATE == crawl)
//					{
//						STATE = crawl;
//						dx = 30;
//					}
//				}
//				else
//				{
//					dir = 1;
//					dx = -50;
//					if (STATE == down || STATE == crawl)
//					{
//						STATE = crawl;
//						dx = -20;
//					}
//				}
//				if (STATE == stay)
//				{
//					STATE = walk;
//				}
//				if (STATE == walk)
//				{
//					stom -= 0.075 * time;
//					if (onLadder && dy != 0)
//					{
//						STATE = ladder;
//					}
//				}
//			}
//		}
//		if (key["Up"])
//		{
//			if (STATE == stay || STATE == walk)
//			{
//				if (onGround)
//				{
//					stom -= 4 * time;
//					dy = -150;
//					onGround = false;
//					STATE = jump;
//				}
//			}
//			else if (onLadder)
//			{
//				STATE = ladder;
//				dy = -10;
//				anim.play();
//			}
//			else
//			{
//				if (STATE != down && STATE != crawl)
//				{
//					if (dy != 0)
//					{
//						STATE = jump;
//					}
//					else
//					{
//						STATE = stay;
//					}
//
//				}
//			}
//		}
//		if (key["Down"])
//		{
//			if (onLadder)
//			{
//				if (STATE != crawl && STATE != down)
//				{
//					STATE = ladder;
//					dy = 10;
//					anim.play();
//				}
//			}
//			if (STATE == stay || STATE == walk)
//			{
//				STATE = down;
//			}
//			if (STATE == crawl)
//			{
//				if (!(key["R"] || key["L"]))
//				{
//					dx = 0;
//					STATE = down;
//				}
//			}
//			if (STATE == jump && onGround || STATE == ladder && !onLadder)
//			{
//				STATE = stay;
//			}
//		}
//		if (key["Space"])
//		{
//			if (STATE != down && STATE != crawl && STATE != walk)
//			{
//				if (stom < 1)
//				{
//					stom = 0;
//				}
//				if (!ATTACK && stom > 0)
//				{
//					if (STATE == attack)
//					{
//						anim.restart();
//						anim.pause();
//					}
//					STATE = attack;
//					stom -= time * 3;
//
//					if (stom > 0)
//					{
//						force += 5 * time;
//					}
//				}
//				if (force > 85)
//				{
//					//FusRoDahSound.play();
//					STATE = FusRoDah;
//					anim.play();
//					ATTACK = true;
//					force = 0;
//					stom = 0;
//				}
//			}
//		}
//		//отпускание клавиш
//		if (!(key["R"] || key["L"]))
//		{
//			if (STATE == walk)
//			{
//				STATE = stay;
//			}
//			if (STATE == crawl || STATE == down)
//			{
//				STATE = down;
//			}
//			dx = 0;
//		}
//		if (!key["Up"] && !key["Down"])
//		{
//			if (STATE == stay)
//			{
//				if (dy != 0)
//				{
//					STATE = jump;
//				}
//			}
//			if (STATE == jump || STATE == ladder)
//			{
//				if (onLadder)
//				{
//					STATE = ladder;
//					dy = 0;
//					anim.pause();
//				}
//				else if (onGround)
//				{
//					STATE = stay;
//
//				}
//				else
//				{
//					anim.play();
//					STATE = jump;
//				}
//			}
//			if (STATE == down || STATE == crawl)
//			{
//				sf::FloatRect temp = rect;
//				temp.size.y = 24;
//				temp.position.y = rect.position.y - 16;
//				/*temp.height = 24;
//				temp.top = obj.rect.top - 16;*/
//
//				for (int i = 0; i < objects.size(); i++)//проходимся по объектам
//					if (temp.findIntersection(objects[i].rect))//проверяем пересечение игрока с объектом
//					{
//						if (objects[i].name == "solid")//если встретили препятствие
//						{
//							temp.size.y = 16;
//							//temp.height = 16;
//							if (dx != 0)
//							{
//								STATE = crawl;
//							}
//							else
//							{
//								STATE = down;
//							}
//						}
//					}
//				rect.size.y = temp.size.y;
//				//obj.rect.height = temp.height;
//				if (rect.size.y == 24)
//				{
//					STATE = stay;
//					rect.position.y -= 12;
//					//obj.rect.top -= 12;
//				}
//			}
//		}
//		if (!key["Space"])
//		{
//			if (STATE != ladder)
//			{
//				anim.play();
//			}
//			force = 0;
//			if (STATE == attack)
//			{
//				if (!shot)
//				{
//					ATTACK = true;
//					shot = true;
//				}
//				if (anim.getCurrentFrame() > 5)
//				{
//					shot = false;
//					STATE = stay;
//					anim.restart();
//				}
//			}
//		}
//	}
//
//}