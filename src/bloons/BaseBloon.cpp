#include "bloons/BaseBloon.hpp"

namespace bloons {
	BaseBloon::BaseBloon(const std::shared_ptr<map::route::Route> &start_route) {
		m_current_route = start_route;

		m_target_point = twist_pos(m_current_route->get_end_point());
		
		// add starting pos to history
		if (start_route) {
			m_path_history.push_front(start_route->get_start_point());
		}
	};

	int BaseBloon::get_length_to_exit() {
		glm::vec2 end_point_diff = {
			m_target_point[0] - m_Transform.translation[0],
			m_target_point[1] - m_Transform.translation[1],
		};

		return glm::length(end_point_diff) + m_current_route->get_length_to_exit();
	};

	void BaseBloon::m_move() {
		if (is_at_end()) throw std::runtime_error("bloon is at the end");

		// add pos to history
		m_path_history.push_front(m_Transform.translation);
		if (m_path_history.size() > m_max_path_history_size) {
			m_path_history.pop_back();
		}

		glm::vec2 diff = {
			m_target_point[0] - m_Transform.translation[0],
			m_target_point[1] - m_Transform.translation[1] 
		};

		float diff_distance = glm::length(diff);

		if (diff_distance < m_speed) {
			m_Transform.translation = m_target_point;
			m_current_route = m_current_route->get_next_route();

			if (!is_at_end()) m_target_point = twist_pos(m_current_route->get_end_point());
		} else {
			m_Transform.translation = {
				m_Transform.translation[0] + diff[0] * m_speed / diff_distance,
				m_Transform.translation[1] + diff[1] * m_speed / diff_distance
			};
		}

		m_hitbox->set_position(m_Transform.translation);
	};

	glm::vec2 BaseBloon::twist_pos(glm::vec2 pos) {
		return pos + glm::vec2{base_bloon_dist(base_bloon_gen), base_bloon_dist(base_bloon_gen)};
	}
}