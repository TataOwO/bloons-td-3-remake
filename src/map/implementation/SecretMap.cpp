#include "map/implementation/SecretMap.hpp"

#include "handlers/PathManager.hpp"
#include "map/MapBackground.hpp"
#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

namespace map::implementation {

SecretMap::SecretMap() {
	std::vector<std::vector<glm::vec2>> points = {
		{ // N
			glm::vec2{63, 317},
			glm::vec2{108, 92},
			glm::vec2{190, 293},
			glm::vec2{220, 105},
		},
		{ // T1
			glm::vec2{271, 102},
			glm::vec2{372, 110},
		},
		{ // T2
			glm::vec2{330, 100},
			glm::vec2{307, 269},
		},
		{ // U
			glm::vec2{416, 120},
			glm::vec2{418, 289},
			glm::vec2{528, 282},
			glm::vec2{508, 129},
		},
		{ // T1
			glm::vec2{555, 137},
			glm::vec2{681, 134},
		},
		{ // T2
			glm::vec2{627, 139},
			glm::vec2{631, 302},
		},
		{ // O1
			glm::vec2{79, 450},
			glm::vec2{66, 566},
			glm::vec2{189, 556},
			glm::vec2{198, 452},
			glm::vec2{41, 440},
		},
		{ // O2
			glm::vec2{262, 454},
			glm::vec2{265, 550},
			glm::vec2{373, 502},
			glm::vec2{360, 432},
			glm::vec2{264, 454},
		},
		{ // P
			glm::vec2{414, 556},
			glm::vec2{427, 416},
			glm::vec2{534, 420},
			glm::vec2{506, 476},
			glm::vec2{427, 493},
		},
		{ // L
			glm::vec2{591, 416},
			glm::vec2{587, 541},
			glm::vec2{676, 558},
		},
	};
	
	// routes
	std::vector<std::vector<std::shared_ptr<map::route::Route>>> route_vec_vec = {};
	
	for (const std::vector<glm::vec2>& vec: points) {
		std::vector<std::shared_ptr<map::route::Route>> rv1 = {};
		glm::vec2 prev = vec.at(0);
		for (unsigned int i=0; i<vec.size(); ++i) {
			glm::vec2 now = vec.at(i);
			rv1.push_back(std::make_shared<map::route::Route>(prev, now));
			prev = now;
		}
		std::vector<std::shared_ptr<map::route::Route>> rv2 = {};
		prev = vec.at(vec.size()-1);
		for (int i=vec.size()-2; i>=0; --i) {
			glm::vec2 now = vec.at(i);
			rv2.push_back(std::make_shared<map::route::Route>(prev, now));
			prev = now;
		}
		
		route_vec_vec.push_back(rv1);
		route_vec_vec.push_back(rv2);
	}

	// route paths
	std::vector<std::shared_ptr<map::route::RoutePath>> route_paths = {};
	
	for (auto& routes: route_vec_vec) {
		route_paths.push_back(std::make_shared<map::route::RoutePath>(routes));
	}

	// add route paths to manager
	m_path_manager = std::make_shared<handlers::PathManager>(route_paths);

	AddChild(m_path_manager);
	
	// background initialization
	std::vector<std::string> background_images = {
		RESOURCE_DIR"/images/maps/secret_map.png",
	};
	
	m_background = std::make_shared<map::MapBackground>();
	m_background->set_layers(background_images);
	AddChild(m_background);
}

void SecretMap::update() {
	
}

SecretMap::~SecretMap() {
}

}

