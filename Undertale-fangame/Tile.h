#pragma once

#include <SFML/Graphics.hpp>

typedef enum {
	SOLID,
	ACTION,
	CHANGE_LEVEL,
	SAVE
} TTileType;

class Tile
{
private:
	sf::RectangleShape m_shape;
	sf::FloatRect m_rect;
	sf::Color m_color;
	sf::Vector2f m_spawn_pos;
	TTileType m_type;
	size_t m_index;

public:
	Tile(
		sf::FloatRect rect,
		sf::Color color,
		TTileType type,
		sf::Vector2f spawn_pos,
		size_t index
	);

	sf::Vector2f getSpawnPosition();
	sf::RectangleShape getShape();
	sf::FloatRect getRect();
	size_t getIndex();
	TTileType getType();
};

