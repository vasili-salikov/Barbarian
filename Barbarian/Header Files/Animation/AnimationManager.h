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
	void create(std::string name, sf::Texture& texture, sf::Vector2i position, sf::Vector2i frameSize, int frameCount, float speed, sf::Vector2i frameStep = { 0, 0 });
	void draw(sf::RenderWindow& w, sf::Vector2f position = {0, 0});
	void set(sf::String name);
	void flip(bool b = 1);
	void tick(float time);
	void pause();
	void play();
	double getCurrentFrame();
	std::string getCurrentAnimationName();
	void setScale(sf::Vector2f factors);
	void restart();
};