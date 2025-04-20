#include "handlers/PathManager.hpp"

#include <iostream>

namespace handlers {

PathManager::PathManager(std::vector<std::shared_ptr<map::route::RoutePath>> paths, const std::shared_ptr<Util::Renderer> &render_manager) : m_paths(paths), m_render_manager(render_manager) {
	for (std::shared_ptr<map::route::RoutePath> rp: paths) {
		// renderer
		render_manager->AddChild(rp);
		
		// routes vector
		for (auto route: rp->get_all_routes()) {
			m_all_routes.push_back(route);
		}
	}
	
	m_paths = paths;
}

std::shared_ptr<map::route::RoutePath> PathManager::get_random_route_path() const {
	return m_paths.at(std::rand() % m_paths.size());
}

}
