 #pragma once
#include "../../Header Files/Animation/Animation.h"
#include <iostream>

Animation::Animation() {}

Animation::Animation(sf::Texture& t, int x, int y, int w, int h, int count, double Speed, int stepX = 0, int stepY = 0)
	:sprite(std::make_unique<sf::Sprite>(t))
{
	currentFrame = 0;
	speed = Speed;
	isPlaying = true;
	flip = false;

	for (size_t i = 0; i < count; i++)
	{
		frames.push_back(sf::IntRect(sf::Vector2i(x + i * stepX, y + i * stepY), sf::Vector2i(w, h)));
		frames_flip.push_back(sf::IntRect(sf::Vector2i(x + i * stepX + w, y + i * stepY), sf::Vector2i(-w, h)));
	}

	sprite->setTextureRect(frames[0]);
}

void Animation::tick(double time)
{
	if (!isPlaying || frames.empty())
		return;

	currentFrame += speed * time;

	// Wrap safely using modulo, even if currentFrame becomes large
	int i = static_cast<int>(currentFrame) % frames.size();

	if (flip)
		sprite->setTextureRect(frames_flip[i]);
	else
		sprite->setTextureRect(frames[i]);
}

sf::Sprite* Animation::getSprite() const
{
	return this->sprite.get();
}

bool Animation::getFlip() const
{
	return flip;
}

void Animation::setFlip(bool flip)
{
	this->flip = flip;
}

bool Animation::getIsPlaying() const
{
	return this->isPlaying;
}

void Animation::setIsPlaying(bool isPlaying)
{
	this->isPlaying = isPlaying;
}

double Animation::getCurrentFrame() const
{
	return this->currentFrame;
}

void Animation::setCurrentFrame(double newFrame)
{
	this->currentFrame = newFrame;
}