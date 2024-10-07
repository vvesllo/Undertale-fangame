#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include "Utils.h"
#include "Player.h"
#include "Projectile.h"
#include "AnimationManager.h"

typedef struct
{
	std::string action_name;
	std::string action_result_text;
	unsigned short mercy_k;
} TActionParam;

class Enemy
{
private:

	std::vector<TActionParam> m_actions;
	sf::Vector2f m_view_center;
	sf::Vector2f m_view_size;
	sf::IntRect m_rect;
	TEntityInfo m_info;

protected:

	short mercy_k;
	bool is_spared;
	bool is_attacking;
	sf::Color inactive_color;

	void addAction(TActionParam params);

	// animation
	void initAnimation();
	void initEnemy(
		sf::IntRect rect,
		TEntityInfo& info,
		sf::Vector2f view_center,
		sf::Vector2f view_size
	);
	void updateAnimation(float dt);
	
	sf::Vector2f getPosition();
	sf::Vector2f getViewCenter();
	sf::Vector2f getViewSize();
	sf::SoundBuffer* createBuffer(std::string path_to_file);
public:
	Enemy();
	Enemy(
		sf::Vector2f position,
		sf::IntRect rect,
		sf::Texture& texture,
		TEntityInfo info
	);

	void doAction(unsigned char idx);
	std::string getActionResultText(unsigned char idx);
	TActionParam getAction(unsigned char idx);

	void setAttack(bool b);

	bool mercy();
	bool isSpared();
	bool isDead();
	TEntityInfo& getInfo();
	sf::Sprite getHPIndicator();
	sf::IntRect getRect();


	virtual void update(float dt);

	virtual void attack(
		sf::Vector2f player_position,
		sf::FloatRect rect,
		std::vector<SimpleProjectile*>& bullets_vec,
		size_t enemies_count
	);
	
	virtual bool isAttacking();
	
	virtual sf::Sprite getShape();
	
	virtual std::vector<TActionParam> getActMenu();

};

