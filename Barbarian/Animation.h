#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
private:
	std::vector<sf::IntRect> frames, frames_flip; //frames from sprite, and their reverse
	double currentFrame, speed;
	bool flip, isPlaying;
	std::unique_ptr<sf::Sprite> sprite; //workaround due to absence of defaul constructor for sprite in SFML 3.0

public:
	Animation();
	Animation(sf::Texture& t, int x, int y, int w, int h, int count, double Speed, int stepX, int stepY);

	void tick(double time);
	sf::Sprite* getSprite() const;
	bool getFlip() const;
	void setFlip(bool flip);
	bool getIsPlaying() const;
	void setIsPlaying(bool isPlaying);
	double getCurrentFrame() const;
	void setCurrentFrame(double newFrame);
};