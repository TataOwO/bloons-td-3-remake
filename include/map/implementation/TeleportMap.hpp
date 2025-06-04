#ifndef TELEPORT_MAP_HPP
#define TELEPORT_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace Util {class Animation;}

namespace map::implementation {

class TeleportMap final : public BaseMap {
public:
	TeleportMap();

	void set_wave(int) override;
	void update() override;

	CONSTANTS::TYPE::MAP get_map_type() const override {return CONSTANTS::TYPE::MAP::TELEPORT;}
private:
	std::vector<std::shared_ptr<handlers::PathManager>> m_wave_paths;
	bool m_animation_was_playing = false;

	std::shared_ptr<Util::Animation> m_animation;

	std::vector<std::shared_ptr<Util::Animation>> m_animations_vec;
// base
public:
	TeleportMap(const TeleportMap&) = delete;

	TeleportMap(TeleportMap&&) = delete;

	TeleportMap& operator=(const TeleportMap&) = delete;

	TeleportMap& operator=(TeleportMap&&) = delete;

	~TeleportMap() override = default;
};

}


#endif
