#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "Application.h"
#include "Player.h"
#include "HeartShapeObject.h"
#include "Level.h"

#include "Enemy.h"
#include "Noise.h"
#include "Frog.h"

#define VIEW_SCALE 1.f
#define TEXT_SIZE 20

typedef enum
{
	SELECT_ACT,
	SELECT_ENEMY,
	CURRENT_ACTION,
	CURRENT_ACTION_RESULT,
	CHECK_ENEMIES,
	FINISH,
	END
} TActState;

class Game: public Application
{
private:
	std::shared_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<Player> m_player;
	std::list<TILE_TYPE> m_colliders;
	std::vector<SimpleProjectile*> m_enemy_bullets;

	sf::RectangleShape m_full_screen_shape;
	sf::Sprite m_level_sprite;
	sf::Sprite m_battle_bg;
	sf::Sprite m_dialogue_menu_sprite;
	sf::Vector2f m_dir;
	sf::Texture* m_map_texture;
	sf::Texture* m_dialogue_menu_bg_texture;
	sf::Texture* m_act_dialogue_bg_texture;
	sf::Font m_font;
	float m_delta_time;

	bool m_do_transition;
	bool m_battle_all_died;
	bool m_battle_enemy_killed;
	bool m_battle_active;
	bool m_battle_end;
	sf::FloatRect m_battle_rect;
	sf::RectangleShape m_battle_area;

	short m_battle_max_coin_revard;
	short m_battle_max_exp_revard;

	TGameState m_game_state;
	Level m_level;
	TConfigStruct m_config;
	HeartShapeObject m_heart;

	int m_transition_speed;
	int m_transition_base_speed_1;
	int m_alpha;
	short m_action_state;
	bool m_to_new_level;

	short m_act_menu_index;
	short m_act_menu_select;
	TActState m_act_state;
	sf::Sprite m_act_fight_area;
	sf::RectangleShape m_fight_indifier;
	float m_fight_indifier_pos;
	float m_fight_indifier_speed;
	float m_fight_damage_indifier;

	unsigned short m_act_select_enemy_arrow;
	unsigned short m_act_select_3_arrow;
	unsigned short m_act_select_2_arrow;
	
	std::vector<Enemy*> m_current_attack_enemies;
	

	sf::Texture* m_act_active_buttons_textures[4];
	sf::Texture* m_act_inactive_buttons_textures[4];
	

	sf::Music* m_battle_music1;


	bool m_is_dialogue;
	bool m_show_dialogue;
	bool m_act_show_dialogue;
	size_t m_dialogue_text_length;
	float m_dialogue_text_index;
	float m_dialogue_text_show_speed;

	// default
	void stateWalkUpdate();
	void stateWalkDraw();
	// battle
	void stateBattleUpdate();
	void stateBattleDraw();

	void nextAction();

	void checkEnemies();
	void initBattle(std::vector<Enemy*> enemies);
	void initGame();
	void initLevel(int level_i);
	void drawColliders();
	void updateViewPosition();
	void checkActions();
	void makeDialogue(std::string text, char position, bool type_effect);
	sf::Sprite makeDialogueInAct(std::string text, bool type_effect);
	
	// state Battle
	void drawAttack(
		sf::Vector2f view_center,
		sf::Vector2f view_size
	);
	void drawActMenu(
		sf::Vector2f view_center,
		sf::Vector2f view_size
	);

protected:
	
	void selfUpdate() override;
	
	void draw() override;
	
	void checkKeys() override;
	
	void pollEvent(sf::Event _event) override;

public:
	Game(
		size_t window_width,
		size_t window_height,
		std::string window_title
	);

};

