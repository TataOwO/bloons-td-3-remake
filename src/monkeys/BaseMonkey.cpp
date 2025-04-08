#include "monkeys/BaseMonkey.hpp"

#include <iostream>

namespace monkeys {
    BaseMonkey::BaseMonkey(glm::vec2 position) {
		m_base_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);
		m_radius_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);
		
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
		return m_radius_hitbox->get_radius();
	};

	glm::vec2 BaseMonkey::get_position() const {
		return m_base_hitbox->get_position();
	};

}
