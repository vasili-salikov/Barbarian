#include "../../Header Files/Animation/AnimationManager.h"

void AnimationManager::create(std::string name, sf::Texture& texture, sf::Vector2i position, sf::Vector2i frameSize, int frameCount, float speed, sf::Vector2i frameStep)
{
	animList[name] = Animation(texture, position, frameSize, frameCount, speed, frameStep);
	currentAnim = name;
}

void AnimationManager::draw(sf::RenderWindow& w, sf::Vector2f position)
{
	animList[currentAnim].getSprite()->setPosition(position);
	w.draw(*animList[currentAnim].getSprite());
}

void AnimationManager::set(sf::String name) { currentAnim = name; }

void AnimationManager::flip(bool b) { animList[currentAnim].setFlip(b); }

void AnimationManager::tick(float time) { animList[currentAnim].tick(time); }

void AnimationManager::pause() { animList[currentAnim].setIsPlaying(false); }

void AnimationManager::play() { animList[currentAnim].setIsPlaying(true); }

double AnimationManager::getCurrentFrame() { return animList[currentAnim].getCurrentFrame(); }

std::string AnimationManager::getCurrentAnimationName() { return currentAnim; }

void AnimationManager::setScale(sf::Vector2f factors) { animList[currentAnim].getSprite()->setScale(factors); }

void AnimationManager::restart() { animList[currentAnim].setCurrentFrame(0); }