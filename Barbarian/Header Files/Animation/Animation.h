#pragma once
#include <SFML/Graphics.hpp>
#include <memory> //for unique_ptr

class Animation
{
private:
	std::vector<sf::IntRect> frames, frames_flip; // Frames from the sprite sheet and their mirrored (reversed) versions
	float currentFrame, speed;
	bool flip, isPlaying;
	std::unique_ptr<sf::Sprite> sprite; //workaround due to absence of defaul constructor for sprite in SFML 3.0

public:
	Animation();
	Animation(sf::Texture& texture, sf::Vector2i position, sf::Vector2i frameSize, int frameCount, float speed, sf::Vector2i frameStep);

	void tick(float time);
	sf::Sprite* getSprite() const;
	bool getFlip() const;
	void setFlip(bool flip);
	bool getIsPlaying() const;
	void setIsPlaying(bool isPlaying);
	float getCurrentFrame() const;
	void setCurrentFrame(float newFrame);
};