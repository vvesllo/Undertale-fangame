#include "Projectile.h"


SimpleProjectile::SimpleProjectile(
    sf::Vector2f position,
    sf::Vector2f dir,
    std::function<void(SimpleProjectile* bullet, sf::Vector2f)> ai
)
{
    can_be_deleted = false;
    m_ai = ai;
    m_dir = dir;
    m_position = position;
    m_shape.setPosition(position);
    m_shape.setSize(sf::Vector2f(4, 4));
    m_acceleration = 0;
}

void SimpleProjectile::setDirection(sf::Vector2f dir)
{
    m_dir = dir;
}

void SimpleProjectile::AI(std::function<void(SimpleProjectile* bullet, sf::Vector2f)> ai)
{
    m_ai = ai;
}

void SimpleProjectile::update(
    float dt,
    sf::Vector2f player_position
)
{
    m_acceleration += 0.1f * dt;
    m_ai(
        this,
        player_position
    );
}

float SimpleProjectile::getAcceleration()
{
    return m_acceleration;
}

sf::RectangleShape& SimpleProjectile::getObject()
{
    return m_shape;
}

sf::RectangleShape SimpleProjectile::getShape()
{
    return m_shape;
}

sf::Vector2f SimpleProjectile::getPostion()
{
    return m_shape.getPosition();
}

sf::Vector2f SimpleProjectile::getDirection()
{
    return m_dir;
}
