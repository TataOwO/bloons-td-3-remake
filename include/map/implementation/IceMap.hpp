#ifndef ICE_MAP_HPP
#define ICE_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class IceMap final : public BaseMap {
public:
	IceMap();

	void set_wave(int) override;
	void update() override;

	MAP_TYPE get_map_type() const override {return MAP_TYPE::ICE;}
private:

// base
public:
	IceMap(const IceMap&) = delete;

	IceMap(IceMap&&) = delete;

	IceMap& operator=(const IceMap&) = delete;

	IceMap& operator=(IceMap&&) = delete;

	~IceMap() override;
};

}

#endif
