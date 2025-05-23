#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include "Util/GameObject.hpp"

namespace Util {class Renderer;}
namespace map::route {class Route;}
namespace map::route {class RoutePath;}
namespace hitboxes {class I_BaseHitbox;}

namespace handlers {

class PathManager final : public Util::GameObject {
public:
	PathManager(const std::vector<std::shared_ptr<map::route::RoutePath>>& paths);

	std::shared_ptr<map::route::Route> get_collided_route(const std::shared_ptr<hitboxes::I_BaseHitbox> &hitbox);

public:
	std::vector<std::shared_ptr<map::route::Route>> get_all_routes() {return m_all_routes;};

	std::shared_ptr<map::route::RoutePath> get_random_route_path() const;
private:
	std::vector<std::shared_ptr<map::route::RoutePath>> m_paths = {};

	std::vector<std::shared_ptr<map::route::Route>> m_all_routes = {};

// base
public:
    PathManager(const PathManager&) = delete;

    PathManager(PathManager&&) = delete;

    PathManager& operator=(const PathManager&) = delete;

    PathManager& operator=(PathManager&&) = delete;

	~PathManager() override;

};

}

#endif
