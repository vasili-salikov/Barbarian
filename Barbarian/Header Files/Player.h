#pragma once
#include "DynamicEntity.h"
#include <map>
#include "Map/Level.h"

class Player: public DynamicEntity
{
public:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder, FusRoDah } STATE;
	std::map<std::string, bool> key; //map of pressed buttons
	int health;//
	Object* testObj;
	sf::FloatRect& testRect;
	
	bool onLadder, isAlive, onGround, isAttacking;

	Player(sf::Image img, std::string name, Level &lvl, sf::FloatRect rect);
	void update(double time) override;
	void draw(sf::RenderWindow &w) override;

private:
	void checkCollision(float Dx, float Dy);
	std::string getCurrentStateAsString();
	void standUp(); // Switch hero to standing state (restore full height)
	void sitDown(); // Switch hero to sitting state (shrink model)

	void handleControls();
	void handleHorizontalMovement();
	void handleVerticalMovement();
	void handleLadderMovement();
	void handleStandUpTransition();
	void handleAttack();

};
