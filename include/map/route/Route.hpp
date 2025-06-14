#ifndef MAP_ROUTE_HPP
#define MAP_ROUTE_HPP

#include "Util/GameObject.hpp"

namespace Util {class Image;}
namespace hitboxes {class RectangularHitbox;}

namespace map::route {
enum class RouteConnection {
	BEFORE,
	AFTER,
	NOT_CONNECTED
};

class Route final : public Util::GameObject {
public:
	Route(glm::vec2 start_point, glm::vec2 end_point, bool tts=false);

	RouteConnection route_is_connected(const std::shared_ptr<Route> &route);
	
	// linked list implementation
	std::shared_ptr<Route> get_next_route() const;

	// begin and end
	glm::vec2 get_start_point() const;
	glm::vec2 get_end_point() const;

	double recursive_calculate_exit_length();
	double get_length_to_exit() const {return m_length_to_exit;};

	// for teleport map
	bool should_teleport_to_start() const {return m_teleport_to_start;}

	void set_next_route(const std::shared_ptr<Route> &next_route);

	// not supposed to be here but whatever
	static glm::vec2 convert_pos(glm::vec2 v);
	
	std::shared_ptr<hitboxes::RectangularHitbox> get_hitbox() {return m_hitbox;}
private:
	std::string m_image_path = RESOURCE_DIR"/images/route_thin.png";

	glm::vec2 m_start_point  = {0,0};
	glm::vec2 m_end_point    = {0,0};
	glm::vec2 m_center_point = {0,0};
	glm::vec2 m_diff = {0,0};

	double m_length;

	double m_length_to_exit = 0;

	std::shared_ptr<hitboxes::RectangularHitbox> m_hitbox;

	std::shared_ptr<Route> m_next_route = nullptr;

	bool m_teleport_to_start;
// base
public:

    Route(const Route&) = delete;

    Route(Route&&) = delete;

    Route& operator=(const Route&) = delete;

    Route& operator=(Route&&) = delete;

	~Route() override;
};

}

#endif
