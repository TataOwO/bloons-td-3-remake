#include "App.hpp"

#include "Constants.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "handlers/BloonManager.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

#include "handlers/MonkeyManager.hpp"

#include "map/implementation/IceMap.hpp"
#include "map/implementation/PeacefulMap.hpp"
#include "map/implementation/SummonMap.hpp"
// #include "map/implementation/IceMap.hpp"

void App::Start() {
	LOG_TRACE("Start");

	// initialize map object
	m_map = std::make_shared<map::implementation::SummonMap>();
	m_render_manager->AddChild(m_map);

	// get path manager from map object
	auto m_path_manager = m_map->get_path_manager();

	// initialize monkey manager
	m_monkey_manager = std::make_shared<handlers::MonkeyManager>();
	m_render_manager->AddChild(m_monkey_manager);

	// initialize bloon manager
	m_bloon_manager = std::make_shared<handlers::BloonManager>(m_path_manager);
	m_render_manager->AddChild(m_bloon_manager);

	// initialize projectile manager
	m_projectile_manager = std::make_shared<handlers::ProjectileManager>();
	m_render_manager->AddChild(m_projectile_manager);

	// initialize click manager
	m_click_handler = std::make_shared<handlers::ClickHandler>(m_path_manager, m_monkey_manager);
	m_render_manager->AddChild(m_click_handler);
	m_click_handler->set_monkey_obstacles(m_map->get_obstacles());

	// hp display
	// TODO: UI
	m_hp_text = std::make_shared<layout::GameText>("HP", 30);
	m_money_text = std::make_shared<layout::GameText>("money", 30);
	m_hp_text->set_value(CONSTANTS::OPERATION_CONSTANTS::GAME_HP);
	m_money_text->set_value(CONSTANTS::OPERATION_CONSTANTS::MONEY);
	m_render_manager->AddChild(m_hp_text);
	m_render_manager->AddChild(m_money_text);
	m_hp_text->m_Transform.translation = {360,330};
	m_money_text->m_Transform.translation = {360,280};
}

void App::Update() {
	++game_tick;

	// spawn random bloons
	// TODO: WAVES
	if (game_tick % 20 - 10 == 0) {
		m_bloon_manager->spawn_random_bloon();
	}

	// bloons update
	m_bloon_manager->update(game_tick, m_hp_text);

	// monkey targetting
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

	// hp display
	// TODO: UI
	m_hp_text->update();
	m_money_text->update();

	// get mouse pos
	auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
	glm::vec2 mouse_pos = {
		 mouse_ptsd_pos.x,
		-mouse_ptsd_pos.y
	};

	// monkey place controller first
	m_click_handler->update_monkey_placement_controller(
		mouse_pos,
		Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB),
		Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB),
		m_money_text
	);
	// then handles clickable objects
	m_click_handler->update(
		mouse_pos,
		Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)
	);

	m_render_manager->Update();

	/*
	 * Do not touch the code below as they serve the purpose for
	 * closing the window.
	 */
	if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
		Util::Input::IfExit()) {
		m_CurrentState = State::END;
	}
}

void App::End() { // NOLINT(this method will mutate members in the future)
	LOG_TRACE("End");
}