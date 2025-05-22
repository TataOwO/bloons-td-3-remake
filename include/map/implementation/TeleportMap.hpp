#ifndef TELEPORT_MAP_HPP
#define TELEPORT_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class TeleportMap final : public BaseMap {
public:
	TeleportMap();

	void update() override;

	MAP_TYPE get_map_type() const override {return MAP_TYPE::TELEPORT;}
private:

// base
public:
	TeleportMap(const TeleportMap&) = delete;

	TeleportMap(TeleportMap&&) = delete;

	TeleportMap& operator=(const TeleportMap&) = delete;

	TeleportMap& operator=(TeleportMap&&) = delete;

	~TeleportMap();
};

}


#endif
