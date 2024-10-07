#pragma once

#include "Game.h"



void Game::checkActions()
{
	m_player->setCanMove(0);

	sf::View& view = getView();
	sf::Vector2f view_size = view.getSize();
	sf::Vector2f view_center = view.getCenter();
	sf::Vector2f view_position = view_center - view_size / 2.f;

	switch (m_config.current_action_index)
	{
	case 1: {

		switch (m_action_state)
		{
		case 0: {
			makeDialogue("Hello", 1, 1);
		}break;

		case 1: {
			m_player->setAnimationDirection(ANIMATION_UP);
			if (view.getCenter().y >= m_player->getCenter().y - 200)
				view.move(sf::Vector2f(0, -2 * m_delta_time));
			else
				nextAction();
		} break;
			
		case 2: {
			makeDialogue("AHAHAHAHHAHAHAHAHAHAHAHAHAHA\nAHAHAHAHAHAHA\nAHAHAHAHAHHAHAHAHAHA\nAHAHAHHA\nHAAHA\nAHAHAHHAH", 1, 1);
		}break;

		case 3: {
			m_game_state = TGameState::ACT;
			
			sf::Texture* t = new sf::Texture;
			t->loadFromFile("Images/monster.png");
			initBattle(
				{
					new NoiseEnemy(
						view_center,
						view_size,
						sf::IntRect(0, 0, 128, 128)
					),
					new FrogEnemy(
						view_center,
						view_size,
						sf::IntRect(0, 0, 128, 128)
					)
				}
			);
		} break;

		case 4: {
			if (view.getCenter().y <= m_player->getCenter().y)
				view.move(sf::Vector2f(0, 2 * m_delta_time));
			else
				nextAction();
		}break;
		case 5: {
			makeDialogue("wtf bro?", 1, 1);
		}break;
		default: {
			m_player->setCanMove(1);
			m_player->resetValues();
		} break;
		}
	} break;

	}
}

