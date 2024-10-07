#include "Tile.h"

Tile::Tile(
	sf::FloatRect rect,
	sf::Color color,
	TTileType type,
	sf::Vector2f spawn_pos,
	size_t index
)
{
	m_color = color;
	m_rect = rect;
	m_type = type;
	m_spawn_pos = spawn_pos;
	m_index = index;

	m_shape = sf::RectangleShape(
		sf::Vector2f(rect.width, rect.height)
	);
	m_shape.setPosition(
		sf::Vector2f(rect.left, rect.top)
	);
	m_shape.setFillColor(m_color);
}

sf::RectangleShape Tile::getShape() { return m_shape; }
sf::FloatRect Tile::getRect() { return m_rect; }
size_t Tile::getIndex() { return m_index; }
TTileType Tile::getType() { return m_type; }
sf::Vector2f Tile::getSpawnPosition() { return m_spawn_pos; }
