#include "handlers/ClickHandler.hpp"

#include <algorithm>

namespace handlers {

void ClickHandler::update(const glm::vec2& mouse_pos) {
	for (auto& clickable: m_clickable_vec) {
		if (clickable->shall_be_removed()) {
			m_removal_queue.push_back(clickable);
			continue;
		}

		clickable->process_click(mouse_pos);
	}

	remove_clickable(m_removal_queue);
	m_removal_queue.clear();
}

// setters
void ClickHandler::add_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec) {
	m_clickable_vec.insert(m_clickable_vec.end(), c_vec.start(), c_vec.end());
}

void ClickHandler::remove_clickable(const std::vector<std::shared_ptr<inputs::Clickable>>& c_vec);
	for (auto& c: c_vec) {
		auto& it = std::find(m_clickable_vec.start(), m_clickable_vec.end(), c);
		
		if (it == m_clickable_vec.end()) continue;
		
		m_clickable_vec.erase(it);
	}
}
