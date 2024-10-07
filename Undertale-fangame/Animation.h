#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
private:
	size_t m_frame_count;
	float m_speed;
	float m_current_frame;
	bool m_paused;
	std::vector<sf::IntRect> m_frame_rects;

public:
	Animation();
	Animation(
		size_t frame_count,
		float speed
	);

	void reset();
	void stop();
	void play();
	void pause();
	void toggle();
	void update(sf::Sprite& sprite, float dt);
	void add(sf::IntRect rect);
};

