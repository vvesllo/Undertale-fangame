#pragma once

#include <SFML/Graphics.hpp>

#include "Utils.h"

class HeartShapeObject
{
private:
	float m_speed;
	sf::Sprite m_shape;
	sf::FloatRect m_rect;
	sf::Vector2f m_direction;


public:
	HeartShapeObject();

	void update(
		sf::FloatRect rect,
		float dt,
		TGameState game_state
	);


	void setPosition(sf::Vector2f position);
	void setDirection(sf::Vector2f direction);

	sf::Vector2f getSize();
	sf::Vector2f getCenter();
	sf::Vector2f getPosition();
	sf::Sprite getShape();
};

