#include "Frog.h"


FrogEnemy::FrogEnemy(
	sf::Vector2f view_center,
	sf::Vector2f view_size,
	sf::IntRect rect
)
{
	m_tick = 0.f;
	m_move_ampletude = 0.1f;
	m_move_speed = 0.05f;

	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile("Images/Enemies/frog.png");
	m_damaged_shape.setTexture(*texture);
	m_damaged_shape.setTextureRect(
		{256, 0, 128, 120});
	m_damaged_shape.setPosition({ 300, 80 });

	m_head_shape.setTexture(*texture);
	m_head_shape.setPosition({ 300, 80 });

	m_body_shape.setTexture(*texture);
	m_body_shape.setPosition({ 300, 120 });

	TEntityInfo info;
	info.name = "Frog";
	info.max_hp = 50;
	info.hp = info.max_hp;
	info.damage = 2;
	info.exp = 10;
	info.coins = 20;

	m_dt = 0;
	m_attack_speed = 0.1f;
	m_attack_timer = 0;
	m_attack_cooldown = 0;
	initEnemy(
		rect,
		info,
		view_center,
		view_size
	);
	initAnimation();
}

void FrogEnemy::update(float dt)
{
	m_dt = dt;

	if (!(isSpared() || isDead()))
	{
		sf::Vector2f position = m_head_shape.getPosition();

		position.y += m_move_ampletude * -std::cos(M_PI / 6 * m_tick) * dt;
		position.x += m_move_ampletude * 2 * -std::cos(M_PI / 6 * m_tick * 2) * dt;

		m_tick += m_move_speed * dt;
		m_attack_timer += m_attack_speed * dt;
		m_head_shape.setPosition(position);


		updateAnimation(dt);


		if (is_attacking)
		{
			m_attack_cooldown += m_attack_speed;
			if (m_attack_cooldown > 30)
				is_attacking = false;
		}
		else
			m_attack_cooldown = 0;
	}
	else
		m_damaged_shape.setColor(inactive_color);
}

void FrogEnemy::initAnimation()
{
	m_head_animation = Animation(2, 0.03f);
	m_body_animation = Animation(2, 0.03f);

	// head
	m_head_animation.add(
		sf::IntRect(0, 0, 128, 64)
	);
	m_head_animation.add(
		sf::IntRect(128, 0, 128, 64)
	);

	// body
	m_body_animation.add(
		sf::IntRect(0, 64, 128, 73)
	);
	m_body_animation.add(
		sf::IntRect(128, 64, 128, 73)
	);

	m_head_animation.play();
	m_body_animation.play();
}

void FrogEnemy::updateAnimation(float dt)
{
	m_head_animation.update(m_head_shape, dt);
	m_body_animation.update(m_body_shape, dt);
}

void FrogEnemy::attack(
	sf::Vector2f player_position,
	sf::FloatRect rect,
	std::vector<SimpleProjectile*>& bullets_vec,
	size_t enemies_count
)
{

	if (m_attack_timer > 3)
	{
		sf::Vector2f position(rect.left + rect.width / 2, rect.top - 20);

		sf::Vector2f dir = normVec2f(player_position - position);
		dir = rotateVec2f(dir, 30 - std::rand() % 30);

		bullets_vec.push_back(
			new SimpleProjectile(
				{ player_position.x, position.y },
				dir,
				[=](SimpleProjectile* bullet, sf::Vector2f pl_pos) {
					if (bullet->getPostion().y < rect.top + rect.height)
					{
						bullet->getObject().setSize(sf::Vector2f(10, 10));
						bullet->getObject()
							.move(
								dir * m_dt * 1.2f
							);
					}
					else
						bullet->can_be_deleted = true;
				}
			)
		);
		m_attack_timer = 0;
	}
}

sf::Sprite FrogEnemy::getShape()
{
	sf::RenderTexture* render_texture = new sf::RenderTexture;
	render_texture->create(
		getViewSize().x, getViewSize().y
	);

	if (isSpared() || isDead())
	{
		render_texture->draw(m_damaged_shape);
	}
	else {

		render_texture->draw(m_body_shape);
		render_texture->draw(m_head_shape);

	}

	render_texture->display();

	sf::Sprite result(render_texture->getTexture());
	result.setPosition(
		getPosition()
	);

	return result;
}