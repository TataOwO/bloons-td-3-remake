#include "map/implementation/IceMap.hpp"

#include "handlers/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

namespace map::implementation {

IceMap::IceMap() {
	std::vector points = {
		glm::vec2{215, 0},
		glm::vec2{167, 132},
		glm::vec2{176, 149},
		glm::vec2{389, 55},
		glm::vec2{413, 66},
		glm::vec2{439, 166},
		glm::vec2{428, 190},
		glm::vec2{284, 203},
		glm::vec2{262, 212},
		glm::vec2{243, 232},
		glm::vec2{127, 393},
		glm::vec2{120, 413},
		glm::vec2{141, 423},
		glm::vec2{246, 440},
		glm::vec2{311, 462},
		glm::vec2{344, 456},
		glm::vec2{364, 433},
		glm::vec2{387, 370},
		glm::vec2{407, 339},
		glm::vec2{438, 316},
		glm::vec2{526, 253},
		glm::vec2{548, 226},
		glm::vec2{562, 193},
		glm::vec2{573, 125},
		glm::vec2{598, 120},
		glm::vec2{629, 149},
		glm::vec2{645, 181},
		glm::vec2{648, 211},
		glm::vec2{644, 247},
		glm::vec2{620, 338},
		glm::vec2{590, 426},
		glm::vec2{576, 453},
		glm::vec2{549, 460},
		glm::vec2{497, 457},
		glm::vec2{479, 467},
		glm::vec2{477, 501},
		glm::vec2{470, 534},
		glm::vec2{441, 592},
		glm::vec2{428, 601},
		glm::vec2{410, 601},
		glm::vec2{302, 566},
		glm::vec2{278, 562},
		glm::vec2{201, 559},
		glm::vec2{170, 574},
		glm::vec2{127, 659},
		glm::vec2{109, 685},
		glm::vec2{81, 720},
	};
	
	// routes
	std::vector<std::shared_ptr<map::route::Route>> route_vec1 = {};
	
	glm::vec2 prev = points.at(0);
	for (unsigned int i=1; i<points.size(); ++i) {
		glm::vec2 now = points.at(i);
		route_vec1.push_back(std::make_shared<map::route::Route>(prev, now));
		prev = now;
	}

	// route paths
	std::vector<std::shared_ptr<map::route::RoutePath>> route_paths = {
		std::make_shared<map::route::RoutePath>(route_vec1),
	};

	// add route paths to manager
	m_path_manager = std::make_shared<handlers::PathManager>(route_paths);

	AddChild(m_path_manager);
	
	// background initialization
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/ice_map.png",
		RESOURCE_DIR"/images/maps/ice_map_frozen.png",
		RESOURCE_DIR"/images/maps/ice_map_sleeping_frog.png"
	};
	
	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
}

void IceMap::set_wave(int wave_number) {
	if (wave_number == m_current_wave) return;
	m_current_wave = wave_number;
}

void IceMap::update() {
	
}

IceMap::~IceMap() {
}

}

