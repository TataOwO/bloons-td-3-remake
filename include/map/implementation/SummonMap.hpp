#ifndef SUMMON_MAP_HPP
#define SUMMON_MAP_HPP

#include "map/implementation/BaseMap.hpp"

namespace handlers {
	class MonkeyManager;
}

namespace map::implementation {

class SummonMap final : public BaseMap {
public:
	SummonMap();

	void set_wave(int) override;
	void update() override;

	CONSTANTS::TYPE::MAP get_map_type() const override {return CONSTANTS::TYPE::MAP::SUMMON;}

	void set_monkey_manager(const std::shared_ptr<handlers::MonkeyManager>& monkey_m) {m_monkey_manager = monkey_m;};
private:
	std::shared_ptr<handlers::MonkeyManager> m_monkey_manager;

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
