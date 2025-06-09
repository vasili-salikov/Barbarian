#include "AnimationManager.h"

void AnimationManager::create(std::string name, sf::Texture& t, int x, int y, int w, int h, int count, double speed, int stepX, int stepY)
{
	animList[name] = Animation(t, x, y, w, h, count, speed, stepX, stepY);
	currentAnim = name;
}

void AnimationManager::draw(sf::RenderWindow& w, int x, int y)
{
	animList[currentAnim].getSprite()->setPosition(sf::Vector2f(x, y));
	w.draw(*animList[currentAnim].getSprite());
}

void AnimationManager::set(sf::String name) 
{ 
	currentAnim = name; 
}

void AnimationManager::flip(bool b) 
{ 
	animList[currentAnim].setFlip(b);
}

void AnimationManager::tick(double time)
{ 
	animList[currentAnim].tick(time); 
}

void AnimationManager::pause() 
{ 
	animList[currentAnim].setIsPlaying(false); 
}

void AnimationManager::play() 
{ 
	animList[currentAnim].setIsPlaying(true); 
}

double AnimationManager::getCurrentFrame()
{ 
	return animList[currentAnim].getCurrentFrame(); 
}

void AnimationManager::setScale(sf::Vector2f size) 
{ 
	animList[currentAnim].getSprite()->setScale(size);
}

void AnimationManager::restart() 
{
	animList[currentAnim].setCurrentFrame(0);
}