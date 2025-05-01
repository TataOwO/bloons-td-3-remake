#include "handlers/ClickHandler.hpp"

#include "Constants.hpp"

#include "handlers/MonkeyManager.hpp"
#include "handlers/PathManager.hpp"
#include "Util/Renderer.hpp"

#include "layout/Button.hpp"
#include "inputs/Clickable.hpp"
#include "Util/GameObject.hpp"

#include "placement/MonkeyPlacementController.hpp"

#include <algorithm>
#include <iostream>

#include "hitboxes/CircularHitbox.hpp"
#include "layout/Button.hpp"
#include "Util/Image.hpp"

namespace handlers {

ClickHandler::ClickHandler(const std::shared_ptr<Util::Renderer> &render_manager, const std::shared_ptr<handlers::PathManager>& path_manager, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager) : m_render_manager(render_manager) {
	m_monkey_placement_manager = std::make_shared<placement::MonkeyPlacementController>(path_manager, monkey_manager);
	m_render_manager->AddChild(m_monkey_placement_manager);
	
	auto button = m_add_new_button(placement::PLACABLE_TYPE::DART);
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
	if (left_button && m_monkey_placement_manager->place_monkey(current_money)) m_monkey_placement_manager->clear_all();
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
		
		auto button = std::dynamic_pointer_cast<layout::Button>(c);
		if (button) m_render_manager->RemoveChild(button);
	}
}

std::shared_ptr<layout::Button> ClickHandler::m_add_new_button(const placement::PLACABLE_TYPE& type) {
	std::shared_ptr<layout::Button> new_button = std::make_shared<layout::Button>();
	
	new_button->SetZIndex(CONSTANTS::Z_INDEX_CONSTANTS::IN_GAME_BUTTONS);
	new_button->m_Transform.scale = {0.5f, 0.5f};
	new_button->SetVisible(true);

	m_clickable_vec.push_back(new_button);
	m_render_manager->AddChild(new_button);

	switch (type) {
	case placement::PLACABLE_TYPE::DART:
		// sets on click behavior
		new_button->set_on_click([mpm = m_monkey_placement_manager]() {
			mpm->set_monkey(placement::PLACABLE_TYPE::DART);
			std::cout << "set monkey to dart" << std::endl;
			return true;
		});
		new_button->set_removal([]() {
			return false;
		});
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/dart.png"));
		new_button->m_Transform.translation = {360,0};
		new_button->set_hitbox(
			std::make_shared<hitboxes::CircularHitbox>(glm::vec2{360,0}, 15)
		);
	default: break;
	}
	
	return new_button;
}

}
