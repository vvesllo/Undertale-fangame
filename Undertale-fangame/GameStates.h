#pragma once

#include "Game.h"

// When casey go brbrbrbrbbrrbrbrbrrrbrbrbrbrb
void Game::stateWalkDraw()
{
	m_window->draw(m_level_sprite);
	m_window->draw(m_player->getShape());
}

void Game::stateWalkUpdate()
{
	m_player->setDirection(m_dir);
	m_player->update(m_delta_time, m_config);

	m_full_screen_shape.setPosition(0, 0);
	if (m_player->checkGotoNewLevel())
	{
		m_transition_speed = m_transition_base_speed_1;
		m_do_transition = true;
		m_to_new_level = true;
		m_player->setCanMove(0);
	}

	if (m_player->checkNewAction())
		checkActions();
	else
		updateViewPosition();

	m_full_screen_shape.setPosition(
		getView().getCenter() - sf::Vector2f(getWindowWidth(), getWindowHeight()) / 2.f
	);
}

// When heart go brbrbrbrbbrrbrbrbrrrbrbrbrbrb
void Game::stateBattleDraw()
{
	sf::Vector2f view_center = getView().getCenter();
	sf::Vector2f view_size = getView().getSize();

	m_battle_area.setSize(
		sf::Vector2f(m_battle_rect.width, m_battle_rect.height)
	);

	m_battle_area.setFillColor(sf::Color::Black);
	m_battle_area.setOutlineThickness(2);
	m_battle_area.setOutlineColor(sf::Color::White);

	m_battle_rect.left = view_center.x - m_battle_rect.width / 2.f;
	m_battle_rect.top = view_center.y - m_battle_rect.height / 2.f;

	m_battle_area.setPosition(
		m_battle_rect.left, m_battle_rect.top
	);
	m_battle_bg.setPosition(
		view_center - sf::Vector2f(640, 480) / 2.f
	);

	m_window->draw(m_battle_bg);


	for (size_t i = 0; i < m_current_attack_enemies.size(); i++)
	{
		m_current_attack_enemies[i]->update(m_delta_time);
		m_window->draw(m_current_attack_enemies[i]->getShape());
	}



	if (m_game_state == TGameState::BATTLE)
	{
		m_full_screen_shape.setFillColor(sf::Color(0, 0, 0, 120));
		m_window->draw(m_full_screen_shape);
		m_window->draw(m_battle_area);
		m_window->draw(m_heart.getShape());
		for (size_t i = 0; i < m_enemy_bullets.size(); i++)
			m_window->draw(
				m_enemy_bullets[i]->getShape()
			);
	}
	else if (m_game_state == TGameState::ACT)
	{
		sf::Sprite button;
		for (size_t i = 0; i < 4; i++)
		{
			if (m_act_state == 0)
			{
				if (m_act_menu_index == i)
					button.setTexture(*m_act_active_buttons_textures[i]);
				else
					button.setTexture(*m_act_inactive_buttons_textures[i]);
			}
			else
				button.setTexture(*m_act_inactive_buttons_textures[i]);
			sf::Vector2u size = button.getTexture()->getSize();
			button.setPosition(
				view_center.x - view_size.x / 2 + size.x * i,
				view_center.y + view_size.y / 2 - size.y
			);
			m_window->draw(button);
		}


		m_battle_enemy_killed = false;
		if (m_battle_all_died)
		{
			m_act_state = TActState::END;
		}
		switch (m_act_state)
		{
		case TActState::SELECT_ACT:
			m_act_select_enemy_arrow = 0;
			m_window->draw(makeDialogueInAct("* Something on da way", 1));
			break;
		case TActState::SELECT_ENEMY:
			if (m_act_menu_index == 0 ||
				m_act_menu_index == 1 ||
				m_act_menu_index == 3)
			{
				std::string list = "";
				for (size_t i = 0; i < m_current_attack_enemies.size(); i++)
				{
					if (m_act_select_enemy_arrow == i)
						list += "> ";
					else 
						list += "* ";
					list += m_current_attack_enemies[i]->getInfo().name + '\n';
				}
				sf::Sprite dialogue = makeDialogueInAct(list, 0);
				m_window->draw(dialogue);
				for (size_t i = 0; i < m_current_attack_enemies.size(); i++)
				{
					sf::Sprite indicator = m_current_attack_enemies[i]->getHPIndicator();
					indicator.setPosition(
						{
							view_center.x,
							dialogue.getPosition().y + 25 + (25 * i)
						}
					);
					m_window->draw(indicator);
				}
			}
			else
			{
				std::vector<Item*> inventory = m_player->getInventory();
				std::string inv_list;
				for (size_t i = 0; i < inventory.size(); i++)
				{
					if (m_act_select_3_arrow == i)
						inv_list += "> ";
					else
						inv_list += "* ";
					inv_list += inventory.at(i)->getInfo().title +'\n';
				}
				
				sf::Sprite menu = makeDialogueInAct(inv_list, 0);
				sf::RenderTexture menu_t;
				sf::Vector2u t_size = menu.getTexture()->getSize();
				sf::Vector2f pos = menu.getPosition();
				sf::Text desc;



				desc.setPosition(t_size.x/2, 20);
				desc.setFont(m_font);
				desc.setCharacterSize(TEXT_SIZE);
				desc.setString(inventory.at(m_act_select_3_arrow)->getInfo().description);
				desc.setFillColor(sf::Color(0xaa, 0xaa, 0xaa, 0xff));

				menu_t.create(t_size.x, t_size.y);
				
				menu.setPosition(0,0);
				menu_t.draw(menu); 
				menu_t.draw(desc);
				
				menu_t.display();

				sf::Sprite new_menu(menu_t.getTexture());
				new_menu.setPosition(pos);
				m_window->draw(
					new_menu
				);
			}
			break;


		case TActState::CURRENT_ACTION:
			if (m_act_menu_index == 1)
			{
				std::string res="";
				std::vector<TActionParam> actions = m_current_attack_enemies[m_act_select_enemy_arrow]->getActMenu();
				for (size_t i = 0; i < actions.size(); i++)
				{
					if (m_act_select_2_arrow == i)
						res += "> ";
					else
						res += "* ";
					res += actions.at(i).action_name + '\n';
				}
				m_window->draw(
					makeDialogueInAct(
						res, 0
					)
				);
			}
			break;
		case TActState::CURRENT_ACTION_RESULT:
			if (m_act_menu_index == 0)
				drawAttack(
					view_center,
					view_size
				);
			else if (m_act_menu_index == 1)
			{
				m_window->draw(
					makeDialogueInAct(
						m_current_attack_enemies[m_act_select_enemy_arrow]->getActionResultText(m_act_select_2_arrow),
						1
					)
				);
			}
			else if (m_act_menu_index == 2)
			{
				m_window->draw(
					makeDialogueInAct(
						m_player->getInventory().at(m_act_select_3_arrow)->getResultText(),
						1
					)
				);
			}
			else if (m_act_menu_index == 3)
			{
				Enemy* enemy = m_current_attack_enemies[m_act_select_enemy_arrow];
				if (enemy->mercy())
				{
					m_window->draw(
						makeDialogueInAct(
							"You spared " + enemy->getInfo().name,
							1
						)
					);
				}
				else
				{
					m_window->draw(
						makeDialogueInAct(
							"No mercy\nOnly kill",
							1
						)
					);
				}
			}
			break;
		case TActState::CHECK_ENEMIES:
			
			if (m_act_menu_index == 0)
			{
				Enemy* enemy = m_current_attack_enemies[m_act_select_enemy_arrow];
				int damage = m_player->getInfo().damage - short(m_player->getInfo().damage * std::abs(m_fight_damage_indifier));
				enemy->getInfo().hp -= damage;
				if (enemy->isDead()) checkEnemies();
			}
			
			else if (m_act_menu_index == 3)
			{
				m_current_attack_enemies[m_act_select_enemy_arrow]->mercy();
			}
			m_act_state = TActState::FINISH;
			if (std::count_if(
					m_current_attack_enemies.begin(),
					m_current_attack_enemies.end(),
					[](Enemy* enemy) { return enemy->isSpared() || enemy->isDead(); }
				) != m_current_attack_enemies.size())
				m_game_state = TGameState::BATTLE;
			else
			{
				nextAction();
				m_act_state = TActState::END;
			}
			break;
		case TActState::FINISH:
			{
				m_dialogue_text_index = 0;
				m_battle_active = false;
				m_heart.setPosition(
					sf::Vector2f(
						m_battle_rect.left + m_battle_rect.width / 2 - m_heart.getSize().x / 2,
						m_battle_rect.top + m_battle_rect.height / 2 - m_heart.getSize().y / 2
					)
				);
				m_act_state = TActState::SELECT_ACT;
			}
			break;
		case TActState::END:
			m_battle_music1->stop();
			m_window->draw(makeDialogueInAct(
				std::format("You win\nAnd get {} exp and {} coins",
					m_battle_max_exp_revard, m_battle_max_coin_revard), 
				1));
			break;
		}
	}
}

void Game::stateBattleUpdate()
{
	m_battle_all_died = m_current_attack_enemies.size() == 0;
	
	if (m_game_state == TGameState::BATTLE)
	{
		for (size_t i = 0; i < m_current_attack_enemies.size(); i++)
		{
			Enemy* enemy = m_current_attack_enemies.at(i);
			if (enemy->isSpared() || enemy->isDead()) continue;
			if (!m_battle_active)
				enemy->setAttack(1);
			enemy->attack(
				m_heart.getCenter(),
				m_battle_rect,
				m_enemy_bullets, 
				std::count_if(
					m_current_attack_enemies.begin(),
					m_current_attack_enemies.end(),
					[](Enemy* enemy) { return !(enemy->isSpared() || enemy->isDead()); }
				)
			);
			if (!enemy->isAttacking())
			{
				for (size_t i = 0; i < m_enemy_bullets.size(); i++)
				{
					delete m_enemy_bullets[i];
					m_enemy_bullets.erase(
						m_enemy_bullets.begin() + i
					);
				}

				m_enemy_bullets.clear();

				m_game_state = TGameState::ACT;

				return;
			}
		}

		m_battle_active = true;
		
		for (size_t i = 0; i < m_enemy_bullets.size(); i++)
		{
			m_enemy_bullets[i]->update(
				m_delta_time,
				m_heart.getCenter()
			);
			if (m_enemy_bullets[i]->can_be_deleted)
			{
				delete m_enemy_bullets[i];
				m_enemy_bullets.erase(
					m_enemy_bullets.begin() + i
				);
			}
		}


		m_heart.setDirection(m_dir);
		m_heart.update(
			m_battle_rect,
			m_delta_time,
			m_game_state
		);
	}
	else
	{
		if (m_act_menu_index == 0) m_fight_indifier_pos += m_fight_indifier_speed;
	}
}

void Game::checkEnemies()
{
	Enemy* enemy = m_current_attack_enemies.at(m_act_select_enemy_arrow);
	if (!enemy->isSpared())
		m_battle_max_exp_revard += enemy->getInfo().exp;
	m_battle_max_coin_revard += enemy->getInfo().coins;
	m_battle_enemy_killed = false;
}

void Game::drawAttack(
	sf::Vector2f view_center,
	sf::Vector2f view_size
)
{
	m_fight_damage_indifier = -std::cos((M_PI / 6) * m_fight_indifier_pos);
	m_act_fight_area.setPosition(
		view_center.x - 620 / 2,
		view_center.y + view_size.y / 2 - 180 - m_act_active_buttons_textures[0]->getSize().y
	);

	m_fight_indifier.setPosition(
		view_center.x - m_fight_indifier.getSize().x / 2 + 280 * m_fight_damage_indifier,
		view_center.y + view_size.y / 2 - 160 - m_act_active_buttons_textures[0]->getSize().y
	);
	m_window->draw(m_act_fight_area);
	m_window->draw(m_fight_indifier);
}

void Game::drawActMenu(
	sf::Vector2f view_center,
	sf::Vector2f view_size
)
{
	m_fight_damage_indifier = -std::cos((M_PI / 6) * m_fight_indifier_pos);
	m_act_fight_area.setPosition(
		view_center.x - 620 / 2,
		view_center.y + view_size.y / 2 - 180 - m_act_active_buttons_textures[0]->getSize().y
	);

	m_fight_indifier.setPosition(
		view_center.x - m_fight_indifier.getSize().x / 2 + 280 * m_fight_damage_indifier,
		view_center.y + view_size.y / 2 - 160 - m_act_active_buttons_textures[0]->getSize().y
	);
	m_window->draw(m_act_fight_area);
	m_window->draw(m_fight_indifier);
}
