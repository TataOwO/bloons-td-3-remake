#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

#include "Util/Renderer.hpp"

namespace handlers {

class PathManager final {
public:
	PathManager(std::vector<std::shared_ptr<map::route::RoutePath>> paths, std::shared_ptr<Util::Renderer> render_manager);
public:
	std::vector<std::shared_ptr<map::route::Route>> get_all_routes() {return m_all_routes;};

	std::shared_ptr<map::route::RoutePath> get_random_route_path() const;
private:
	std::vector<std::shared_ptr<map::route::RoutePath>> m_paths = {};

	std::vector<std::shared_ptr<map::route::Route>> m_all_routes = {};

	std::shared_ptr<Util::Renderer> m_render_manager;

// base
public:
    PathManager(const PathManager&) = delete;

    PathManager(PathManager&&) = delete;

    PathManager& operator=(const PathManager&) = delete;

    PathManager& operator=(PathManager&&) = delete;

	~PathManager() = default;

};

}

#endif
