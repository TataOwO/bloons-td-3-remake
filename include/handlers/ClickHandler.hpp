#ifndef CLICK_HANDLER_HPP
#define CLICK_HANDLER_HPP

#include "utility/Mortal.hpp"

namespace handlers  {class MonkeyManager;}
namespace handlers  {class PathManager;}
namespace inputs    {class Clickable;}
namespace placement {class MonkeyPlacementController;}
namespace placement {enum class PLACABLE_TYPE;}
namespace Util      {class Renderer;}
namespace layout    {class GameText;}
namespace layout    {class Button;}

namespace handlers {

class ClickHandler final : public utility::Mortal {
public:
	ClickHandler(const std::shared_ptr<Util::Renderer> &render_manager, const std::shared_ptr<handlers::PathManager>& path_manager, const std::shared_ptr<handlers::MonkeyManager>& monkey_manager);

	void update(const glm::vec2& mouse_pos, bool left_button);
	void update_monkey_placement_controller(const glm::vec2& mouse_pos, bool left_button, bool right_button, const std::shared_ptr<layout::GameText> &current_money) const;

	std::vector<std::shared_ptr<inputs::Clickable>> get_clickables() const {return m_clickable_vec;};

	// setters
	void add_clickables(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
	void add_clickable(const std::shared_ptr<inputs::Clickable>& c_vec);
	void remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
private:
	std::shared_ptr<layout::Button> m_add_new_button(const placement::PLACABLE_TYPE&, const glm::vec2&);
	void remove_button(const std::vector<std::shared_ptr<layout::Button>>& b_vec);
private:
	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec = {};
	std::vector<std::shared_ptr<inputs::Clickable>> m_removal_queue = {};

	std::vector<std::shared_ptr<layout::Button>> m_button_vec = {};
	std::vector<std::shared_ptr<layout::Button>> m_button_removal_queue = {};

	std::shared_ptr<Util::Renderer> m_render_manager;
	std::shared_ptr<placement::MonkeyPlacementController> m_monkey_placement_manager;
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
