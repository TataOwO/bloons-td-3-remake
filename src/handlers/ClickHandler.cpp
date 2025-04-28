#include "handlers/ClickHandler.hpp"

#include <algorithm>
#include <iostream>

#include "hitboxes/CircularHitbox.hpp"
#include "layout/Button.hpp"

namespace handlers {

ClickHandler::ClickHandler(std::shared_ptr<Util::Renderer> render_manager, std::shared_ptr<handlers::PathManager> path_manager, std::shared_ptr<handlers::MonkeyManager> monkey_manager) : m_render_manager(render_manager) {
	m_monkey_placement_manager = std::make_shared<placement::MonkeyPlacementController>(path_manager, monkey_manager);
	m_render_manager->AddChild(m_monkey_placement_manager);
	
	std::shared_ptr<layout::Button> dart_monkey_button = std::make_shared<layout::Button>();
	dart_monkey_button->set_on_click([&]() {
		m_monkey_placement_manager->set_monkey(placement::PLACABLE_TYPE::DART);
		std::cout << "set monkey to dart" << std::endl;
		return true;
	});
	dart_monkey_button->set_removal([&]() {
		return !is_mortal_alive();
	});
	dart_monkey_button->set_hitbox(
		std::make_shared<hitboxes::CircularHitbox>(glm::vec2{360,0}, 30)
	);
	dart_monkey_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/dart.png"));
	dart_monkey_button->SetZIndex(CONSTANTS::Z_INDEX_CONSTANTS::IN_GAME_BUTTONS);
	dart_monkey_button->m_Transform.translation = {360,0};
	dart_monkey_button->SetVisible(true);
	
	m_clickable_vec.push_back(dart_monkey_button);
	m_render_manager->AddChild(dart_monkey_button);
}

void ClickHandler::update(const glm::vec2& mouse_pos, bool LB) {
	for (auto& clickable: m_clickable_vec) {
		if (clickable->shall_be_removed()) {
			m_removal_queue.push_back(clickable);
			continue;
		}
		
		if (!LB) continue;
		
		// breaks when a clickable is successfully clicked
		if (clickable->process_click(mouse_pos)) break;
	}

	remove_clickable(m_removal_queue);
	m_removal_queue.clear();
}

void ClickHandler::update_monkey_placement_controller(const glm::vec2 & mouse_pos, const bool left_button, const bool right_button, const std::shared_ptr<layout::GameText> &current_money) const {
	m_monkey_placement_manager->set_mouse_pos(mouse_pos);
	m_monkey_placement_manager->update();

	if (right_button) m_monkey_placement_manager->clear_all();
	if (left_button) m_monkey_placement_manager->place_monkey(current_money);
}

void ClickHandler::add_clickable(const std::shared_ptr<inputs::Clickable>& clickable) {
	// find position to insert at
	// higher z index should be placed earlier (i hope)
	auto pos = std::lower_bound(
		m_clickable_vec.begin(),
		m_clickable_vec.end(),
		clickable,
		[](const std::shared_ptr<inputs::Clickable>& a, const std::shared_ptr<inputs::Clickable>& b) {return a->get_z_index() > b->get_z_index();} // z index compare
	);

	// insert the thing like yeah
	m_clickable_vec.insert(pos, clickable);
}

void ClickHandler::add_clickables(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec) {
	for (const auto& clickable : c_vec) {
		add_clickable(clickable);
	}
}

void ClickHandler::remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec) {
	for (auto& c: c_vec) {
		auto it = std::find(m_clickable_vec.begin(), m_clickable_vec.end(), c);

		if (it == m_clickable_vec.end()) continue;

		m_clickable_vec.erase(it);
	}
}

}
