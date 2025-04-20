#include "map/route/Route.hpp"

#include <memory>

#include "Util/Image.hpp"

#include <iostream>

#include <cmath>

namespace map::route {
	Route::Route(glm::vec2 start_point, glm::vec2 end_point) {
		m_start_point = convert_pos(start_point);
		m_end_point   = convert_pos(end_point);

		m_center_point = {
			(m_start_point[0] + m_end_point[0]) * 0.5,
			(m_start_point[1] + m_end_point[1]) * 0.5
		};
		
		m_diff = {
			(m_start_point[0] - m_end_point[0]),
			(m_start_point[1] - m_end_point[1])
		};
		
		m_length = glm::length(m_diff);
		
		m_Transform.scale = {m_length * 0.5, 1};
		m_Transform.translation = m_center_point;
		m_Transform.rotation = atan(m_diff[1] / m_diff[0]);

		m_hitbox = std::make_shared<hitboxes::RectangularHitbox>(
			m_Transform.translation,
			glm::vec2{m_length, 15},
			m_Transform.rotation
		);

		m_Drawable = std::make_shared<Util::Image>(m_image_path, false);

		this->SetZIndex(2);
		this->SetVisible(false);
	};

	RouteConnection Route::route_is_connected(const std::shared_ptr<Route> &route) {
		auto route_start_point = route->get_start_point();
		auto route_end_point = route->get_end_point();
		
		if (
			m_start_point[0] == route_end_point[0] &&
			m_start_point[1] == route_end_point[1]
		) {
			return RouteConnection::BEFORE;
		}
		
		if (
			m_end_point[0] == route_start_point[0] &&
			m_end_point[1] == route_start_point[1]
		) {
			return RouteConnection::AFTER;
		}
		
		return RouteConnection::NOT_CONNECTED;
	};

	glm::vec2 Route::get_start_point() const {
		return m_start_point;
	};

	glm::vec2 Route::get_end_point() const {
		return m_end_point;
	};
	
	std::shared_ptr<Route> Route::get_next_route() const {
		return m_next_route;
	};
	
	double Route::recursive_calculate_exit_length() {
		if (m_next_route == nullptr) return m_length;
		
		m_length_to_exit = m_next_route->recursive_calculate_exit_length();
		
		return m_length + m_length_to_exit;
	};

	void Route::set_next_route(const std::shared_ptr<Route> &next_route) {
		m_next_route = next_route;
	};
	
	glm::vec2 Route::convert_pos(glm::vec2 v) {
		return glm::vec2{
			 v.x - 480,
			-v.y + 360,
		};
	}
}