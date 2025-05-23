#include "map/implementation/BaseMap.hpp"

#include "map/MapBackground.hpp"
#include "handlers/PathManager.hpp"
#include "map/route/Route.hpp"
#include "hitboxes/RectangularHitbox.hpp"

namespace map::implementation {

BaseMap::BaseMap() {
	// defining the edge of the map
	m_obstacles.push_back(
		std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{0,361}, glm::vec2{960,2}, 0.0f)
	);
	m_obstacles.push_back(
		std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{0,-361}, glm::vec2{960,2}, 0.0f)
	);
	m_obstacles.push_back(
		std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{-481,0}, glm::vec2{2, 720}, 0.0f)
	);
	m_obstacles.push_back(
		std::make_shared<hitboxes::RectangularHitbox>(glm::vec2{360,0}, glm::vec2{240,720}, 0.0f)
	);
}

void BaseMap::set_show_route(bool show) {
	if (show == route_is_visible) return;
	
	route_is_visible = !route_is_visible;
	
	for (auto& route: m_path_manager->get_all_routes()) {
		route->SetVisible(route_is_visible);
	}
}

BaseMap::~BaseMap() {
	
}

}
