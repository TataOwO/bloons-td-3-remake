#include "map/implementation/PeacefulMap.hpp"

#include "handlers/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

namespace map::implementation {

PeacefulMap::PeacefulMap() {
	std::vector points = {
		glm::vec2{502, 0},
		glm::vec2{476, 70},
		glm::vec2{426, 131}, // loop1
		glm::vec2{327, 107},
		glm::vec2{258, 118},
		glm::vec2{215, 149},
		glm::vec2{206, 195},
		glm::vec2{208, 258},
		glm::vec2{202, 288},
		glm::vec2{131, 361},
		glm::vec2{113, 405},
		glm::vec2{123, 454},
		glm::vec2{153, 475},
		glm::vec2{208, 480},
		glm::vec2{303, 460},
		glm::vec2{327, 468},
		glm::vec2{341, 489},
		glm::vec2{355, 552},
		glm::vec2{403, 596}, // loop2
		glm::vec2{447, 603},
		glm::vec2{493, 580},
		glm::vec2{526, 521},
		glm::vec2{520, 471},
		glm::vec2{476, 402},
		glm::vec2{476, 366},
		glm::vec2{506, 343},
		glm::vec2{582, 302},
		glm::vec2{611, 263},
		glm::vec2{616, 219},
		glm::vec2{589, 174},
		glm::vec2{559, 153},
		glm::vec2{426, 131}, // repeat1
		glm::vec2{327, 107},
		glm::vec2{258, 118},
		glm::vec2{215, 149},
		glm::vec2{206, 195},
		glm::vec2{208, 258},
		glm::vec2{202, 288},
		glm::vec2{131, 361},
		glm::vec2{113, 405},
		glm::vec2{123, 454},
		glm::vec2{153, 475},
		glm::vec2{208, 480},
		glm::vec2{303, 460},
		glm::vec2{327, 468},
		glm::vec2{341, 489},
		glm::vec2{355, 552},
		glm::vec2{403, 596}, // repeat2
		glm::vec2{461, 635},
		glm::vec2{500, 720},
	};
	
	// routes
	std::vector<std::shared_ptr<map::route::Route>> route_vec1 = {};
	
	glm::vec2 prev = points.at(0);
	for (unsigned int i=0; i<points.size(); ++i) {
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
		RESOURCE_DIR"/images/maps/peaceful_map.png"
	};

	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
}

void PeacefulMap::update() {
	
}

PeacefulMap::~PeacefulMap() {
}

}

