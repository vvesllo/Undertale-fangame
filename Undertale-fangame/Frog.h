#pragma once

#include "Enemy.h"


class FrogEnemy : public Enemy
{
private:
	float m_attack_cooldown;

	float m_tick;
	float m_move_ampletude;
	float m_move_speed;

	float m_attack_speed;
	float m_attack_timer;

	float m_dt;
	sf::Sprite m_head_shape;
	sf::Sprite m_body_shape;
	sf::Sprite m_damaged_shape;


	Animation m_body_animation;
	Animation m_head_animation;

protected:
	// animation
	void initAnimation();
	void updateAnimation(float dt);

public:
	FrogEnemy(
		sf::Vector2f view_center,
		sf::Vector2f view_size,
		sf::IntRect rect
	);

	void attack(
		sf::Vector2f player_position,
		sf::FloatRect rect,
		std::vector<SimpleProjectile*>& bullets_vec,
		size_t enemies_count
	) override;
	void update(float dt) override;
	sf::Sprite getShape() override;
};