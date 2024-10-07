#pragma once

#include "Game.h"




void Game::updateViewPosition()
{
	sf::View& view = getView();

	sf::Vector2f temp_view_position = m_player->getCenter();
	// X
	if (m_player->getCenter().x - view.getSize().x / 2 < 0)
		temp_view_position.x = view.getSize().x / 2;
	else if (m_player->getCenter().x + view.getSize().x / 2 > m_level.getMaxWidth())
		temp_view_position.x = m_level.getMaxWidth() - view.getSize().x / 2;

	// Y
	if (m_player->getCenter().y - view.getSize().y / 2 < 0)
		temp_view_position.y = view.getSize().y / 2;
	else if (m_player->getCenter().y + view.getSize().y / 2 > (m_level.getMaxHeight()))
		temp_view_position.y = m_level.getMaxHeight() - view.getSize().y / 2;

	view.setCenter(temp_view_position);

}

void Game::makeDialogue(std::string text, char position, bool type_effect)
{
	m_show_dialogue = true;
	m_is_dialogue = true;
	sf::RenderTexture* texture = new sf::RenderTexture();
	sf::Text render_text;
	render_text.setStyle(sf::Text::Regular);
	texture->create(
		m_dialogue_menu_bg_texture->getSize().x,
		m_dialogue_menu_bg_texture->getSize().y
	);
	std::string result;
	m_dialogue_text_length = text.length();
	if (!type_effect)
		m_dialogue_text_index = m_dialogue_text_length;
	for (size_t i = 0; i < m_dialogue_text_index; i++)
		result += text[i];

	render_text.setString(result);
	render_text.setFillColor(sf::Color::White);
	render_text.setFont(m_font);
	render_text.setCharacterSize(TEXT_SIZE);
	render_text.setPosition(sf::Vector2f(40, 20));

	texture->draw(sf::Sprite(*m_dialogue_menu_bg_texture));
	texture->draw(render_text);

	texture->display();
	m_dialogue_menu_sprite.setTexture(texture->getTexture());

	if (position == 1)
		m_dialogue_menu_sprite.setPosition(
			{
				getView().getCenter().x - texture->getSize().x / 2.f,
				getView().getCenter().y - getView().getSize().y / 2
			}
	);
	else if (position == 0)
		m_dialogue_menu_sprite.setPosition(
			{
				getView().getCenter().x - texture->getSize().x / 2,
				getView().getCenter().y - texture->getSize().y / 2
			}
	);
	else if (position == -1)
		m_dialogue_menu_sprite.setPosition(
			{
				getView().getCenter().x - texture->getSize().x / 2.f,
				getView().getCenter().y - texture->getSize().y + getView().getSize().y / 2
			}
	);
}

sf::Sprite Game::makeDialogueInAct(std::string text, bool type_effect)
{
	sf::RenderTexture* texture = new sf::RenderTexture();
	sf::Text render_text;
	sf::Vector2f view_center = getView().getCenter();
	sf::Vector2f view_size = getView().getSize();
	m_act_show_dialogue = true;
	texture->create(
		m_act_dialogue_bg_texture->getSize().x,
		m_act_dialogue_bg_texture->getSize().y
	);

	std::string result;
	m_dialogue_text_length = text.length();
	if (!type_effect)
		m_dialogue_text_index = m_dialogue_text_length;
	for (size_t i = 0; i < int(m_dialogue_text_index); i++)
	{
		if (i >= text.length())
			break;
		result += text[i];
	}

	render_text.setString(result);
	render_text.setFillColor(sf::Color::White);
	render_text.setFont(m_font);
	render_text.setCharacterSize(TEXT_SIZE);
	render_text.setPosition(sf::Vector2f(40, 20));

	texture->draw(sf::Sprite(*m_dialogue_menu_bg_texture));
	texture->draw(render_text);

	texture->display();

	sf::Sprite menu(texture->getTexture());
	
	menu.setPosition(
		view_center.x - texture->getSize().x / 2,
		view_center.y + view_size.y / 2 - texture->getSize().y - m_act_active_buttons_textures[0]->getSize().y
	);

	return menu;
}

// TODO: dont forgot about disable in release build
void Game::drawColliders()
{
	for (std::list<TILE_TYPE>::iterator it = m_colliders.begin(); it != m_colliders.end(); it++)
		m_window->draw((*it)->getShape());
	sf::CircleShape circle(2.f);
	circle.setPosition((getView().getCenter() - sf::Vector2f(5, 5)));
	m_window->draw(circle);
	circle.setFillColor(sf::Color::Red);
	circle.setPosition((getView().getCenter() - sf::Vector2f(5, 5)) - sf::Vector2f(200, 104) / 2.f);
	m_window->draw(circle);

	circle.setFillColor(sf::Color::Red);
	circle.setPosition((getView().getCenter() - sf::Vector2f(5, 5)) + sf::Vector2f(200, -104) / 2.f);
	m_window->draw(circle);
}

inline void Game::nextAction()
{
	m_dialogue_text_index = 0;
	m_action_state++;
}