 #pragma once
#include "../../Header Files/Animation/Animation.h"

Animation::Animation() {}

Animation::Animation(sf::Texture& texture, sf::Vector2i position, sf::Vector2i frameSize, int frameCount, float speed, sf::Vector2i frameStep)
	:sprite(std::make_unique<sf::Sprite>(texture))
{
	currentFrame = 0;
	this->speed = speed;
	isPlaying = true;
	flip = false;

	for (size_t i = 0; i < frameCount; i++)
	{
		// Add each frame to the frames list
		frames.push_back(sf::IntRect(sf::Vector2i(position.x + i * frameStep.x, position.y + i * frameStep.y), frameSize));
		// Add each mirrored frame to the frames_flip list
		// Used to avoid real-time mirroring by precomputing flipped frames
		frames_flip.push_back(sf::IntRect(sf::Vector2i(position.x + i * frameStep.x + frameSize.x, position.y + i * frameStep.y), sf::Vector2i(-frameSize.x, frameSize.y)));
	}
	sprite->setTextureRect(frames[0]);
}

void Animation::tick(float time)
{
	if (!isPlaying || frames.empty())
		return;

	currentFrame += speed * time;

	// Take new frame safely using modulo, even if currentFrame becomes out of range
	int i = (int)(currentFrame) % frames.size();

	if (flip)
		sprite->setTextureRect(frames_flip[i]);
	else
		sprite->setTextureRect(frames[i]);
}

sf::Sprite* Animation::getSprite() const { return this->sprite.get(); }

bool Animation::getFlip() const { return flip; }

void Animation::setFlip(bool flip) { this->flip = flip; }

bool Animation::getIsPlaying() const { return this->isPlaying; }

void Animation::setIsPlaying(bool isPlaying) { this->isPlaying = isPlaying; }

float Animation::getCurrentFrame() const { return this->currentFrame; }

void Animation::setCurrentFrame(float newFrame) { this->currentFrame = newFrame; }