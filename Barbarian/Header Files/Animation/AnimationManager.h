#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <map>

class AnimationManager
{
private:
	std::string currentAnim;
	std::map<std::string, Animation> animList;

public:
	void create(std::string name, sf::Texture& t, int x, int y, int w, int h, int count, double speed, int stepX=0, int stepY=0);
	void draw(sf::RenderWindow& w, int x=0, int y=0);
	void set(sf::String name);
	void flip(bool b = 1);
	void tick(double time);
	void pause();
	void play();
	double getCurrentFrame();
	std::string getCurrentAnimationName();
	void setScale(sf::Vector2f factors);
	void restart();
};