#ifndef ROUTE_PATH_HPP
#define ROUTE_PATH_HPP

#include "map/route/Route.hpp"
#include <vector>

namespace map::route {
class RoutePath : public Util::GameObject {
public:
    explicit RoutePath(std::vector<std::shared_ptr<Route>> routes);

    RoutePath(const RoutePath&) = delete;

    RoutePath(RoutePath&&) = delete;

    RoutePath& operator=(const RoutePath&) = delete;

    RoutePath& operator=(RoutePath&&) = delete;

	std::shared_ptr<Route> get_start_route() const;
private:
    std::vector<std::shared_ptr<Route>> m_routes;

	std::shared_ptr<Route> m_start_route;
	
	int m_route_count;
};
}

#endif
