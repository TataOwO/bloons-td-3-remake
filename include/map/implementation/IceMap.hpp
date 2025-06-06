#ifndef ICE_MAP_HPP
#define ICE_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace map::implementation {class IceMapFrog;}

namespace inputs {class Clickable;}

namespace map::implementation {

class IceMap final : public BaseMap {
public:
	IceMap();

	void set_wave(int) override;
	void update() override;

	CONSTANTS::TYPE::MAP get_map_type() const override {return CONSTANTS::TYPE::MAP::ICE;}
	
private:
	std::shared_ptr<map::implementation::IceMapFrog> m_frog;
	
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
