#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960


typedef enum {
	USUAL,
	ACT,
	BATTLE
} TGameState;

typedef struct
{
	std::string name;
	short max_hp;
	short hp;
	short damage;
	unsigned short coins;
	unsigned short exp;
} TEntityInfo;

struct TConfigStruct
{
	int current_map;
	size_t current_action_index=0;
};

typedef struct
{
	std::string title;
	std::string description;
} TItemInfo;

static sf::Vector2f normVec2f(sf::Vector2f vec)
{
	float distance = std::sqrt(
		vec.x * vec.x + vec.y * vec.y
	);
	return vec / distance;
}

static sf::Vector2f rotateVec2f(sf::Vector2f vec, float deg)
{
	return sf::Vector2f(
		vec.x * std::cos(deg * M_PI / 180) - vec.y * std::sin(deg * M_PI / 180),
		vec.y * std::cos(deg * M_PI / 180) + vec.x * std::sin(deg * M_PI / 180)
	);
}