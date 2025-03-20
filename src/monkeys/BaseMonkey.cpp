#include "monkeys/BaseMonkey.hpp"

#include <iostream>

namespace monkeys {
    BaseMonkey::BaseMonkey(glm::vec2 position) {
        m_position = position;
		
		this->SetZIndex(1.5);
		this->SetVisible(true);
    }
	
	bool BaseMonkey::is_collided_with_route(std::shared_ptr<map::route::Route>) const {
		return false;
	};
	
	bool BaseMonkey::is_collided_with_monkey(std::shared_ptr<BaseMonkey>) const {
		return false;
	};
	
	int BaseMonkey::get_radius() const {
		return m_radius;
	};
	
	glm::vec2 BaseMonkey::get_position() const {
		return m_position;
	};
	
	void BaseMonkey::face_towards(glm::vec2 position) {
		int x_diff = position[0] - m_position[0];
		int y_diff = position[1] - m_position[1];
		
		m_Transform.rotation = std::atan2(y_diff, x_diff) - 1.68;
	};
}
