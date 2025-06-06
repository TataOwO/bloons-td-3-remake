#include "placement/MonkeyPlacementController.hpp"

#include "Util/Image.hpp"
#include <iostream>

#include "constants/MONKEY.hpp"
#include "handlers/MonkeyManager.hpp"
#include "handlers/PathManager.hpp"
#include "hitboxes/CircularHitbox.hpp"
#include "utility/functions.hpp"
#include "CONSTANTS/Z_INDEX.hpp"

namespace placement {

MonkeyPlacementController::MonkeyPlacementController(
	const std::shared_ptr<handlers::PathManager> &path_manager,
	const std::shared_ptr<handlers::MonkeyManager> &monkey_manager)
	: m_path_manager(path_manager), m_monkey_manager(monkey_manager) {

	m_hitbox = std::make_shared<hitboxes::CircularHitbox>(glm::vec2(0, 0), m_default_hitbox_radius);

	SetVisible(false);
	SetZIndex(CONSTANTS::Z_INDEX::MONKE + 0.1f);
}

void MonkeyPlacementController::update() {
	if (!m_is_active) return;

	// check position validity and update visuals
	update_visual_state();
}

void MonkeyPlacementController::set_monkey(const CONSTANTS::TYPE::PLACABLE& type) {
	m_current_monkey_type = type;

	if (type == CONSTANTS::TYPE::PLACABLE::_NULL) {
		SetVisible(false);
		m_is_active = false;
		return;
	}
	
	CONSTANTS::MONKEY::Monke monke_stat;

	std::string monke_name = "";
	switch (type) {
	case CONSTANTS::TYPE::PLACABLE::DART:
		monke_name = "dart";
		monke_stat = CONSTANTS::MONKEY::DART;
		break;
	case CONSTANTS::TYPE::PLACABLE::BOOMERANG:
		monke_name = "boomerang";
		monke_stat = CONSTANTS::MONKEY::BOOMERANG;
		break;
	case CONSTANTS::TYPE::PLACABLE::SUPER:
		monke_name = "super";
		monke_stat = CONSTANTS::MONKEY::SUPER;
		break;
	case CONSTANTS::TYPE::PLACABLE::ICE:
		monke_name = "ice";
		monke_stat = CONSTANTS::MONKEY::ICE;
		break;
	case CONSTANTS::TYPE::PLACABLE::BOMB:
		monke_name = "bomb";
		monke_stat = CONSTANTS::MONKEY::BOMB;
		break;
	case CONSTANTS::TYPE::PLACABLE::TACK:
		monke_name = "tack";
		monke_stat = CONSTANTS::MONKEY::TACK;
		break;
	// case CONSTANTS::TYPE::PLACABLE::SPIKE:
		// monke_name = "spike";
		// break;
	// case CONSTANTS::TYPE::PLACABLE::GLUE:
		// monke_name = "glue";
		// break;
	// case CONSTANTS::TYPE::PLACABLE::PINEAPPLE:
		// monke_name = "pineapple";
		// break;
	// case CONSTANTS::TYPE::PLACABLE::VILLAGE:
		// monke_name = "village";
		// break;
	// case CONSTANTS::TYPE::PLACABLE::CATAPULT:
		// monke_name = "catapult";
		// break;
	default:
		SetVisible(false);
		m_is_active = false;
		return;
	}

	m_Transform.scale = {monke_stat.IMAGE_SCALE,monke_stat.IMAGE_SCALE};
	std::string filetype = ".png";

	std::string prefix = RESOURCE_DIR"/images/monke/";
	std::string placable_path = prefix + monke_name + filetype;
	std::string unplacable_path = prefix + monke_name + "_red" + filetype;

	m_placable = std::make_shared<Util::Image>(placable_path, false);
	m_unplacable = std::make_shared<Util::Image>(unplacable_path, false);

	m_Drawable = m_placable;

	// set active and visible
	m_is_active = true;
	SetVisible(true);

	m_Transform.translation = {1000,1000};

	update_visual_state();
}

bool MonkeyPlacementController::check_valid_position() const {
	if (m_current_monkey_type == CONSTANTS::TYPE::PLACABLE::_NULL || !m_is_active || !m_hitbox) {
		return false;
	}

	bool collides_with_route = false;

	// route collision check
	auto collided_route = m_path_manager->get_collided_route(m_hitbox);
	collides_with_route = (collided_route != nullptr);

	// checks if type should be placed on route
	bool is_route_only_type = m_route_only_types.find(m_current_monkey_type) != m_route_only_types.end();

	bool can_be_placed = (is_route_only_type) ? collides_with_route : !collides_with_route;

	if (!can_be_placed) {
		return false;
	}

	// checks collision with other monkeys
	if (m_monkey_manager->hitbox_is_collided_with_monkeys(m_hitbox)) {
		return false;
	}
	
	for (auto& obstacle: m_obstacles) {
		if (utility::hitboxes_are_collided(m_hitbox, obstacle)) return false;
	}

	return true;
}

void MonkeyPlacementController::update_visual_state() {
	bool valid_pos = check_valid_position();

	if (valid_pos == m_current_position_valid) return;

	m_current_position_valid = valid_pos;
	if (m_current_position_valid) m_Drawable = m_placable;
	else m_Drawable = m_unplacable;
}

bool MonkeyPlacementController::is_valid_placement() const {
	return m_current_position_valid;
}

bool MonkeyPlacementController::place_monkey(const std::shared_ptr<layout::GameText> &available_money) const {
	if (!m_is_active || !is_valid_placement() || m_current_monkey_type == CONSTANTS::TYPE::PLACABLE::_NULL) {
		return false;
	}

	bool placement_successful = false;

	glm::vec2 position = m_hitbox->get_position();

	switch (m_current_monkey_type) {
	case CONSTANTS::TYPE::PLACABLE::DART:
		placement_successful = m_monkey_manager->place_dart_monkey(position, available_money);
	break;
	case CONSTANTS::TYPE::PLACABLE::SUPER:
		placement_successful = m_monkey_manager->place_super_monkey(position, available_money);
	break;
	case CONSTANTS::TYPE::PLACABLE::ICE:
		placement_successful = m_monkey_manager->place_ice_monkey(position, available_money);
	break;
	case CONSTANTS::TYPE::PLACABLE::BOMB:
		placement_successful = m_monkey_manager->place_bomb_shooter(position, available_money);
	break;
	case CONSTANTS::TYPE::PLACABLE::TACK:
		placement_successful = m_monkey_manager->place_tack_shooter(position, available_money);
	break;
	case CONSTANTS::TYPE::PLACABLE::BOOMERANG:
		placement_successful = m_monkey_manager->place_boomerang_monkey(position, available_money);
	break;
	default: break;
	}

	return placement_successful;
}

void MonkeyPlacementController::clear_all() {
	SetVisible(false);
	m_is_active = false;
	m_spawned_monkey = nullptr;
	m_current_monkey_type = CONSTANTS::TYPE::PLACABLE::_NULL;

	std::cout << "cleared all monkeys" << std::endl;
}

void MonkeyPlacementController::set_monkey_obstacles(const std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>>& obstacles) {
	m_obstacles.clear();
	
	m_obstacles.insert(m_obstacles.end(), obstacles.begin(), obstacles.end());
}

void MonkeyPlacementController::set_mouse_pos(const glm::vec2& mouse_pos) {
	if (!m_is_active) return;

	m_Transform.translation = mouse_pos;
	if (m_hitbox) {
		m_hitbox->set_position(mouse_pos);
	}

	update_visual_state();
}

void MonkeyPlacementController::set_active(bool active) {
	m_is_active = active;
	SetVisible(active);

	if (active) {
		update_visual_state();
	}
}

MonkeyPlacementController::~MonkeyPlacementController() {
	
}

}
