#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "Level.h"
#include "Utils.h"
#include "AnimationManager.h"

// items
#include "CandyItem.h"
#include "DirtyMossItem.h"


// CONFIG PARAM

#define ANIMATION_DOWN		0
#define ANIMATION_RIGHT		1
#define ANIMATION_LEFT		2
#define ANIMATION_UP		3

class Player
{
private:
	sf::FloatRect m_rect;
	sf::Vector2u m_sprite_size;
	sf::Sprite m_shape;
	sf::Vector2f m_direction;
	sf::Vector2f m_new_spawn_point;
	std::list<TILE_TYPE> m_colliders_map;
	std::vector<Item*> m_inventory;

	TEntityInfo m_info;
	AnimationManager m_animation_manager;

	float m_speed;
	float m_animation_speed;
	short m_state;
	bool m_can_move;
	bool m_goto_new_level;
	bool m_new_action;

	TILE_TYPE checkCollision(char direction, TConfigStruct& config);
	
	// animation
	void initAnimation();
	void updateAnimation(float dt);
public:
	Player();
	Player(
		sf::FloatRect rect,
		sf::Texture& texture
	);

	void update(float dt, TConfigStruct& config);
	void reset();
	void resetValues();
	
	bool checkGotoNewLevel();
	bool checkNewAction();

	void setAnimationDirection(short dir);
	void setPosition(sf::Vector2f position);
	void setCanMove(bool b);
	void setDirection(sf::Vector2f direction);
	void setCollidersMap(std::list<TILE_TYPE> map);

	TEntityInfo& getInfo();
	bool getCanMove();
	sf::Sprite getShape();
	sf::FloatRect getRect();
	sf::Vector2f getCenter();
	sf::Vector2f getPosition();
	std::vector<Item*>& getInventory();
};

