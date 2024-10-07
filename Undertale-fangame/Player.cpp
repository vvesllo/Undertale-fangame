#include "Player.h"


Player::Player()
{
}

Player::Player(
	sf::FloatRect rect,
	sf::Texture& texture
)
{
	m_can_move = true;
	m_speed = 5.f;
	m_rect = rect;
	m_sprite_size = sf::Vector2u(
		19, 38
	);
	m_shape.setTexture(texture);
	m_shape.setScale(sf::Vector2f(TILE_SCALE, TILE_SCALE));
	m_new_spawn_point = sf::Vector2f(
		rect.left, rect.top
	);
	m_rect.width *= TILE_SCALE;
	m_rect.height *= TILE_SCALE;
	m_state = ANIMATION_DOWN;
	m_animation_speed = 0.1f;

	m_inventory.push_back(new DirtyMossItem);
	m_inventory.push_back(new CandyItem);
	m_inventory.push_back(new CandyItem);
	m_inventory.push_back(new CandyItem);
	m_inventory.push_back(new CandyItem);
	m_inventory.push_back(new CandyItem);

	m_info.coins = 0;
	m_info.damage = 25;
	m_info.max_hp = 20;
	m_info.hp = m_info.max_hp;
	m_info.name = "casey";

	reset();
	initAnimation();
}

void Player::update(float dt, TConfigStruct& config)
{
	int last_map = config.current_map;
	int last_action_index = config.current_action_index;
	
	TILE_TYPE tile;
	m_rect.left += m_speed * m_direction.x * dt;
	tile = checkCollision(0, config);

	m_rect.top += m_speed * m_direction.y * dt;
	tile = checkCollision(1, config);
	if (config.current_map != last_map)
	{
		m_goto_new_level = true;
		m_new_spawn_point = tile->getSpawnPosition();
	}

	if (config.current_action_index != last_action_index)
		m_new_action = true;


	m_shape.setPosition(m_rect.left, m_rect.top + (m_rect.height - m_sprite_size.y * TILE_SCALE));
	updateAnimation(dt);
	m_direction.y = 0;
	m_direction.x = 0;
}

void Player::initAnimation()
{
	Animation* animation;
	for (short i = 0; i < 4; i++)
	{
		animation = new Animation(4, m_animation_speed);
		for (short j = 0; j < 4; j++)
			animation->add(
				sf::IntRect(m_sprite_size.x*j, m_sprite_size.y*i, m_sprite_size.x, m_sprite_size.y)
			);

		m_animation_manager.add(
			i,
			animation
		);
	}
}

void Player::updateAnimation(float dt)
{	
	if (m_direction.x > 0)		m_state = ANIMATION_RIGHT;
	else if (m_direction.x < 0) m_state = ANIMATION_LEFT;

	else if (m_direction.y > 0) m_state = ANIMATION_DOWN;
	else if (m_direction.y < 0) m_state = ANIMATION_UP;

	Animation* current_animation = m_animation_manager.get(m_state);
	if (m_direction.x == 0 && m_direction.y == 0)
		current_animation->reset();
	else
		current_animation->play();
	current_animation->update(m_shape, dt);
}


void Player::reset()
{
	resetValues();
	m_shape.setPosition(
		m_new_spawn_point
	);
	m_rect.left = m_new_spawn_point.x;
	m_rect.top = m_new_spawn_point.y;
}

void Player::resetValues()
{
	m_goto_new_level = false;
	m_new_action = false;
}

TILE_TYPE Player::checkCollision(char direction, TConfigStruct& config)
{
    for (std::list<TILE_TYPE>::iterator it=m_colliders_map.begin(); it != m_colliders_map.end(); it++)
    {
		TILE_TYPE tile = *it;
        sf::FloatRect tile_rect = tile->getRect();
        if (m_rect.intersects(tile_rect))
        {
			switch (tile->getType())
			{
				case TTileType::SOLID:
				{
					if ((m_direction.x > 0) && (direction == 0)) m_rect.left = tile_rect.left - m_rect.width;
					if ((m_direction.x < 0) && (direction == 0)) m_rect.left = tile_rect.left + tile_rect.width;

					if ((m_direction.y > 0) && (direction == 1)) m_rect.top = tile_rect.top - m_rect.height;
					if ((m_direction.y < 0) && (direction == 1)) m_rect.top = tile_rect.top + tile_rect.height;
				} break;

				case TTileType::CHANGE_LEVEL:
				{
					if (!m_goto_new_level)
						config.current_map = tile->getIndex();
				} return tile;

				case TTileType::ACTION:
				{
					if (tile->getIndex() == config.current_action_index)
					{
						config.current_action_index++;
						return tile;
					}
				}
			}
        }
    }
	return std::make_shared<Tile>(
		sf::FloatRect(
			0, // x-pos
			0, // y-pos
			0, // width
			0  // height
		),
		sf::Color::Black,
		TTileType::SOLID,
		sf::Vector2f(0, 0),
		0
		);
}

void Player::setAnimationDirection(short dir) { m_state = dir; }

void Player::setPosition(sf::Vector2f position)
{
	m_rect.left = position.x;
	m_rect.top = position.y;
	m_shape.setPosition(m_rect.left, m_rect.top);
}
void Player::setCanMove(bool b) { m_can_move = b; }
void Player::setDirection(sf::Vector2f direction) { m_direction = direction; }
void Player::setCollidersMap(std::list<TILE_TYPE> map) { m_colliders_map = map; }


bool Player::checkGotoNewLevel() { return m_goto_new_level; }
bool Player::checkNewAction() { return m_new_action; }

TEntityInfo& Player::getInfo() { return m_info; }
bool Player::getCanMove() { return m_can_move;}
sf::FloatRect Player::getRect() { return m_rect; }
sf::Vector2f Player::getCenter() { return sf::Vector2f(m_rect.left + m_rect.width / 2, m_rect.top + m_rect.height / 2); }
sf::Vector2f Player::getPosition() { return sf::Vector2f(m_rect.left, m_rect.top); }
std::vector<Item*>& Player::getInventory() { return m_inventory; }
sf::Sprite Player::getShape() { return m_shape; }