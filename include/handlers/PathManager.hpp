#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include "Util/Renderer.hpp"

#include "map/route/Route.hpp"
#include "map/route/RoutePath.hpp"

#include "hitboxes/I_BaseHitbox.hpp"

namespace handlers {

class PathManager final {
public:
	PathManager(std::vector<std::shared_ptr<map::route::RoutePath>> paths, const std::shared_ptr<Util::Renderer> &render_manager);

	std::shared_ptr<map::route::Route> get_collided_route(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox);

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
