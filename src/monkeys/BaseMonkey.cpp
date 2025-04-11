#include "monkeys/BaseMonkey.hpp"

#include <iostream>
#include "utility/functions.hpp"

namespace monkeys {
    BaseMonkey::BaseMonkey(glm::vec2 position) {
		m_base_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);
		m_radius_hitbox	= std::make_shared<hitboxes::CircularHitbox>(position, 0);
		
		this->SetZIndex(1.5);
		this->SetVisible(true);
    }

	bool BaseMonkey::is_collided_with_route(std::shared_ptr<map::route::Route> route) const {
		auto other = route->get_hitbox();
		return utility::hitboxes_are_collided(other, m_base_hitbox);
	};

	bool BaseMonkey::is_collided_with_monkey(std::shared_ptr<BaseMonkey> monke) const {
		auto other = monke->get_hitbox();
		return utility::hitboxes_are_collided(other, m_base_hitbox);
	};

	int BaseMonkey::get_radius() const {
		return m_radius_hitbox->get_radius();
	};

	glm::vec2 BaseMonkey::get_position() const {
		return m_base_hitbox->get_position();
	};

}
