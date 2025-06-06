#include "logics/MainGame.hpp"

#include "CONSTANTS/OPERATION.hpp"
#include "handlers/BloonManager.hpp"
#include "handlers/BloonWaveManager.hpp"
#include "handlers/ClickHandler.hpp"
#include "handlers/MonkeyManager.hpp"
#include "handlers/ProjectileManager.hpp"
#include "layout/GameText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

#include "map/implementation/BaseMap.hpp"
#include "map/implementation/IceMap.hpp"
#include "map/implementation/PeacefulMap.hpp"
#include "map/implementation/SummonMap.hpp"
#include "map/implementation/TeleportMap.hpp"
#include "map/implementation/SecretMap.hpp"


namespace logics {

MainGame::MainGame() {
	// initialize monkey manager
	m_monkey_manager = std::make_shared<handlers::MonkeyManager>();

	// initialize projectile manager
	m_projectile_manager = std::make_shared<handlers::ProjectileManager>();

	// initialize bloon manager
	m_bloon_manager = std::make_shared<handlers::BloonManager>();
	m_wave_manager = std::make_shared<handlers::BloonWaveManager>();

	// TODO:
	// MOVE TO UI
	m_hp_text = std::make_shared<layout::GameText>("HP", 30);
	m_money_text = std::make_shared<layout::GameText>("money", 30);
	m_wave_text = std::make_shared<layout::GameText>("wave", 30);
	m_hp_text->m_Transform.translation = {360,330};
	m_money_text->m_Transform.translation = {360,280};
	m_wave_text->m_Transform.translation = {360,230};

	AddChild(m_map);
	AddChild(m_monkey_manager);
	AddChild(m_bloon_manager);
	AddChild(m_projectile_manager);
	AddChild(m_click_handler);
	AddChild(m_hp_text);
	AddChild(m_money_text);
	AddChild(m_wave_text);

	auto background_background = std::make_shared<Util::GameObject>();
	background_background->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/wood_background.png"));
	background_background->SetZIndex(-1);
	AddChild(background_background);
	background_background->m_Transform.translation = {300,0};
}

void MainGame::init(const CONSTANTS::TYPE::MAP& map_type) {
	m_monkey_manager->clear_all_monkeys();
	m_projectile_manager->clear_all_projectiles();

	// bloon manager clear
	m_bloon_manager->clear();
	m_wave_manager->reset();

	RemoveChild(m_map);
	// initialize map object
	switch (map_type) {
		case CONSTANTS::TYPE::MAP::SUMMON: {
			auto map = std::make_shared<map::implementation::SummonMap>();
			// map->
			m_map = map;
		}
		break;
		case CONSTANTS::TYPE::MAP::PEACEFUL:
			m_map = std::make_shared<map::implementation::PeacefulMap>();
		break;
		case CONSTANTS::TYPE::MAP::ICE:
			m_map = std::make_shared<map::implementation::IceMap>();
		break;
		case CONSTANTS::TYPE::MAP::TELEPORT:
			m_map = std::make_shared<map::implementation::TeleportMap>();
		break;
		case CONSTANTS::TYPE::MAP::SECRET:
			m_map = std::make_shared<map::implementation::SecretMap>();
		break;
		default: break;
	}
	AddChild(m_map);

	// get path manager from map object
	auto m_path_manager = m_map->get_path_manager();

	// initialize click manager
	RemoveChild(m_click_handler);
	m_click_handler = std::make_shared<handlers::ClickHandler>(m_path_manager, m_monkey_manager, m_wave_manager, m_money_text);
	m_click_handler->set_monkey_obstacles(m_map->get_obstacles());
	AddChild(m_click_handler);

	// resets next game state
	m_game_next_state = CONSTANTS::TYPE::GAME_STATE::NO_CHANGE;

	// hp display
	// TODO: UI
	m_hp_text->set_value(CONSTANTS::OPERATION::GAME_HP);
	m_money_text->set_value(CONSTANTS::OPERATION::MONEY);
	m_wave_text->set_value(1);
}

void MainGame::update() {
	if (m_game_next_state != CONSTANTS::TYPE::GAME_STATE::NO_CHANGE) return;

	m_wave_manager->update(m_bloon_manager);

	m_map->set_wave(m_wave_manager->get_current_wave_number());
	m_map->update();

	// bloons update
	m_bloon_manager->update(m_map->get_path_manager(), m_wave_manager->get_current_tick(), m_hp_text);

	// monkey targeting
	m_monkey_manager->scan_bloons(
		m_bloon_manager->get_bloons_by_front(),
		m_bloon_manager->get_bloons_by_back(),
		m_bloon_manager->get_bloons_by_strong()
	);
	m_monkey_manager->process_attacks(); // add new projectiles if the monkey attacks

	// add new projectiles from monkey manager
	m_projectile_manager->add_new_projectiles(
		m_monkey_manager->get_new_projectiles()
	);

	// remove projectiles from monkey manager
	m_monkey_manager->clear_new_projectiles();

	// projectile update (mostly just collision check)
	m_projectile_manager->update(
		m_bloon_manager->get_all_bloons()
	);

	// update money
	// TODO: UI
	m_money_text->add_value(m_bloon_manager->get_accumulated_money());

	// update wave
	// TODO: UI
	m_wave_text->set_value(m_wave_manager->get_current_wave_number());

	// hp display
	// TODO: UI
	m_hp_text->update();
	m_money_text->update();
	m_wave_text->update();

	// get mouse pos
	auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
	glm::vec2 mouse_pos = {
		 mouse_ptsd_pos.x,
		-mouse_ptsd_pos.y
	};

	bool left_button = Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
	bool right_button = Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB);
	// monkey place controller first
	m_click_handler->update_monkey_placement_controller(
		mouse_pos,
		left_button,
		right_button,
		m_money_text
	);
	// then handles clickable objects
	m_click_handler->update(
		mouse_pos,
		left_button
	);

	// this will decide what the next game screen will be
	if (m_click_handler->should_goto_map_selector()) {
		m_game_next_state = CONSTANTS::TYPE::GAME_STATE::MAP_SELECTOR;
	}
	else if (m_click_handler->should_exit_game()) {
		m_game_next_state = CONSTANTS::TYPE::GAME_STATE::EXIT_GAME;
	}
	else if (m_hp_text->get_value() <= 0) {
		m_game_next_state = CONSTANTS::TYPE::GAME_STATE::GAME_END_SCREEN;
		m_player_won_state = CONSTANTS::TYPE::END_SCREEN::FAILED;
	}
	else if (m_wave_manager->is_all_waves_completed()) {
		m_game_next_state = CONSTANTS::TYPE::GAME_STATE::GAME_END_SCREEN;
		m_player_won_state = CONSTANTS::TYPE::END_SCREEN::WON;
	}

	// utility
	// R for route display toggle
	if (Util::Input::IsKeyUp(Util::Keycode::R)) {
		m_map->toggle_show_route();
	}

	// cheat codes
	// W for skip wave
	if (!m_wave_manager->is_wave_in_progress() && Util::Input::IsKeyUp(Util::Keycode::W)) {
		m_wave_manager->_CHEAT_CODE_ADD_ROUND();
	}
	// M for money hacks
	if (Util::Input::IsKeyUp(Util::Keycode::M)) {
		m_money_text->set_value(99999999);
	}
	// H for HP hacks
	if (Util::Input::IsKeyUp(Util::Keycode::H)) {
		m_hp_text->set_value(99999999);
	}
	// D for death (set HP to 1)
	if (Util::Input::IsKeyUp(Util::Keycode::D)) {
		m_hp_text->set_value(1);
	}
}

}
