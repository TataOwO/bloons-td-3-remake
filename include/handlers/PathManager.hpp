#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

#include "Util/Renderer.hpp"

#include <cstdlib>

namespace handlers {

class PathManager {
public:
	PathManager(std::vector<std::shared_ptr<map::route::RoutePath>> paths, std::shared_ptr<Util::Renderer> render_manager);

    PathManager(const PathManager&) = delete;

    PathManager(PathManager&&) = delete;

    PathManager& operator=(const PathManager&) = delete;

    PathManager& operator=(PathManager&&) = delete;

	~PathManager() = default;

public:
	std::vector<std::shared_ptr<Route>> get_all_routes() {return m_all_routes;};

	std::shared_ptr<map::route::RoutePath> get_random_route_path() const;
private:
	std::vector<std::shared_ptr<map::route::RoutePath>> m_paths = {};

	std::vector<std::shared_ptr<Route>> m_all_routes = {};

	std::shared_ptr<Util::Renderer> m_render_manager;
};

}

#endif
