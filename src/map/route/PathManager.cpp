#include "map/route/PathManager.hpp"

#include <iostream>

namespace map::route {

PathManager::PathManager(std::vector<std::shared_ptr<map::route::RoutePath>> paths, std::shared_ptr<Util::Renderer> render_manager) : m_paths(paths), m_render_manager(render_manager) {
	for (std::shared_ptr<map::route::RoutePath> rp: paths) {
		render_manager->AddChild(rp);
	}
}

std::shared_ptr<map::route::RoutePath> PathManager::get_random_route_path() const {
	return m_paths.at(std::rand() % m_paths.size());
}

}
