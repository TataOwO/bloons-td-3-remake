#ifndef MAP_ROUTE_HPP
#define MAP_ROUTE_HPP

#include <pch.hpp>
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

namespace map::route {
enum RouteConnection {
	BEFORE,
	AFTER,
	NOT_CONNECTED
};

class Route : public Util::GameObject {
public:
	Route(glm::vec2 start_point, glm::vec2 end_point);
	
    Route(const Route&) = delete;

    Route(Route&&) = delete;

    Route& operator=(const Route&) = delete;

    Route& operator=(Route&&) = delete;

	RouteConnection route_is_connected(Route route);

	std::shared_ptr<Route> get_next_route() const;
	
	[[nodiscard]] glm::vec2 get_start_point() const;
	[[nodiscard]] glm::vec2 get_end_point() const;
	
	double recursive_calculate_exit_length();
	double get_length_to_exit();
	
	void set_next_route(std::shared_ptr<Route> next_route);

private:
	std::string m_image_path = RESOURCE_DIR"/images/route_thin.png";
	
	glm::vec2 m_start_point  = {0,0};
	glm::vec2 m_end_point    = {0,0};
	glm::vec2 m_center_point = {0,0};
	glm::vec2 m_diff = {0,0};
	
	double m_length;
	
	double m_length_to_exit = 0;
	
	std::shared_ptr<Route> m_next_route = nullptr;
};

}

#endif
