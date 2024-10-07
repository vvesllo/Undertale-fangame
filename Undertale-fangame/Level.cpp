#include "Level.h"

std::list<std::string> Level::splitAsList(std::string input, char delimiter)
{
	std::list<std::string> tokens;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = input.find(delimiter, prev)) != std::string::npos) {
		tokens.push_back(input.substr(prev, pos - prev));
		prev = pos + 1;
	}
	tokens.push_back(input.substr(prev));

	return tokens;
}

std::vector<std::string> Level::splitAsVector(std::string input, char delimiter)
{
	std::vector<std::string> tokens;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = input.find(delimiter, prev)) != std::string::npos) {
		tokens.push_back(input.substr(prev, pos - prev));
		prev = pos + 1;
	}
	tokens.push_back(input.substr(prev));

	return tokens;
}

std::string Level::readFile(std::string path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cout << std::format("Failed to open `{}`", path) << std::endl;
		exit(-1);
	}
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

Level::Level()
{
	m_max_width = 0;
	m_max_height = 0;
}

std::list<TILE_TYPE> Level::loadFromFile(std::string path)
{
	std::list<TILE_TYPE> colliders;
	std::list<std::string> lines = splitAsList(readFile(path), '\n');
	std::vector<std::string> data;

	m_max_height = 0;
	m_max_width = 0;
	float x, y, w, h, spawn_pos_x, spawn_pos_y;

	for (std::list<std::string>::iterator it = lines.begin(); it != lines.end(); it++)
	{
		data = splitAsVector(*it, ';');

		if (data[0] == "area")
		{
			m_max_width = std::stof(data[1]) * TILE_SCALE;
			m_max_height = std::stof(data[2]) * TILE_SCALE;
			continue;
		}

		x = std::stof(data[1]) * TILE_SCALE;
		y = std::stof(data[2]) * TILE_SCALE;
		w = std::stof(data[3]) * TILE_SCALE;
		h = std::stof(data[4]) * TILE_SCALE;

		if (data[0] == "solid")
			colliders.push_back(
				std::make_shared<Tile>(
					sf::FloatRect(
						x, // x-pos
						y, // y-pos
						w, // width
						h  // height
					),
					sf::Color::Green,
					TTileType::SOLID,
					sf::Vector2f(0, 0),
					0
					)
			);
		else if (data[0] == "level")
		{
			spawn_pos_x = std::stof(data[5]) * TILE_SCALE;
			spawn_pos_y = std::stof(data[6]) * TILE_SCALE;

			colliders.push_back(
				std::make_shared<Tile>(
					sf::FloatRect(
						x, // x-pos
						y, // y-pos
						w, // width
						h  // height
					),
					sf::Color::Magenta,
					TTileType::CHANGE_LEVEL,
					sf::Vector2f(spawn_pos_x, spawn_pos_y),
					std::stoi(data[7])
					)
			);
		}
		else if (data[0] == "new_action")
			colliders.push_back(
				std::make_shared<Tile>(
					sf::FloatRect(
						x, // x-pos
						y, // y-pos
						w, // width
						h  // height
					),
					sf::Color::Blue,
					TTileType::ACTION,
					sf::Vector2f(0, 0),
					std::stoi(data[5])
				)
			);

	}
	return colliders;
}

float Level::getMaxWidth()
{
	return m_max_width;
}

float Level::getMaxHeight()
{
	return m_max_height;
}

sf::Vector2u Level::getViewFixes()
{
	return sf::Vector2u();
}
