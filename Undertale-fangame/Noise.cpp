#include "Noise.h"

#include <iostream>

NoiseEnemy::NoiseEnemy(
	sf::Vector2f view_center,
	sf::Vector2f view_size,
	sf::IntRect rect
)
{
	m_tick = 0.f;
	m_move_ampletude = 0.1f;
	m_move_speed = 0.05f;
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("Images/Enemies/noise.png");
	m_shape.setTexture(*texture);
	m_shape.setPosition({100, 60});
	
	TEntityInfo info;

	info.name = "Bad Noise";
	info.max_hp = 30;
	info.hp = info.max_hp;
	info.damage = 2;
	info.exp = 10;
	info.coins = 20;

	m_dt = 0;
	m_attack_speed = 0.1f;
	m_attack_timer = 0;
	m_attack_cooldown = 0;

	addAction(
		TActionParam{
			"Call",
			"Call result",
			100
		}
	);

	addAction(
		TActionParam{
			"Call2",
			"Call2 result",
			1
		}
	);

	m_attack_sound = sf::Sound(*createBuffer("Audio/sfx/attack2.wav"));
	initEnemy(
		rect,
		info,
		view_center,
		view_size
	);
	initAnimation();
}

void NoiseEnemy::update(float dt)
{
	m_dt = dt;
	if (!(isSpared() || isDead()))
	{
		if (is_attacking)
		{
			m_attack_timer += m_attack_speed * dt;
			m_attack_cooldown += m_attack_speed;
			if (m_attack_cooldown > 30)
				is_attacking = false;
		}
		else
		{
			m_attack_timer = 0;
			m_attack_cooldown = 0;
		}
		updateAnimation(dt);
		sf::Vector2f position = m_shape.getPosition();

		position.y += m_move_ampletude * std::cos(M_PI / 6 * m_tick) * dt;

		m_tick += m_move_speed * dt;
		m_shape.setPosition(position);
	}
	else
		m_shape.setColor(inactive_color);
}

void NoiseEnemy::initAnimation()
{
	m_animation = Animation(3, 0.1f);

	m_animation.add(
		sf::IntRect(0, 0, 128, 128)
	);
	m_animation.add(
		sf::IntRect(128, 0, 128, 128)
	);
	m_animation.add(
		sf::IntRect(256, 0, 128, 128)
	);

	m_animation.play();
}

void NoiseEnemy::updateAnimation(float dt)
{
	m_animation.update(m_shape, dt);
}

void NoiseEnemy::attack(
	sf::Vector2f player_position,
	sf::FloatRect rect,
	std::vector<SimpleProjectile*>& bullets_vec,
	size_t enemies_count
)
{

	if (enemies_count > 1)
	{
		attackType1(
			player_position,
			rect,
			bullets_vec
		);
	}
	else
	{
		attackType2(
			player_position,
			rect,
			bullets_vec
		);
	}
}

sf::Sprite NoiseEnemy::getShape()
{
	sf::RenderTexture* render_texture = new sf::RenderTexture;
	render_texture->create(
		getViewSize().x, getViewSize().y
	);
	render_texture->draw(m_shape);
	render_texture->display();
	sf::Sprite result(render_texture->getTexture());
	result.setPosition(
		getPosition()
	);
	return result;
}

void NoiseEnemy::attackType1(
	sf::Vector2f player_position, 
	sf::FloatRect rect, 
	std::vector<SimpleProjectile*>& bullets_vec)
{

	if (m_attack_timer > 1)
	{
		sf::Vector2f position(rect.left + rect.width / 2, rect.top - 20);

		position.x = rect.left + rand() % int(rect.width);
		sf::Vector2f dir = normVec2f(player_position - position);

		bullets_vec.push_back(
			new SimpleProjectile(
				position,
				dir,
				[=](SimpleProjectile* bullet, sf::Vector2f player_position) {
					if (bullet->getPostion().y < rect.top + rect.height)
					{
						bullet->getObject()
							.move(
								dir * m_dt
							);
					}
				}
			)
		);
		m_attack_sound.play();
		m_attack_timer = 0;
	}
}

void NoiseEnemy::attackType2(
	sf::Vector2f player_position, 
	sf::FloatRect rect, 
	std::vector<SimpleProjectile*>& bullets_vec)
{
	if (m_attack_timer > 2)
	{

		sf::Vector2f position(rect.left + rect.width / 2, rect.top - 20);
		position.x = rect.left + rand() % int(rect.width);
		sf::Vector2f dir = normVec2f(player_position - position);

		for (size_t i = 0; i < 360; i += 360 / 5)
		{
			bullets_vec.push_back(
				new SimpleProjectile(
					position,
					dir * 2.f,
					[=](SimpleProjectile* bullet, sf::Vector2f player_position) {

						bullet->getObject()
						.move(
							rotateVec2f(bullet->getDirection(), i) * m_dt
						);
						bullet->getObject().setSize(sf::Vector2f(6, 3));
						bullet->getObject().rotate(3);
						bullet->setDirection(bullet->getDirection() * 0.99f);
					}
				)
			);
		}
		m_attack_sound.play();
		m_attack_timer = 0;
	}
}
