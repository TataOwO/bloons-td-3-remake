#ifndef ICE_MAP_HPP
#define ICE_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class IceMap final : public map::implementation::IceMap {
public:
	// TODO

private:
	std::shared_ptr<>

// base
public:
	IceMap(const IceMap&) = delete;

	IceMap(IceMap&&) = delete;

	IceMap& operator=(const IceMap&) = delete;

	IceMap& operator=(IceMap&&) = delete;

	~IceMap() = default;
}

}

#endif
