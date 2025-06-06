#ifndef MONKEY_PLACEMENT_CONTROLLER_HPP
#define MONKEY_PLACEMENT_CONTROLLER_HPP

#include <unordered_set>

#include "constants/TYPE.hpp"
#include "Util/GameObject.hpp"

namespace Core {class Drawable;}

namespace handlers {class PathManager;}
namespace handlers {class MonkeyManager;}
namespace monkeys  {class BaseMonkey;}
namespace hitboxes {class I_BaseHitbox;}
namespace hitboxes {class CircularHitbox;}
namespace layout   {class GameText;}

namespace placement {

class MonkeyPlacementController : public Util::GameObject {
public:
	MonkeyPlacementController(const std::shared_ptr<handlers::PathManager> &path_manager, const std::shared_ptr<handlers::MonkeyManager> &monkey_manager);

	void set_monkey(const CONSTANTS::TYPE::PLACABLE& type, const std::shared_ptr<layout::GameText> &current_money);

	void update();

	// monkey placement
	bool is_valid_placement() const;
	bool place_monkey(const std::shared_ptr<layout::GameText> &available_money) const;

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
	CONSTANTS::TYPE::PLACABLE get_current_type() const { return m_current_monkey_type; }

	void set_monkey_obstacles(const std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>>&);

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

	CONSTANTS::TYPE::PLACABLE m_current_monkey_type = CONSTANTS::TYPE::PLACABLE::_NULL;
	std::shared_ptr<monkeys::BaseMonkey> m_spawned_monkey;

	std::shared_ptr<hitboxes::CircularHitbox> m_hitbox = nullptr;

	bool m_is_active = false;
	bool m_current_position_valid = false;

	// Track which types need to be placed ON routes instead of off routes
	const std::unordered_set<CONSTANTS::TYPE::PLACABLE> m_route_only_types = {
		CONSTANTS::TYPE::PLACABLE::GLUE,
		CONSTANTS::TYPE::PLACABLE::PINEAPPLE,
		CONSTANTS::TYPE::PLACABLE::SPIKE
	};

	// Hitbox radius for different monkey types
	float m_default_hitbox_radius = 30.0f;
	
	std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>> m_obstacles = {};

// base
public:
	MonkeyPlacementController(const MonkeyPlacementController&) = delete;
	MonkeyPlacementController(MonkeyPlacementController&&) = delete;
	MonkeyPlacementController& operator=(const MonkeyPlacementController&) = delete;
	MonkeyPlacementController& operator=(MonkeyPlacementController&&) = delete;
	~MonkeyPlacementController() override;
};

}

#endif