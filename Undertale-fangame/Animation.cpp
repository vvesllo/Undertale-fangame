#include "Animation.h"
#include <iostream>
Animation::Animation()
{
	m_frame_count = 0;
	m_speed = 0;
	m_current_frame = 0;
	m_paused = false;
}

Animation::Animation(
	size_t frame_count,
	float speed
)
{
	m_frame_count = frame_count;
	m_speed = speed;
	m_current_frame = 0;
	m_paused = false;
}

void Animation::update(sf::Sprite& sprite, float dt)
{
	if (m_paused) return;
	m_current_frame += m_speed * dt;
	if (m_current_frame >= m_frame_count)
		m_current_frame = 0;
	sprite.setTextureRect(m_frame_rects[int(m_current_frame)]);
}

void Animation::reset()
{
	m_current_frame = 0;
}

void Animation::toggle()
{
	m_paused = !m_paused;
}

void Animation::stop()
{
	m_paused = true;
	reset();
}

void Animation::play()
{
	m_paused = false;
}

void Animation::pause()
{
	m_paused = true;
}

void Animation::add(sf::IntRect rect)
{
	m_frame_rects.push_back(rect);
}
