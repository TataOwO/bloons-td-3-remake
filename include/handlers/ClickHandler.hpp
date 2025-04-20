#ifndef CLICK_HANDLER_HPP
#define CLICK_HANDLER_HPP

#include "inputs/Clickable.hpp"

#include "pch.hpp"

namespace handlers {

class ClickHandler final {
public:
	ClickHandler(std::vector<std::shared_ptr<inputs::Clickable>>& clickable_vec) : m_clickable_vec(clickable_vec) {};
	
	void update(const glm::vec2& mouse_pos);
	
	// setters
	void add_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
	void remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
private:
	// TODO: SORTED VECTOR FOR ZINDEX
	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec = {};
	
	std::vector<std::shared_ptr<inputs::Clickable>> m_removal_queue = {};
// base
public:
	ClickHandler(const ClickHandler&) = delete;

	ClickHandler(ClickHandler&&) = delete;

	ClickHandler& operator=(const ClickHandler&) = delete;

	ClickHandler& operator=(ClickHandler&&) = delete;

	virtual ~ClickHandler() = default;
};

}

#endif
