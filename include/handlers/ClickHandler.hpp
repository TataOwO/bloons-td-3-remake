#ifndef CLICK_HANDLER_HPP
#define CLICK_HANDLER_HPP

#include "utility/Mortal.hpp"
#include "Util/GameObject.hpp"

namespace hitboxes {class I_BaseHitbox;}
namespace handlers  {class MonkeyManager;}
namespace handlers  {class PathManager;}
namespace handlers  {class BloonWaveManager;}
namespace inputs    {class Clickable;}
namespace placement {class MonkeyPlacementController;}
namespace CONSTANTS::TYPE {enum class PLACABLE;}
namespace Util      {class Renderer;}
namespace layout    {class GameText;}
namespace layout    {class Button;}

namespace handlers {

class ClickHandler final : public utility::Mortal, public Util::GameObject {
public:
	ClickHandler(const std::shared_ptr<handlers::PathManager>& path_manager, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager, const std::shared_ptr<handlers::BloonWaveManager>& bloon_wave_manager, const std::shared_ptr<layout::GameText> &current_money);

	void update(const glm::vec2& mouse_pos, bool left_button, bool right_button, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager, const std::shared_ptr<layout::GameText> &current_money);
	void update_monkey_placement_controller(const glm::vec2& mouse_pos, bool left_button, bool right_button, const std::shared_ptr<layout::GameText> &current_money) const;

	std::vector<std::shared_ptr<inputs::Clickable>> get_clickables() const {return m_clickable_vec;};

	// monket placement obstacles
	void set_monkey_obstacles(const std::vector<std::shared_ptr<hitboxes::I_BaseHitbox>>&) const;

	// setters
	void add_clickables(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
	void add_clickable(const std::shared_ptr<inputs::Clickable>& c_vec);
	void remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);

	// game states
	bool should_goto_map_selector() const {return *m_map_state;}
	bool should_exit_game() const {return *m_exit_state;}
	void clear_states() const {*m_exit_state = *m_map_state = false;}
private:
	std::shared_ptr<layout::Button> m_add_new_monkey_placement_button(const CONSTANTS::TYPE::PLACABLE&, const glm::vec2&, const std::shared_ptr<layout::GameText> &current_money);

	void add_existing_button(const std::shared_ptr<layout::Button>& button);
	void remove_button(const std::vector<std::shared_ptr<layout::Button>>& b_vec);
private:
	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec = {};
	std::vector<std::shared_ptr<inputs::Clickable>> m_removal_queue = {};

	std::vector<std::shared_ptr<layout::Button>> m_button_vec = {};
	std::vector<std::shared_ptr<layout::Button>> m_button_removal_queue = {};

	// other managers required to be stored here
	std::shared_ptr<placement::MonkeyPlacementController> m_monkey_placement_manager;
	std::shared_ptr<handlers::BloonWaveManager> m_bloon_wave_manager;
	
	// wave buttons
	std::shared_ptr<layout::Button> m_wave_button;

	std::shared_ptr<bool> m_map_state  = std::make_shared<bool>(false);
	std::shared_ptr<bool> m_exit_state = std::make_shared<bool>(false);

// base
public:
	ClickHandler(const ClickHandler&) = delete;

	ClickHandler(ClickHandler&&) = delete;

	ClickHandler& operator=(const ClickHandler&) = delete;

	ClickHandler& operator=(ClickHandler&&) = delete;

	~ClickHandler() override;
};

}

#endif
