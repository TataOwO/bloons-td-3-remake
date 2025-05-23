#include "map/route/RoutePath.hpp"

#include "map/route/Route.hpp"

namespace map::route {

RoutePath::RoutePath(std::vector<std::shared_ptr<Route>> routes) {
	m_routes = routes;

	for (std::shared_ptr<Util::GameObject> route : routes) {
		this->AddChild(route);
	}

	m_route_count = routes.size();
	for (int i=0; i<m_route_count-1; ++i) {
		routes.at(i)->set_next_route(routes.at(i+1));
	}

	m_start_route = m_routes[0];

	m_start_route->recursive_calculate_exit_length();
};

std::vector<std::shared_ptr<Route>> RoutePath::get_all_routes() {
	return m_routes;
};

std::shared_ptr<Route> RoutePath::get_start_route() const {
	return m_start_route;
};

RoutePath::~RoutePath() {
	
}

}
