#pragma once
#include "Hitbox.h"

class IFighter
{
protected:
	std::vector<Hitbox> activeHitboxes;

public:
	virtual void startAttack() = 0;
	virtual void endAttack() = 0;
	std::vector<Hitbox>& getHitboxes();
};