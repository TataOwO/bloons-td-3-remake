#ifndef MONKEY_PLACEMENT_CONTROLLER_HPP
#define MONKEY_PLACEMENT_CONTROLLER_HPP

#include <unordered_set>

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Core/Drawable.hpp"

#include "handlers/PathManager.hpp"
#include "handlers/MonkeyManager.hpp"
#include "monkeys/BaseMonkey.hpp"
#include "hitboxes/I_BaseHitbox.hpp"
#include "hitboxes/CircularHitbox.hpp"

namespace placement {

enum class PLACABLE_TYPE {
	DART,
	BOOMERANG,
	SUPER,
	ICE,
	BOMB,
	TACK,
	SPIKE,
	GLUE,
	PINEAPPLE,
	VILLAGE,
	CATAPULT,
	_NULL,
};

class MonkeyPlacementController : public Util::GameObject {
public:
	MonkeyPlacementController(std::shared_ptr<handlers::PathManager> path_manager, std::shared_ptr<handlers::MonkeyManager> monkey_manager);

	void set_monkey(const PLACABLE_TYPE& type);

	void update();

	// monket placement
	bool is_valid_placement() const;
	bool place_monkey(std::shared_ptr<layout::GameText> available_money);

	// activeness
	void set_active(bool active);
	bool is_active() const { return m_is_active; }

	// spawned monkeys access
	bool has_spawned_monkey() const { return m_spawned_monkey != nullptr; }
	std::shared_ptr<monkeys::BaseMonkey> get_spawned_monkey() const { return m_spawned_monkey; }

	// temporarily disables the controller
	void clear_all();

	void set_mouse_pos(const glm::vec2& mouse_pos);

	// get current type
	PLACABLE_TYPE get_current_type() const { return m_current_monkey_type; }

private:
	// checks if position is valid for current monkey type
	bool check_valid_position() const;

	// update visual state based on placement validity
	void update_visual_state();

private:
	std::shared_ptr<Core::Drawable> m_placable;
	std::shared_ptr<Core::Drawable> m_unplacable;

	std::shared_ptr<handlers::PathManager> m_path_manager;
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	PLACABLE_TYPE m_current_monkey_type = PLACABLE_TYPE::_NULL;
	std::shared_ptr<monkeys::BaseMonkey> m_spawned_monkey;

	std::shared_ptr<hitboxes::CircularHitbox> m_hitbox = nullptr;

	bool m_is_active = false;
	bool m_current_position_valid = false;

	// Track which types need to be placed ON routes instead of off routes
	const std::unordered_set<PLACABLE_TYPE> m_route_only_types = {
		PLACABLE_TYPE::GLUE,
		PLACABLE_TYPE::PINEAPPLE,
		PLACABLE_TYPE::SPIKE
	};

	// Hitbox radius for different monkey types
	float m_default_hitbox_radius = 30.0f;

// base
public:
	MonkeyPlacementController(const MonkeyPlacementController&) = delete;
	MonkeyPlacementController(MonkeyPlacementController&&) = delete;
	MonkeyPlacementController& operator=(const MonkeyPlacementController&) = delete;
	MonkeyPlacementController& operator=(MonkeyPlacementController&&) = delete;
	~MonkeyPlacementController() override = default;
};

}

#endif