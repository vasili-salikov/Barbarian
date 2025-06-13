#pragma once
#include "DynamicEntity.h"
#include <map>
#include "Map/Level.h"

class Player: public DynamicEntity
{
public:
	std::map<std::string, bool> key; //map of pressed buttons	
	bool onLadder, isAlive, onGround, isAttacking;

	Player(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(double time) override;
	void draw(sf::RenderWindow &w) override;

private:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder, FusRoDah } STATE;
	int health;//

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
