#pragma once

#include "Game.h"

void Game::initGame()
{
	sf::Texture* p_texture = new sf::Texture;
	sf::Texture* battle_bg_texture = new sf::Texture;
	sf::Texture* act_fight_texture = new sf::Texture;
	m_map_texture = new sf::Texture();
	m_dialogue_menu_bg_texture = new sf::Texture();
	m_act_dialogue_bg_texture = new sf::Texture();

	m_dialogue_menu_bg_texture->loadFromFile("Images/dialogue.png");
	m_act_dialogue_bg_texture->loadFromFile("Images/dialogue.png");

	m_font.loadFromFile("Fonts/Pixel Emulator.otf");

	battle_bg_texture->loadFromFile("Images/battle-background-1.png");
	act_fight_texture->loadFromFile("Images/fight-area.png");
	p_texture->loadFromFile("Images/casey.png");

	m_act_fight_area.setTexture(*act_fight_texture);

	m_full_screen_shape = sf::RectangleShape(
		sf::Vector2f(getWindowWidth(), getWindowHeight())
	);

	// act buttons

	std::string button_file_pathes[8] = {
		"Images/Buttons/fight-button-on.png",
		"Images/Buttons/act-button-on.png",
		"Images/Buttons/item-button-on.png",
		"Images/Buttons/mercy-button-on.png",

		"Images/Buttons/fight-button-off.png",
		"Images/Buttons/act-button-off.png",
		"Images/Buttons/item-button-off.png",
		"Images/Buttons/mercy-button-off.png"
	};

	for (size_t i = 0; i < 4; ++i)
	{
		m_act_active_buttons_textures[i] = new sf::Texture();
		m_act_active_buttons_textures[i]->loadFromFile(button_file_pathes[i]);
	}

	for (size_t i = 0; i < 4; ++i)
	{
		m_act_inactive_buttons_textures[i] = new sf::Texture();
		m_act_inactive_buttons_textures[i]->loadFromFile(button_file_pathes[4 + i]);
	}

	m_dialogue_text_show_speed = .5f;
	m_dialogue_text_index = 0;
	
	m_transition_base_speed_1 = 25;
	m_transition_speed = m_transition_base_speed_1;
	
	m_fight_indifier.setSize({ 10, 140 });
	m_fight_indifier.setFillColor(sf::Color(0,0,0, 120));
	m_fight_indifier.setOutlineColor(sf::Color::White);
	m_fight_indifier.setOutlineThickness(2);
	m_fight_indifier_pos = 0;
	m_fight_indifier_speed = .1f;
	m_alpha = 0;
	m_to_new_level = false;
	m_window = getWindowPtr();
	m_game_state = TGameState::USUAL;
	m_player = std::make_shared<Player>(
		sf::FloatRect(471, 280, 21, 21),
		*p_texture
		);
	m_battle_bg.setTexture(*battle_bg_texture);

	// sounds
	m_battle_music1 = new sf::Music;
	m_battle_music1->openFromFile("Audio/rude_buster.ogg");
	m_battle_music1->setVolume(5.7f);
}

void Game::initLevel(int level_i)
{
	std::string i = std::to_string(level_i);
	m_colliders = m_level.loadFromFile("Maps/" + i + ".csv");
	m_map_texture->loadFromFile("Images/Maps/" + i + ".png");
	m_action_state = 0;
	m_battle_rect = sf::FloatRect(
		0, 0, 200, 100
	);
	m_level_sprite = sf::Sprite(*m_map_texture);
	m_level_sprite.setScale(
		sf::Vector2f(TILE_SCALE, TILE_SCALE)
	);

	m_player->reset();
	m_player->setCollidersMap(m_colliders);


	getView().setCenter(m_player->getCenter());
	updateViewPosition();
}

void Game::initBattle(std::vector<Enemy*> enemies)
{
	m_battle_music1->setLoop(1);
	m_battle_music1->play();
	m_act_select_enemy_arrow = 0;
	m_act_select_3_arrow = 0;
	m_current_attack_enemies = enemies;

	m_battle_max_coin_revard = 0;
	m_battle_max_exp_revard = 0;

	m_dialogue_text_index = 0;
	
	m_dialogue_text_show_speed = .5f;
	m_act_menu_index = 0;
	m_heart.setPosition(
		getView().getCenter() - m_heart.getSize() / 2.f
	);
	m_player->setCanMove(1);
	// m_player->resetValues();
}
