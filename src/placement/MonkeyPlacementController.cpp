#include "placement/MonkeyPlacementController.hpp"

#include "Util/Image.hpp"
#include <cstring>

namespace placement {

MonkeyPlacementController::MonkeyPlacementController(
	std::shared_ptr<handlers::PathManager> path_manager,
	std::shared_ptr<handlers::MonkeyManager> monkey_manager)
	: m_path_manager(path_manager), m_monkey_manager(monkey_manager) {

	SetVisible(false);
	m_hitbox = std::make_shared<hitboxes::CircularHitbox>(glm::vec2(0, 0), m_default_hitbox_radius);
}

void MonkeyPlacementController::update() {
	if (!m_is_active) return;

	// check position validity and update visuals
	update_visual_state();
}

void MonkeyPlacementController::set_monkey(const PLACABLE_TYPE& type) {
	m_current_monkey_type = type;

	if (type == PLACABLE_TYPE::_NULL) {
		SetVisible(false);
		m_is_active = false;
		return;
	}

	std::string monke_name = "";
	switch (type) {
	case PLACABLE_TYPE::DART:
		monke_name = "dart";
		break;
	case PLACABLE_TYPE::BOOMERANG:
		monke_name = "boomerang";
		break;
	case PLACABLE_TYPE::SUPER:
		monke_name = "super";
		break;
	case PLACABLE_TYPE::ICE:
		monke_name = "ice";
		break;
	case PLACABLE_TYPE::BOMB:
		monke_name = "bomb";
		break;
	case PLACABLE_TYPE::TACK:
		monke_name = "tack";
		break;
	case PLACABLE_TYPE::SPIKE:
		monke_name = "spike";
		break;
	case PLACABLE_TYPE::GLUE:
		monke_name = "glue";
		break;
	case PLACABLE_TYPE::PINEAPPLE:
		monke_name = "pineapple";
		break;
	case PLACABLE_TYPE::VILLAGE:
		monke_name = "village";
		break;
	case PLACABLE_TYPE::CATAPULT:
		monke_name = "catapult";
		break;
	default:
		SetVisible(false);
		m_is_active = false;
		return;
	}

	std::string prefix = RESOURCE_DIR"/images/";
	std::string placable_path = prefix + monke_name + ".png";
	std::string unplacable_path = prefix + monke_name + "_RED.png";

	m_placable = std::make_shared<Util::Image>(placable_path, false);
	m_unplacable = std::make_shared<Util::Image>(unplacable_path, false);

	m_Drawable = m_placable;

	// set active and visible
	m_is_active = true;
	SetVisible(true);

	update_visual_state();
}

bool MonkeyPlacementController::check_valid_position() const {
	if (m_current_monkey_type == PLACABLE_TYPE::_NULL || !m_is_active || !m_hitbox) {
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

	return true;
}

void MonkeyPlacementController::update_visual_state() {
	m_current_position_valid = check_valid_position();

	if (m_current_position_valid) m_Drawable = m_placable;
	else m_Drawable = m_unplacable;
}

bool MonkeyPlacementController::is_valid_placement() const {
	return m_current_position_valid;
}

bool MonkeyPlacementController::place_monkey(int& available_money) {
	if (!m_is_active || !is_valid_placement() || m_current_monkey_type == PLACABLE_TYPE::_NULL) {
		return false;
	}

	bool placement_successful = false;
	
	glm::vec2 position = m_hitbox->get_position();
	
	switch (m_current_monkey_type) {
	case PLACABLE_TYPE::DART:
		placement_successful = m_monkey_manager->place_dart_monkey(position, available_money);
		break;
	// more monkeys to be added
	default:
		break;
	}

	return placement_successful;
}

void MonkeyPlacementController::clear_all() {
	SetVisible(false);
	m_is_active = false;
	m_spawned_monkey = nullptr;
	m_current_monkey_type = PLACABLE_TYPE::_NULL;
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

}