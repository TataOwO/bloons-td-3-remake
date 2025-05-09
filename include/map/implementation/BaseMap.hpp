#ifndef BASE_MAP_HPP
#define BASE_MAP_HPP

#include "Util/GameObject.hpp"

namespace map {class MapBackground;}
namespace handlers {class PathManager;}
namespace inputs {class Clickable;}

namespace map::implementation {

class BaseMap : public Util::GameObject {
protected:
	BaseMap();
public:
	virtual void update() = 0;
	
	std::vector<std::shared_ptr<inputs::Clickable>> get_clickables() {return m_clickables;};
protected:
	std::shared_ptr<map::MapBackground> m_background;
	
	// NOT INITIALIZED YET
	std::shared_ptr<handlers::PathManager> m_path_manager;

	std::vector<std::shared_ptr<inputs::Clickable>> m_clickables = {};

// base
public:
	BaseMap(const BaseMap&) = delete;

	BaseMap(BaseMap&&) = delete;

	BaseMap& operator=(const BaseMap&) = delete;

	BaseMap& operator=(BaseMap&&) = delete;

	virtual ~BaseMap() = default;
};

}

#endif 
