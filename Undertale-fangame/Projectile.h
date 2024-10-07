#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "HeartShapeObject.h"

class SimpleProjectile
{
private:
	sf::Vector2f m_dir;
	sf::Vector2f m_position;
	sf::RectangleShape m_shape;
	std::function<void(SimpleProjectile* bullet, sf::Vector2f)> m_ai;
	float m_acceleration;

public:
	bool can_be_deleted;
	SimpleProjectile(
		sf::Vector2f position,
		sf::Vector2f dir,
		std::function<void(SimpleProjectile* bullet, sf::Vector2f)> ai
	);

	void setDirection(sf::Vector2f dir);
	void update(
		float dt,
		sf::Vector2f player_position
	);
	void AI(std::function<void(SimpleProjectile* bullet, sf::Vector2f)> ai);

	float getAcceleration();
	sf::RectangleShape& getObject();
	sf::RectangleShape getShape();
	sf::Vector2f getPostion();
	sf::Vector2f getDirection();
};

