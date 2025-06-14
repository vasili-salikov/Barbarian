#pragma once
#include "DynamicEntity.h"
#include "IFighter.h"
#include "IDamageable.h"
#include <map>
#include "Map/Level.h"

class Player: public DynamicEntity, public IFighter, public IDamageable
{
public:
	std::map<std::string, bool> key; //map of pressed buttons	
	bool onLadder, isAlive, onGround, isAttacking;

	Player(sf::Image img, std::string name, sf::FloatRect& rect, std::vector<Object*> objectsToInteractWith);
	void update(float time) override;
	void draw(sf::RenderWindow &w) override;
	void startAttack() override;
	void endAttack() override;
	void takeDamage(int amount) override;
	std::vector<Hitbox>& getHitboxes();

private:
	enum { stay, walk, jump, attack, hurt, down, crawl, die, ladder } STATE;
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
