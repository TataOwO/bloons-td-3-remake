#include "App.hpp"

#include "Constants.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "handlers/BloonManager.hpp" // Add this include

void App::Start() {
	LOG_TRACE("Start");

	// TODO: MOVE ALL THESE TO MAPS
	// route
	std::vector<std::shared_ptr<map::route::Route>> route_vec1 = {
		std::make_shared<map::route::Route>(glm::vec2(215,0), glm::vec2(157, 158)),
		std::make_shared<map::route::Route>(glm::vec2(157, 158), glm::vec2(406, 57)),
		std::make_shared<map::route::Route>(glm::vec2(406, 57), glm::vec2(443,183)),
		std::make_shared<map::route::Route>(glm::vec2(443,183), glm::vec2(262,209)),
		std::make_shared<map::route::Route>(glm::vec2(262,209), glm::vec2(116,413)),
		std::make_shared<map::route::Route>(glm::vec2(116,413), glm::vec2(316,462)),
		std::make_shared<map::route::Route>(glm::vec2(316,462), glm::vec2(352,453)),
		std::make_shared<map::route::Route>(glm::vec2(352,453), glm::vec2(397,345)),
		std::make_shared<map::route::Route>(glm::vec2(397,345), glm::vec2(537,239)),
		std::make_shared<map::route::Route>(glm::vec2(537,239), glm::vec2(563,195)),
		std::make_shared<map::route::Route>(glm::vec2(563,195), glm::vec2(581,111)),
		std::make_shared<map::route::Route>(glm::vec2(581,111), glm::vec2(632,149)),
		std::make_shared<map::route::Route>(glm::vec2(632,149), glm::vec2(652,215)),
		std::make_shared<map::route::Route>(glm::vec2(652,215), glm::vec2(624,328)),
		std::make_shared<map::route::Route>(glm::vec2(624,328), glm::vec2(572,462)),
		std::make_shared<map::route::Route>(glm::vec2(572,462), glm::vec2(485,460)),
		std::make_shared<map::route::Route>(glm::vec2(485,460), glm::vec2(480,497)),
		std::make_shared<map::route::Route>(glm::vec2(480,497), glm::vec2(428,604)),
		std::make_shared<map::route::Route>(glm::vec2(428,604), glm::vec2(319,573)),
		std::make_shared<map::route::Route>(glm::vec2(319,573), glm::vec2(185,559)),
		std::make_shared<map::route::Route>(glm::vec2(185,559), glm::vec2(82,720)),
	};

	// route paths
	std::vector<std::shared_ptr<map::route::RoutePath>> route_paths = {
		std::make_shared<map::route::RoutePath>(route_vec1),
	};

	// add route paths to manager
	m_path_manager = std::make_shared<handlers::PathManager>(route_paths, m_render_manager);

	// initialize monkey manager
	m_monkey_manager = std::make_shared<handlers::MonkeyManager>(m_render_manager);

	// initialize bloon manager
	m_bloon_manager = std::make_shared<handlers::BloonManager>(m_render_manager, m_path_manager);

	// initialize projectile manager
	m_projectile_manager = std::make_shared<handlers::ProjectileManager>(m_render_manager);

	// initialize click manager
	m_click_handler = std::make_shared<handlers::ClickHandler>(m_render_manager, m_path_manager, m_monkey_manager);

	// background
	// TODO: MAP OBJECT
	background.set_layers(background_images);
	for (auto layer: background.get_layers()) {
		m_render_manager->AddChild(layer);
	}

	// hp display
	// TODO: UI
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