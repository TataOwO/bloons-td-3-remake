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

#include "handlers/BloonWaveManager.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"
#include "hitboxes/HitboxGroup.hpp"
#include "Util/Image.hpp"

namespace handlers {

ClickHandler::ClickHandler(const std::shared_ptr<handlers::PathManager>& path_manager, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager, const std::shared_ptr<handlers::BloonWaveManager>& bloon_wave_manager) : m_bloon_wave_manager(bloon_wave_manager) {
	m_monkey_placement_manager = std::make_shared<placement::MonkeyPlacementController>(path_manager, monkey_manager);
	AddChild(m_monkey_placement_manager);

	auto dart_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::DART, glm::vec2{288,120});
	add_existing_button(dart_button);
	auto super_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::SUPER, glm::vec2{336,120});
	add_existing_button(super_button);
	auto ice_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::ICE, glm::vec2{384,120});
	add_existing_button(ice_button);
	auto bomb_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::BOMB, glm::vec2{432,120});
	add_existing_button(bomb_button);
	auto tack_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::TACK, glm::vec2{288,72});
	add_existing_button(tack_button);
	auto boomer_button = m_add_new_monkey_placement_button(CONSTANTS::TYPE::PLACABLE::BOOMERANG, glm::vec2{336,72});
	add_existing_button(boomer_button);

	// map button
	auto map_button = std::make_shared<layout::Button>();
	map_button->m_Transform.translation = {390,-345};
	map_button->SetZIndex(CONSTANTS::Z_INDEX::IN_GAME_BUTTONS);
	// map button hitbox
	auto map_button_hitbox = std::make_shared<hitboxes::HitboxGroup>();
	std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>> map_button_hitboxes = {};
	map_button_hitboxes.push_back(std::make_shared<hitboxes::CircularHitbox>(glm::vec2{375,-345}, 15));
	map_button_hitboxes.push_back(std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{390,-345},glm::vec2{30,30},0));
	map_button_hitboxes.push_back(std::make_shared<hitboxes::CircularHitbox>(glm::vec2{405,-345}, 15));
	map_button_hitbox->add_hitboxes(map_button_hitboxes);
	map_button->set_hitbox(map_button_hitbox);
	// on click
	map_button->set_on_click([ms=m_map_state]() {
		*ms = true;
		std::cout << "map button clicked" << std::endl;
		return true;
	});
	map_button->set_removal([]() {
		return false;
	});
	// map button drawable
	map_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/map.png"));
	map_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/map_yellow.png"));
	// add to children
	add_existing_button(map_button);

	// exit button
	auto exit_button = std::make_shared<layout::Button>();
	exit_button->m_Transform.translation = {450,-345};
	exit_button->SetZIndex(CONSTANTS::Z_INDEX::IN_GAME_BUTTONS);
	// exit button hitbox
	auto exit_button_hitbox = std::make_shared<hitboxes::HitboxGroup>();
	std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>> exit_button_hitboxes = {};
	exit_button_hitboxes.push_back(std::make_shared<hitboxes::CircularHitbox>(glm::vec2{435,-345}, 15));
	exit_button_hitboxes.push_back(std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{450,-345},glm::vec2{30,30},0));
	exit_button_hitboxes.push_back(std::make_shared<hitboxes::CircularHitbox>(glm::vec2{465,-345}, 15));
	exit_button_hitbox->add_hitboxes(exit_button_hitboxes);
	exit_button->set_hitbox(exit_button_hitbox);
	// on click
	exit_button->set_on_click([me=m_exit_state]() {
		*me = true;
		std::cout << "exit button clicked" << std::endl;
		return true;
	});
	exit_button->set_removal([]() {
		return false;
	});
	// exit button drawable
	exit_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/exit.png"));
	exit_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/exit_yellow.png"));
	// add to children
	add_existing_button(exit_button);
	
	// wave button
	m_wave_button = std::make_shared<layout::Button>();
	m_wave_button->m_Transform.translation = {360,-240};
	m_wave_button->SetZIndex(CONSTANTS::Z_INDEX::IN_GAME_BUTTONS);
	// wave button hitbox
	m_wave_button->set_hitbox(std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{360,-240},glm::vec2{240,180},0));
	// on click
	m_wave_button->set_on_click([bwm=bloon_wave_manager]() {
		bwm->set_spawn_new_wave();
		std::cout << "wave button clicked" << std::endl;
		return true;
	});
	m_wave_button->set_removal([]() {
		return false;
	});
	// wave button drawable
	m_wave_button->set_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/start_wave.png"));
	m_wave_button->set_hover_drawable(std::make_shared<Util::Image>(RESOURCE_DIR"/images/buttons/start_wave_hover.png"));
	// add to children
	add_existing_button(m_wave_button);
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

		// breaks when a clickable is successfully clicked
		if (button->update(mouse_pos, LB)) break;
	}
	
	// wave button updates
	if (m_bloon_wave_manager->is_wave_in_progress()) m_wave_button->disable();
	else m_wave_button->enable();
	
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

void ClickHandler::set_monkey_obstacles(const std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>>& obstcbles) const {
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

void ClickHandler::add_existing_button(const std::shared_ptr<layout::Button>& new_button) {
	new_button->SetVisible(true);
	m_button_vec.push_back(new_button);
	AddChild(new_button);

}

void ClickHandler::remove_button(const std::vector<std::shared_ptr<layout::Button>>& b_vec) {
	for (auto& b: b_vec) {
		auto it = std::find(m_button_vec.begin(), m_button_vec.end(), b);

		if (it == m_button_vec.end()) continue;

		m_button_vec.erase(it);
	}
}

std::shared_ptr<layout::Button> ClickHandler::m_add_new_monkey_placement_button(const CONSTANTS::TYPE::PLACABLE& type, const glm::vec2& pos) {
	// creates new button
	std::shared_ptr<layout::Button> new_button = std::make_shared<layout::Button>();

	// initialize button's GameObject
	new_button->SetZIndex(CONSTANTS::Z_INDEX::IN_GAME_BUTTONS);
	new_button->m_Transform.scale = {0.5f, 0.5f};

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

	std::string path_prefix = RESOURCE_DIR"/images/buttons/";
	std::string monke_name;

	switch (type) {
	case CONSTANTS::TYPE::PLACABLE::DART:
		monke_name = "dart";
	break;
	case CONSTANTS::TYPE::PLACABLE::BOOMERANG:
		monke_name = "boomerang";
	break;
	case CONSTANTS::TYPE::PLACABLE::SUPER:
		monke_name = "super";
	break;
	case CONSTANTS::TYPE::PLACABLE::BOMB:
		monke_name = "bomb";
	break;
	case CONSTANTS::TYPE::PLACABLE::TACK:
		monke_name = "tack";
	break;
	case CONSTANTS::TYPE::PLACABLE::ICE:
		monke_name = "ice";
	break;
	default: break;
	}
	
	new_button->set_drawable(std::make_shared<Util::Image>(path_prefix + monke_name + ".png"));
	new_button->set_hover_drawable(std::make_shared<Util::Image>(path_prefix + monke_name + "_yellow.png"));

	return new_button;
}

ClickHandler::~ClickHandler() {

}

}
