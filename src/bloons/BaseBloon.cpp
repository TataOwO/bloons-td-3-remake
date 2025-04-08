#include "bloons/BaseBloon.hpp"

#include <cstdlib>
#include <exception>

namespace bloons {
	BaseBloon::BaseBloon(std::shared_ptr<map::route::Route> start_route) {
		m_current_route = start_route;
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
		glm::vec2 route_end = m_current_route->get_end_point();
		glm::vec2 end_point_diff = {
			route_end[0] - m_Transform.translation[0],
			route_end[1] - m_Transform.translation[2],
		};
		
		return glm::length(end_point_diff) + m_current_route->get_length_to_exit();
	};

	void BaseBloon::m_move() {
		if (is_at_end()) throw std::runtime_error("bloon is at the end");

		glm::vec2 end = m_current_route->get_end_point();

		glm::vec2 diff = {
			end[0] - m_Transform.translation[0],
			end[1] - m_Transform.translation[1]
		};

		float diff_distance = glm::length(diff);

		if (diff_distance < m_speed) {
			m_Transform.translation = end;
			m_current_route = m_current_route->get_next_route();
		} else {
			m_Transform.translation = {
				m_Transform.translation[0] + diff[0] * m_speed / diff_distance,
				m_Transform.translation[1] + diff[1] * m_speed / diff_distance
			};
		}
		
		m_hitbox->set_position(m_Transform.translation);
	};
}
