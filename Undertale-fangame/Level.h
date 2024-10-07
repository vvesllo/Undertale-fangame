#pragma once

#include <vector>
#include <list>
#include <format>
#include <iostream>
#include <fstream>
#include <memory>
#include "Tile.h"

#define TILE_SCALE 1.5f
#define TILE_TYPE std::shared_ptr<Tile>

class Level
{
private:
	float m_max_width;
	float m_max_height;

	std::list<std::string> splitAsList(
		std::string input,
		char delimiter
	);
	std::vector<std::string> splitAsVector(
		std::string input,
		char delimiter
	);
	std::string readFile(std::string path);

public:
	Level();

	std::list<TILE_TYPE> loadFromFile(
		std::string path
	);

	float getMaxWidth();
	float getMaxHeight();
	sf::Vector2u getViewFixes();

};

