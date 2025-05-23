#include "handlers/PathManager.hpp"

#include "Util/Renderer.hpp"

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

#include "hitboxes/I_BaseHitbox.hpp"
#include "hitboxes/RectangularHitbox.hpp"

#include <iostream>
#include "utility/functions.hpp"

namespace handlers {

PathManager::PathManager(const std::vector<std::shared_ptr<map::route::RoutePath>>& paths) : m_paths(paths) {
	for (const std::shared_ptr<map::route::RoutePath>& rp: paths) {
		// renderer
		AddChild(rp);
		
		// insert
		auto routes = rp->get_all_routes();
		m_all_routes.insert(m_all_routes.end(), routes.begin(), routes.end());
	}
	
	m_paths = paths;
}

std::shared_ptr<map::route::Route> PathManager::get_collided_route(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox) {
	for (auto& route: m_all_routes) {
		if (utility::hitboxes_are_collided(route->get_hitbox(), hitbox)) return route;
	}
	return nullptr;
}

std::shared_ptr<map::route::RoutePath> PathManager::get_random_route_path() const {
	return m_paths.at(std::rand() % m_paths.size());
}

PathManager::~PathManager() {
	
}

}
