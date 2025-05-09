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

ClickHandler::ClickHandler(const std::shared_ptr<handlers::PathManager>& path_manager, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager) {
	m_monkey_placement_manager = std::make_shared<placement::MonkeyPlacementController>(path_manager, monkey_manager);
	AddChild(m_monkey_placement_manager);

	auto dart_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::DART, glm::vec2{288,120});
	auto super_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::SUPER, glm::vec2{336,120});
	auto ice_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::ICE, glm::vec2{384,120});
	auto bomb_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::BOMB, glm::vec2{432,120});
	auto tack_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::TACK, glm::vec2{288,72});
	auto boomer_button = m_add_new_monkey_placement_button(placement::PLACABLE_TYPE::BOOMERANG, glm::vec2{336,72});
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

	for (auto& button: m_button_vec) {
		if (button->shall_be_removed()) {
			m_button_removal_queue.push_back(button);
			continue;
		}

		if (!LB) continue;

		// breaks when a clickable is successfully clicked
		if (button->process_click(mouse_pos)) break;
	}

	// removes clickable
	remove_clickable(m_removal_queue);
	m_removal_queue.clear();
	// removes buttons
	remove_button(m_button_removal_queue);
	m_button_removal_queue.clear();
}

void ClickHandler::update_monkey_placement_controller(const glm::vec2 & mouse_pos, const bool left_button, const bool right_button, const std::shared_ptr<layout::GameText> &current_money) const {
	m_monkey_placement_manager->set_mouse_pos(mouse_pos);
	m_monkey_placement_manager->update();

	// if right clicks, clear all
	if (right_button) m_monkey_placement_manager->clear_all();
	// if left clicks, try to place monkey
	// if monkey is placed successfully, clear all
	if (left_button && m_monkey_placement_manager->place_monkey(current_money)) m_monkey_placement_manager->clear_all();
}

void ClickHandler::set_monkey_obstacles(const std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>>& obstcbles) {
	m_monkey_placement_manager->set_monkey_obstacles(obstcbles);
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

void ClickHandler::remove_button(const std::vector<std::shared_ptr<layout::Button>>& b_vec) {
	for (auto& b: b_vec) {
		auto it = std::find(m_button_vec.begin(), m_button_vec.end(), b);

		if (it == m_button_vec.end()) continue;

		m_button_vec.erase(it);
	}
}

std::shared_ptr<layout::Button> ClickHandler::m_add_new_monkey_placement_button(const placement::PLACABLE_TYPE& type, const glm::vec2& pos) {
	// creates new button
	std::shared_ptr<layout::Button> new_button = std::make_shared<layout::Button>();

	// initialize button's GameObject
	new_button->SetZIndex(CONSTANTS::Z_INDEX_CONSTANTS::IN_GAME_BUTTONS);
	new_button->m_Transform.scale = {0.5f, 0.5f};
	new_button->SetVisible(true);

	// initialize button's Clickable
	new_button->m_Transform.translation = pos;
	new_button->set_hitbox(std::make_shared<hitboxes::CircularHitbox>(pos, 15));
	new_button->set_removal([]() {
		return false;
	});
	new_button->set_on_click([mpm = m_monkey_placement_manager, t=type]() {
		mpm->set_monkey(t);
		return true;
	});

	// adds button to corresponding handlers
	m_button_vec.push_back(new_button);
	AddChild(new_button);

	switch (type) {
	case placement::PLACABLE_TYPE::DART:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/dart.png"));
	break;
	case placement::PLACABLE_TYPE::BOOMERANG:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/boomerang.png"));
	break;
	case placement::PLACABLE_TYPE::SUPER:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/super.png"));
	break;
	case placement::PLACABLE_TYPE::BOMB:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/bomb.png"));
	break;
	case placement::PLACABLE_TYPE::TACK:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/tack.png"));
	break;
	case placement::PLACABLE_TYPE::ICE:
		new_button->SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/ice.png"));
	break;
	default: break;
	}

	return new_button;
}

ClickHandler::~ClickHandler() {
	
}

}
