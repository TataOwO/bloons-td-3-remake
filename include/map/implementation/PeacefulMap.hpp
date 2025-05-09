#ifndef PEACEFUL_MAP_HPP
#define PEACEFUL_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class PeacefulMap final : public BaseMap {
public:
	PeacefulMap();

	void update() override;

private:

// base
public:
	PeacefulMap(const PeacefulMap&) = delete;

	PeacefulMap(PeacefulMap&&) = delete;

	PeacefulMap& operator=(const PeacefulMap&) = delete;

	PeacefulMap& operator=(PeacefulMap&&) = delete;

	~PeacefulMap();
};

}


#endif
