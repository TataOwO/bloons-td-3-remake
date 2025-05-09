#include "map/implementation/SummonMap.hpp"

#include "handlers/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

namespace map::implementation {

SummonMap::SummonMap() {
	std::vector points = {
		glm::vec2{0, 555},
		glm::vec2{235, 562},
		glm::vec2{252, 534},
		glm::vec2{181, 452},
		glm::vec2{161, 398},
		glm::vec2{167, 281},
		glm::vec2{216, 211},
		glm::vec2{278, 165},
		glm::vec2{355, 146},
		glm::vec2{415, 146},
		glm::vec2{481, 179},
		glm::vec2{538, 228},
		glm::vec2{573, 287},
		glm::vec2{575, 389},
		glm::vec2{558, 451},
		glm::vec2{517, 507},
		glm::vec2{476, 548},
		glm::vec2{486, 573},
		glm::vec2{720, 573},
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
		RESOURCE_DIR"/images/maps/summon_map.png"
	};

	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
}

void SummonMap::update() {
	
}

SummonMap::~SummonMap() {
}

}

