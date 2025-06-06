#ifndef ROUTE_PATH_HPP
#define ROUTE_PATH_HPP

#include "Util/GameObject.hpp"

namespace map::route {class Route;}

namespace map::route {
class RoutePath final : public Util::GameObject {
public:
    explicit RoutePath(std::vector<std::shared_ptr<Route>> routes);
public:
	std::vector<std::shared_ptr<Route>> get_all_routes();

	std::shared_ptr<Route> get_start_route() const;
private:
    std::vector<std::shared_ptr<Route>> m_routes;

	std::shared_ptr<Route> m_start_route;
	
	int m_route_count;

public:

    RoutePath(const RoutePath&) = delete;

    RoutePath(RoutePath&&) = delete;

    RoutePath& operator=(const RoutePath&) = delete;

    RoutePath& operator=(RoutePath&&) = delete;

	~RoutePath() override;

};
}

#endif
