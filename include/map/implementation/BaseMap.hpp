#ifndef BASE_MAP_HPP
#define BASE_MAP_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

#include "map/MapBackground.hpp"
#include "handlers/PathManager.hpp"
#include "inputs/Clickable.hpp"

namespace map::implementation {

class BaseMap : public Util::GameObject {
protected:
	BaseMap() = default;
public:
	virtual void update() = 0;
protected:
	map::MapBackground m_background = map::MapBackground();
	
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
