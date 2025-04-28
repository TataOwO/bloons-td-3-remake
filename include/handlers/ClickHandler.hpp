#ifndef CLICK_HANDLER_HPP
#define CLICK_HANDLER_HPP

#include "MonkeyManager.hpp"
#include "PathManager.hpp"
#include "inputs/Clickable.hpp"
#include "utility/Mortal.hpp"

#include "Constants.hpp"

#include "pch.hpp"
#include "placement/MonkeyPlacementController.hpp"

namespace handlers {

class ClickHandler final : public utility::Mortal {
public:
	ClickHandler(std::shared_ptr<Util::Renderer> render_manager, std::shared_ptr<handlers::PathManager> path_manager, std::shared_ptr<handlers::MonkeyManager> monkey_manager);

	void update(const glm::vec2& mouse_pos, bool left_button);
	void update_monkey_placement_controller(const glm::vec2& mouse_pos, bool left_button, bool right_button, const std::shared_ptr<layout::GameText> &current_money) const;

	std::vector<std::shared_ptr<inputs::Clickable>> get_clickables() const {return m_clickable_vec;};

	// setters
	void add_clickables(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
	void add_clickable(const std::shared_ptr<inputs::Clickable>& c_vec);
	void remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
private:
	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec = {};

	std::vector<std::shared_ptr<inputs::Clickable>> m_removal_queue = {};
	
	std::shared_ptr<Util::Renderer> m_render_manager;
	std::shared_ptr<placement::MonkeyPlacementController> m_monkey_placement_manager;
// base
public:
	ClickHandler(const ClickHandler&) = delete;

	ClickHandler(ClickHandler&&) = delete;

	ClickHandler& operator=(const ClickHandler&) = delete;

	ClickHandler& operator=(ClickHandler&&) = delete;

	~ClickHandler() = default;
};

}

#endif
