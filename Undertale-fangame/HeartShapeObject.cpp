#include "HeartShapeObject.h"
#include <iostream>

HeartShapeObject::HeartShapeObject()
{
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("Images/HeartShapedObject.png");
	m_shape.setTexture(*texture);
	m_rect.width = 10;
	m_rect.height = 9;
	m_shape.setPosition(300, 300);
	m_speed = 2;
}

void HeartShapeObject::setPosition(sf::Vector2f position)
{
	m_rect.left = position.x;
	m_rect.top = position.y;
	m_shape.setPosition(position);
}

void HeartShapeObject::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

sf::Vector2f HeartShapeObject::getSize()
{
	return sf::Vector2f(m_rect.width, m_rect.height);
}

sf::Vector2f HeartShapeObject::getCenter()
{
	return sf::Vector2f(
		m_rect.left + m_rect.width,
		m_rect.top + m_rect.height
	);
}

sf::Vector2f HeartShapeObject::getPosition()
{
	return sf::Vector2f(m_rect.left, m_rect.top);
}

sf::Sprite HeartShapeObject::getShape()
{
	return m_shape;
}

void HeartShapeObject::update(
	sf::FloatRect rect,
	float dt,
	TGameState game_state
)
{
	m_rect.left += m_speed * m_direction.x * dt;
	m_rect.top += m_speed * m_direction.y * dt;
	
	if (game_state == TGameState::BATTLE)
	{
		if (m_rect.left < rect.left) m_rect.left = rect.left;
		if (m_rect.left + m_rect.width > rect.left + rect.width) m_rect.left = rect.left + rect.width - m_rect.width;

		if (m_rect.top < rect.top) m_rect.top = rect.top;
		if (m_rect.top + m_rect.height > rect.top + rect.height) m_rect.top = rect.top + rect.height - m_rect.height;
	}


	//std::cout << m_rect.left << ", " <<
	//    m_rect.top << '\n';

	m_shape.setPosition(
		m_rect.left, m_rect.top
	);

	m_direction.x = 0;
	m_direction.y = 0;
}