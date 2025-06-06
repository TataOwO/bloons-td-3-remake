#ifndef MAP_SELECTOR_HPP
#define MAP_SELECTOR_HPP

#include "constants/TYPE.hpp"
#include "Util/GameObject.hpp"

namespace map::implementation {class BaseMap;}
namespace map::implementation {enum class MAP_TYPE;}
namespace map {class MapBackground;}

namespace inputs {class Clickable;}
namespace layout {class Button;}

namespace hitboxes {class I_BaseHitbox;}

namespace logics {

class MapSelector final: public Util::GameObject {
public:
	MapSelector();

	void update();

	bool should_switch() const {return has_map;}
	CONSTANTS::TYPE::MAP get_map_type();
private:
	CONSTANTS::TYPE::MAP m_spawn_map_type;
	bool has_map = false;

	std::shared_ptr<map::MapBackground> m_background;

	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec;
	std::vector<std::shared_ptr<layout::Button>> m_button_vec;
	
	std::shared_ptr<layout::Button> peaceful_button;
	std::shared_ptr<layout::Button> ice_button;
	std::shared_ptr<layout::Button> teleport_button;
	std::shared_ptr<layout::Button> summon_button;

	std::shared_ptr<map::MapBackground> m_peaceful_background;
	std::shared_ptr<map::MapBackground> m_ice_background;
	std::shared_ptr<map::MapBackground> m_teleport_background;
	std::shared_ptr<map::MapBackground> m_summon_background;

	int secret_map_state = 0;
// base
public:
	MapSelector(const MapSelector&) = delete;

	MapSelector(MapSelector&&) = delete;

	MapSelector& operator=(const MapSelector&) = delete;

	MapSelector& operator=(MapSelector&&) = delete;

	~MapSelector() override = default;
};

}

#endif
