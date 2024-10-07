#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

Enemy::Enemy(
	sf::Vector2f position,
	sf::IntRect rect,
	sf::Texture& texture,
	TEntityInfo info
)
{
	initEnemy(
		rect, 
		info,
		{0, 0},
		{0, 0}
	);
	initAnimation();
}

void Enemy::update(float dt)
{
	updateAnimation(dt);
}

void Enemy::setAttack(bool b)
{
	is_attacking = b;
}

void Enemy::attack(
	sf::Vector2f player_position,
	sf::FloatRect rect,
	std::vector<SimpleProjectile*>& bullets_vec,
	size_t enemies_count
)
{
}


void Enemy::initAnimation() { }

void Enemy::initEnemy(
	sf::IntRect rect,
	TEntityInfo& info,
	sf::Vector2f view_center,
	sf::Vector2f view_size
)
{
	mercy_k = 0;
	inactive_color = sf::Color(0x80, 0x80, 0x80);

	m_info = info;
	m_rect = rect;

	m_view_size = view_size;
	m_view_center = view_center;
}

void Enemy::updateAnimation(float dt) {}

sf::Vector2f Enemy::getPosition() { return m_view_center - m_view_size / 2.f; }

sf::Vector2f Enemy::getViewSize() { return m_view_size; }

sf::SoundBuffer* Enemy::createBuffer(std::string path_to_file)
{
	sf::SoundBuffer* buf = new sf::SoundBuffer;
	buf->loadFromFile("Audio/sfx/attack2.wav");
	return buf;
}

sf::Vector2f Enemy::getViewCenter() { return m_view_center; }

bool Enemy::mercy() { return (is_spared = mercy_k >= 100); }

bool Enemy::isSpared()
{
	return is_spared;
}

bool Enemy::isDead() { return m_info.hp <= 0; }

bool Enemy::isAttacking() { return is_attacking; }

TEntityInfo& Enemy::getInfo() { return m_info; }

sf::IntRect Enemy::getRect() { return m_rect; }

sf::Sprite Enemy::getShape() { return sf::Sprite(); }

sf::Sprite Enemy::getHPIndicator()
{
	sf::RenderTexture* texture = new sf::RenderTexture;
	texture->create(200, 10);
	texture->clear(sf::Color::Red);
	float a = 200.f * m_info.hp / m_info.max_hp * 1.f;

	sf::RectangleShape shape(sf::Vector2f(a, 10));
	shape.setFillColor(sf::Color::Green);
	texture->draw(shape);

	texture->display();
	return sf::Sprite(texture->getTexture());
}

// Action Menu

void Enemy::addAction(TActionParam param) { m_actions.push_back(param); }

void Enemy::doAction(unsigned char idx) { mercy_k += m_actions[idx].mercy_k; }

std::string Enemy::getActionResultText(unsigned char idx) { return m_actions[idx].action_result_text; }

TActionParam Enemy::getAction(unsigned char idx) { return m_actions[idx]; }

std::vector<TActionParam> Enemy::getActMenu() { return m_actions; }