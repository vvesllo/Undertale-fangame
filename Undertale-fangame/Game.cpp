#include "Game.h"

Game::Game(
	size_t window_width,
	size_t window_height,
	std::string window_title
)
{
	initWindow(
		window_width,
		window_height,
		window_title,
		60
	);
	initGame();
	initLevel(0);
	initView(
		sf::FloatRect(
			0, 0, // x y
			getWindowWidth(),
			getWindowHeight()
		),
		sf::Vector2f(getWindowWidth(), getWindowHeight()) / (2.f * VIEW_SCALE)
	);
	setBackgroundColor(sf::Color(0, 0, 0));
	setDeltaTimeK(16000.f);
}

void Game::selfUpdate()
{
	m_delta_time = getDeltaTime();
	if (m_game_state == TGameState::USUAL) stateWalkUpdate();
	else if (m_game_state == TGameState::BATTLE || m_game_state == TGameState::ACT) stateBattleUpdate();

	if (m_show_dialogue || m_act_show_dialogue)
	{
		if (m_dialogue_text_index < m_dialogue_text_length)
			m_dialogue_text_index += m_dialogue_text_show_speed;
	}
	else
		m_dialogue_text_index = 0;

	if (m_do_transition)
	{
		m_alpha += int(m_transition_speed * m_delta_time);
		if (m_alpha >= 240 && m_transition_speed > 0)
		{
			m_transition_speed = -m_transition_speed;
			if (m_to_new_level) initLevel(m_config.current_map);
			if (m_battle_end)
			{
				m_act_state = TActState::SELECT_ACT;
				m_game_state = TGameState::USUAL;
			}
		}
		if (m_alpha < std::abs(m_transition_speed * m_delta_time))
		{
			m_battle_end = 0;
			m_to_new_level = 0;
			m_do_transition = false;
			m_player->setCanMove(1);
		}
		m_full_screen_shape.setFillColor(sf::Color(0, 0, 0, m_alpha));
	}
	m_dir = { 0,0 };
}

void Game::checkKeys()
{
	if (!m_player->getCanMove()) return;
	if (m_game_state == TGameState::ACT) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_dir.x = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_dir.x = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_dir.y = -1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) m_dir.y = 1;
}

void Game::pollEvent(sf::Event _event)
{
	switch (_event.type)
	{
	case sf::Event::Closed:
		m_window->close();
		return;
	case sf::Event::KeyPressed:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (m_is_dialogue)
			{
				nextAction();
				m_show_dialogue = false;
				m_is_dialogue = false;
			}

			if (m_game_state == TGameState::ACT)
			{
				m_dialogue_text_index = 0;
				switch (m_act_state)
				{
				case TActState::SELECT_ACT:
					m_act_state = TActState::SELECT_ENEMY;
					break;
				case TActState::SELECT_ENEMY:

					if (m_act_menu_index == 3 || m_act_menu_index == 0)
					{
						if (m_current_attack_enemies[m_act_select_enemy_arrow]->isDead() || m_current_attack_enemies[m_act_select_enemy_arrow]->isSpared()) return;
						m_act_state = TActState::CURRENT_ACTION_RESULT;
					}
					else
						m_act_state = TActState::CURRENT_ACTION;

					if (m_act_menu_index == 0) m_fight_indifier_pos = 0;
					if (m_act_menu_index == 2)
					{
						m_player->getInventory().at(m_act_select_3_arrow)->use(m_player->getInfo());
						m_act_state = TActState::CURRENT_ACTION_RESULT;
					}
					break;

				case TActState::CURRENT_ACTION:
					if (m_act_menu_index == 1)
						m_current_attack_enemies[m_act_select_enemy_arrow]->doAction(m_act_select_2_arrow);

					else if (m_act_menu_index == 2)
						m_player->getInventory().erase(
							m_player->getInventory().begin() + m_act_select_3_arrow
						);
					m_act_state = TActState::CURRENT_ACTION_RESULT;
					break;

				case TActState::CURRENT_ACTION_RESULT:
					m_act_state = TActState::CHECK_ENEMIES;
					break;

				case TActState::END:
					m_transition_speed = m_transition_base_speed_1;
					m_battle_end = 1;
					m_do_transition = 1;
					break;
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if (m_game_state == TGameState::ACT)
			{
				switch (m_act_state)
				{
				case TActState::CURRENT_ACTION:
					m_dialogue_text_index = 0;
					m_act_state = TActState::SELECT_ENEMY;
					break;
				case TActState::SELECT_ENEMY:
					m_dialogue_text_index = 0;
					m_act_state = TActState::SELECT_ACT;
					break;
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_game_state == TGameState::ACT)
			{
				if (m_act_state == TActState::CURRENT_ACTION)
				{
					if (m_act_menu_index == 1)
					{
						if (m_act_select_2_arrow > 0)
							m_act_select_2_arrow--;
					}
				}
				else if (m_act_state == TActState::SELECT_ENEMY)
				{
					if (m_act_menu_index == 2)
					{
						if (m_act_select_3_arrow > 0)
							m_act_select_3_arrow--;
					}
					else
					{
						if (m_act_select_enemy_arrow > 0)
							m_act_select_enemy_arrow--;
					}

				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_game_state == TGameState::ACT)
			{

				if (m_act_state == TActState::CURRENT_ACTION)
				{
					if (m_act_menu_index == 1)
					{
						if (m_act_select_2_arrow < m_current_attack_enemies[m_act_select_enemy_arrow]->getActMenu().size() - 1)
							m_act_select_2_arrow++;
					}
				}
				else if (m_act_state == TActState::SELECT_ENEMY)
				{
					if (m_act_menu_index == 2)
					{
						if (m_act_select_3_arrow < m_player->getInventory().size() - 1)
							m_act_select_3_arrow++;
					}
					else
					{
						if (m_act_select_enemy_arrow < m_current_attack_enemies.size() - 1)
							m_act_select_enemy_arrow++;
					}
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_act_state == TActState::SELECT_ACT)
			{
				if (++m_act_menu_index > 3)
					m_act_menu_index = 0;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_act_state == TActState::SELECT_ACT)
			{
				if (--m_act_menu_index < 0)
					m_act_menu_index = 3;
			}
		}
		return;
	}
}

void Game::draw()
{
	if (m_game_state == TGameState::USUAL) stateWalkDraw();
	else if (m_game_state == TGameState::BATTLE || m_game_state == TGameState::ACT) stateBattleDraw();
	//drawColliders();

	if (m_show_dialogue)
		m_window->draw(m_dialogue_menu_sprite);

	if (m_do_transition)
		m_window->draw(m_full_screen_shape);
}
