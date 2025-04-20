#include "App.hpp"

#include <iostream>
#include <cstring>
#include <cstdlib>

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

	// background
	// TODO: MAP OBJECT
	background.set_layers(background_images);
	for (auto layer: background.get_layers()) {
		m_render_manager->AddChild(layer);
	}

	// hp display
	// TODO: UI
	status_text_obj->SetColor(Util::Color(255,255,255));

	status_display->SetDrawable(status_text_obj);
	m_render_manager->AddChild(status_display);
	status_display->SetZIndex(10);
	status_display->m_Transform.translation = {365, 300};
	m_CurrentState = State::UPDATE;

	// monke placeholder
	monkey_place_holder->SetDrawable(dart_img);
	m_render_manager->AddChild(monkey_place_holder);
	monkey_place_holder->SetZIndex(10);
}

void App::Update() {
	++game_tick;

	// spawn random bloons
	// TODO: WAVES
	if (game_tick % 20 - 10 == 0) {
		m_bloon_manager->spawn_random_bloon();
	}

	// bloons update
	m_bloon_manager->update(game_tick, game_hp, &money_changed);

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
	int ret_money = m_bloon_manager->get_accumulated_money();
	money += ret_money;

	money_changed |= ret_money != 0;

	// hp display
	// TODO: UI
	if (money_changed) {
		status_text = "hp: ";
		status_text.append(std::to_string(game_hp));
		status_text.append("\nmoney: ");
		status_text.append(std::to_string(money));
		status_text_obj->SetText(status_text);
		money_changed = false;
	}

	// place monkey
	if (Util::Input::IsMouseMoving()) {
		monke_place_hold_has_collision = false;
		auto mouse_ptsd_pos = Util::Input::GetCursorPosition();
		glm::vec2 mouse_pos = {mouse_ptsd_pos.x, mouse_ptsd_pos.y};
		mouse_pos.y = -mouse_pos.y;

		monkey_place_holder->m_Transform.translation = mouse_pos;
		monke_placeholder_hitbox->set_position(mouse_pos);

		for (auto route : m_path_manager->get_all_routes()) {
			auto other = route->get_hitbox();
			if (!utility::hitboxes_are_collided(monke_placeholder_hitbox, other)) continue;

			monke_place_hold_has_collision = true;
			monkey_place_holder->SetDrawable(dart_red);
		}
		if (!monke_place_hold_has_collision) {
			if (m_monkey_manager->hitbox_is_collided_with_monkeys(monke_placeholder_hitbox)) {
				monke_place_hold_has_collision = true;
				monkey_place_holder->SetDrawable(dart_red);
			}
		}
		if (!monke_place_hold_has_collision) monkey_place_holder->SetDrawable(dart_img);
	}

	// Places monkey
	if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && !monke_place_hold_has_collision) {
		glm::vec2 monke_pos = monke_placeholder_hitbox->get_position();
		if (m_monkey_manager->place_dart_monkey(monke_pos, money)) {
			money_changed = true;
		}
	}

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