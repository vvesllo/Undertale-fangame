#pragma once

#include "Enemy.h"


class NoiseEnemy : public Enemy
{
private:
	float m_attack_cooldown;

	float m_tick;
	float m_move_ampletude;
	float m_move_speed;

	float m_attack_speed;
	float m_attack_timer;

	float m_dt;

	Animation m_animation;
	sf::Sprite m_shape;
	sf::Sound m_attack_sound;

protected:
	// animation
	void initAnimation();
	void updateAnimation(float dt);

public:
	NoiseEnemy(
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

private:
	void attackType1(
		sf::Vector2f player_position,
		sf::FloatRect rect,
		std::vector<SimpleProjectile*>& bullets_vec
	);
	void attackType2(
		sf::Vector2f player_position,
		sf::FloatRect rect,
		std::vector<SimpleProjectile*>& bullets_vec
	);
};