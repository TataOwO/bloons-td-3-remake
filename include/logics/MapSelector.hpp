#ifndef MAP_SELECTOR_HPP
#define MAP_SELECTOR_HPP

#include "Util/GameObject.hpp"

namespace map::implementation {class BaseMap;}
namespace map {class MapBackground;}

namespace inputs {class Clickable;}
namespace layout {class Button;}

namespace hitboxes {class I_BaseHitbox;}

namespace logics {

class MapSelector final: public Util::GameObject {
public:
	MapSelector();

	void update();

	bool should_switch() const {return m_generated_map!=nullptr;}
	std::shared_ptr<map::implementation::BaseMap> get_map();
private:
	std::shared_ptr<map::implementation::BaseMap> m_generated_map;

	std::shared_ptr<map::MapBackground> m_background;

	std::vector<std::shared_ptr<inputs::Clickable>> m_clickable_vec;
	std::vector<std::shared_ptr<layout::Button>> m_button_vec;
	
	std::shared_ptr<hitboxes::I_BaseHitbox> peaceful_hitbox;
	std::shared_ptr<hitboxes::I_BaseHitbox> ice_hitbox;
	std::shared_ptr<hitboxes::I_BaseHitbox> teleport_hitbox;
	std::shared_ptr<hitboxes::I_BaseHitbox> summon_hitbox;

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
