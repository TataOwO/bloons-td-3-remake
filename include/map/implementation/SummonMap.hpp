#ifndef SUMMON_MAP_HPP
#define SUMMON_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {

class SummonMap final : public BaseMap {
public:
	SummonMap();

	void update() override;

	MAP_TYPE get_map_type() const override {return MAP_TYPE::SUMMON;}
private:

// base
public:
	SummonMap(const SummonMap&) = delete;

	SummonMap(SummonMap&&) = delete;

	SummonMap& operator=(const SummonMap&) = delete;

	SummonMap& operator=(SummonMap&&) = delete;

	~SummonMap();
};

}


#endif
