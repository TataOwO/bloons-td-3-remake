#include "bloons/BaseBloon.hpp"

#include <cstdlib>
#include <exception>

namespace bloons {
	BaseBloon::BaseBloon(std::shared_ptr<map::route::Route> start_route) {
		m_current_route = start_route;
		
		m_target_point = m_current_route->get_end_point() + glm::vec2{std::rand()%20-10, std::rand()%20-10};
	};

	bool BaseBloon::is_at_end() {
		return m_current_route == nullptr;
	};

	int BaseBloon::get_hp() {
		return m_hp;
	};

	glm::vec2 BaseBloon::get_pos() {
		return m_Transform.translation;
	};

	int BaseBloon::get_length_to_exit() {
		glm::vec2 end_point_diff = {
			m_target_point[0] - m_Transform.translation[0],
			m_target_point[1] - m_Transform.translation[2],
		};
		
		return glm::length(end_point_diff) + m_current_route->get_length_to_exit();
	};

	void BaseBloon::m_move() {
		if (is_at_end()) throw std::runtime_error("bloon is at the end");

		glm::vec2 diff = {
			m_target_point[0] - m_Transform.translation[0],
			m_target_point[1] - m_Transform.translation[1]
		};

		float diff_distance = glm::length(diff);

		if (diff_distance < m_speed) {
			m_Transform.translation = m_target_point;
			m_current_route = m_current_route->get_next_route();
			
			if (!is_at_end()) m_target_point = m_current_route->get_end_point() + glm::vec2{std::rand()%20-10, std::rand()%20-10};
		} else {
			m_Transform.translation = {
				m_Transform.translation[0] + diff[0] * m_speed / diff_distance,
				m_Transform.translation[1] + diff[1] * m_speed / diff_distance
			};
		}
		
		m_hitbox->set_position(m_Transform.translation);
	};
}
