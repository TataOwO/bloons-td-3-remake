#ifndef SUMMON_MAP_HPP
#define SUMMON_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace handlers {class MonkeyManager;}
namespace hitboxes {class I_BaseHitbox;}

namespace map::implementation {

class SummonMap final : public BaseMap {
public:
	SummonMap(const std::shared_ptr<handlers::MonkeyManager>& monkey_m);

	void set_wave(int) override;
	void update() override;

	CONSTANTS::TYPE::MAP get_map_type() const override {return CONSTANTS::TYPE::MAP::SUMMON;}

	void set_monkey_manager(const std::shared_ptr<handlers::MonkeyManager>& monkey_m) {m_monkey_manager = monkey_m;};
private:
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

	// to be initialized
	std::shared_ptr<hitboxes::I_BaseHitbox> m_dart_placement;
	std::shared_ptr<hitboxes::I_BaseHitbox> m_bomb_placement;
	std::shared_ptr<hitboxes::I_BaseHitbox> m_boomer_placement;
	std::shared_ptr<hitboxes::I_BaseHitbox> m_ice_placement;
	std::shared_ptr<hitboxes::I_BaseHitbox> m_super_placement;
	std::shared_ptr<hitboxes::I_BaseHitbox> m_tack_placement;

	bool m_dart_matched = false;
	bool m_bomb_matched = false;
	bool m_boomer_matched = false;
	bool m_ice_matched = false;
	bool m_super_matched = false;
	bool m_tack_matched = false;
	bool m_god_is_spawned = false;

// base
public:
	SummonMap(const SummonMap&) = delete;

	SummonMap(SummonMap&&) = delete;

	SummonMap& operator=(const SummonMap&) = delete;

	SummonMap& operator=(SummonMap&&) = delete;

	~SummonMap() override;
};

}


#endif
